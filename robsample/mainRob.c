/* mainRob.C
*
* Basic Robot Agent
* Very simple version for demonstration
*
* For more information about the CiberRato Robot Simulator
* please see http://microrato.ua.pt/ or contact us.
*/

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#include "RobSock.h"

#include "robfunc.h"

#define true 1
#define false 0

typedef enum {NONE, BANG, BANG2, BANGH, P, PID} controller_t;

float getXvel(void);
float controlAction(controller_t type, float setPoint, float feedback);
float xLineSensor(float targetY);



int main(int argc, char *argv[])
{
  char host[100]="localhost";
  char rob_name[20]="robsample";
  float lPow,rPow;
  int rob_id = 1;
  char lmap[CELLROWS*2-1][CELLCOLS*2-1]; // in this map the center of cell (i,j), (i in 0..6, j in 0..13) is mapped to lmap[i*2][j*2].
  // to know if there is a wall on top of cell(i,j) (i in 0..5), check if the value of lmap[i*2+1][j*2] is space or not
  float xVel;

  float velSetPoint=0.1;


  printf( " Sample Robot\n Copyright (C) 2001-2019 Universidade de Aveiro\n" );

  /* processing arguments */
  while (argc > 2) /* every option has a value, thus argc must be 1, 3, 5, ... */
  {
    if (strcmp(argv[1], "--host") == 0 || strcmp(argv[1], "-h") == 0)
    {
      strncpy(host, argv[2], 99);
      host[99]='\0';
    }
    else if (strcmp(argv[1], "--robname") == 0 || strcmp(argv[1], "-r") == 0)
    {
      strncpy(rob_name, argv[2], 19);
      rob_name[19]='\0';
    }
    else if (strcmp(argv[1], "--pos") == 0 || strcmp(argv[1], "-p") == 0)
    {
      if(sscanf(argv[2], "%d", &rob_id)!=1)
      argc=0; /* error message will be printed */
    }
    else if (strcmp(argv[1], "--map") == 0 || strcmp(argv[1], "-m") == 0)
    {
      ReadMap(argv[2],lmap);
      for(int r=CELLROWS*2-2; r>=0; r--) {
        for(int c=0; c<CELLCOLS*2-1; c++) {
          printf("%c", lmap[r][c]);
        }
        printf("\n");
      }
    }
    else
    {
      break; /* the while */
    }
    argc -= 2;
    argv += 2;
  }

  if (argc != 1)
  {
    fprintf(stderr, "Bad number of parameters\n"
    "SYNOPSIS: mainRob [--host hostname] [--robname robotname] [--pos posnumber]\n");

    return 1;
  }

  /* Connect Robot to simulator */
  if(InitRobot(rob_name, rob_id, host)==-1)
  {
    printf( "%s Failed to connect\n", rob_name);
    exit(1);
  }
  printf( "%s Connected\n", rob_name );

  /* Open a file for writing values */
  FILE *fd=fopen("output.txt","w+");

  /* Main cycle */
  while(1)
  {

    /* Reading next values from Sensors */
    ReadSensors();

    if(GetFinished()) /* Simulator has received Finish() or Robot Removed */
    {
      printf(  "%s Exiting\n", rob_name );
      exit(0);
    }

    /* Test if reached end of labyrinth */
    if(GetX() > 26.0){
      printf("Reached end of maze! Terminating...\n");
      fclose(fd);
      exit(0);
    }

    if(GetStopButton() && (GetTime()>0) ){
      fclose(fd);
      printf("Stop button pressed! Terminating...\n");
      exit(0);
    }

    /* Change speed according to X position */
    if(((int)GetX())/4 % 2){
      velSetPoint = 0.1;
    }
    else{
      velSetPoint = 0.15;
    }
    //velSetPoint = 0.1;

    /* Read current speed */
    xVel = getXvel();

    /* Compute control value */
    lPow = rPow = controlAction(NONE, velSetPoint,xVel);

    /* Act on the system */
    DriveMotors(lPow,rPow);

    fprintf(fd,"%u\t",GetTime());
    fprintf(fd,"%4.5f\t%4.5f\t",GetX(),GetY());
    fprintf(fd,"%4.5f\t",velSetPoint);
    fprintf(fd,"%4.5f\t",xVel);
    fprintf(fd,"%4.5f\t",lPow);   /* lPow (or rPow) is equal to u */

    fprintf(fd,"\n");

    printf("%u\t",GetTime());
    printf("%4.5f\t%4.5f\t",GetX(),GetY());
    printf("%4.5f\t",velSetPoint);
    printf("%4.5f\t",lPow);
    printf("%u\t",((int)GetX())/4 % 2 );
    printf("\n");
  }

  fclose(fd);
  return 1;
}

/**
 * float getXvel(void)
 *
 * Computes current velocity along X axis.
 */
float getXvel(void){

  float xVel;
  float currentXpos;
  static float lastXpos=0;
  static int lastTime;
  int currTime;

  currentXpos = GetX();
  currTime = GetTime();

  if(currTime > lastTime){
    xVel = (currentXpos - lastXpos)/(currTime - lastTime);
  }
  else{
    xVel = 0;
  }

  /* Store for future memory... */
  lastXpos = currentXpos;
  lastTime = currTime;

  return xVel;

}

/**
* float controlAction(controller_t type, float setPoint, float feedback)
*
* Implements the control action, dependening on type.
*
* If type is set to NONE, no feedback is used. The setpoint is propagated
* to the output (r=u)
*/
float controlAction(controller_t type, float setPoint, float feedback)
{
  float u=0;    /**> Control signal */
  float e=0;    /**> Error signal */

  const float max_u = 0.5;  // max_u - saturation value for control signal

  // PID constants:
  const float Kp = 1;       // Kp - proportional constant
  // const float Ti = ;     // Ti - Integration time
  //      set to FLT_MAX to disable I component
  const float Ti = FLT_MAX;
  const float Td = 0.0;     // Td - differential time
  const float h = 0.050;    // h  - sampling interval

  // Auxiliary constants for the PID controller
  static const float K0 = Kp*(1+h/Ti+Td/h);
  static const float K1 = -Kp*(1+2*Td/h);
  static const float K2 = Kp*Td/h;

  // memory for error
  static float e_m1 = 0;
  static float e_m2 = 0;

  // memory for the control signal
  static float u_m1 = 0;

  /* Compute error */
  e = setPoint - feedback;

  /* Implement control action depending on the type of control. */
  switch (type) {
    case NONE:
      /* No feedback action */
      u = setPoint;
      break;
    case BANG:
      /* Bang-bang control */
      if(e>0){
        u = max_u;
      }
      else{
        u = 0;
      }
      break;
    case BANG2:
      /* Bang-bang control with bipolar output */
      if(e>0){
        u = max_u;
      }
      else if (e<0){
        u = -max_u;
      }
      else{
        u = 0;
      }
      break;
    case BANGH:
      /* Bang-bang control with hysteresis */
      const float delta = 0.05;

      if(e>delta){
        u = max_u;
      }
      else if (e<-delta){
        u = -max_u;
      }
      else{
        u = u_m1;
      }
      u_m1 = u;
      break;
    case P:
    /* Proportional control */
      u = Kp*e;
      break;
    case PID:

      /* Compute control signal */
      u = u_m1 + K0*e + K1*e_m1 + K2*e_m2;

      /* store values for next iterations */
      e_m2 = e_m1;
      e_m1 = e;
      u_m1 = u;

      // Clip the control signal to avoid saturation
      if(u_m1>max_u){
        u_m1 = max_u;
      }
      if (u_m1<-max_u){
        u_m1 = -max_u;
      }
      break;
  }

  return u;
}
