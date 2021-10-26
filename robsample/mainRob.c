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

float getXvel(void);
float controlAction(float setPoint, float feedback);
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

    float velSetPoint=0.1;

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

    /* Compute error and control value */
    lPow = rPow = controlAction(velSetPoint,xVel);

    DriveMotors(lPow,rPow);

    fprintf(fd,"%u\t",GetTime());
    fprintf(fd,"%4.5f\t%4.5f\t",GetX(),GetY());
    fprintf(fd,"%4.5f\t",xVel);
    fprintf(fd,"%4.5f\t",velSetPoint-xVel);
    fprintf(fd,"%4.5f\t",lPow);

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
* float xLineSensor(float targetY)
*
* Provides a simulation of a line sensor, detecting a
* horizontal line at y=targetY
*/
float xLineSensor(float targetY){
  float value = (targetY - GetY())/cos(M_PI*GetDir()/180.0);
  value = (targetY - GetY());

  if (value>1)
  value = 1;
  if (value < -1)
  value = -1;
  return value;
}

#define NONE          0
#define BANG          1
#define BANG2         2
#define BANGH         3
#define P             10
#define PID           11
#define CONTROLLER    P

float controlAction(float setPoint, float feedback)
{
  const float Kp = 12;
  const float Ti = 10;
  // const float Ti = FLT_MAX;
  const float Td = 0.0;
  const float h = 0.050;
  const float max_u = 0.5;

  const float K0 = Kp*(1+h/Ti+Td/h);
  const float K1 = -Kp*(1+2*Td/h);
  const float K2 = Kp*Td/h;

  // memory for the control signal
  static float u_m1 = 0;
  // memory for error
  static float e_m1 = 0;
  static float e_m2 = 0;

  const float delta = 0.05;

  float u=0;
  float e=0;

  /* Compute error */
  e = setPoint - feedback;

  #if CONTROLLER==BANG
  if(e>0){
    u = max_u;
  }
  else if (e<0){
    u = -max_u;
    u = 0;
  }
  else{
    u = 0;
  }
  return u;
  #elif CONTROLLER==BANG2
  if(e>0){
    u = max_u;
  }
  else if (e<0){
    u = -max_u;
  }
  else{
    u = 0;
  }
  return u;
  #elif CONTROLLER==BANGH
  if(e>0+delta){
    u = max_u;
  }
  else if (e<0-delta){
    u = -max_u;
  }
  else{
    u = u_m1;
  }
  u_m1 = u;
  return u;

  #elif CONTROLLER==P
  return Kp*e;
  #elif CONTROLLER == PID

  /* Compute control signal */
  u = u_m1 + K0*e + K1*e_m1 + K2*e_m2;

  /* store values for next iterations */
  e_m2 = e_m1;
  e_m1 = e;
  u_m1 = u;


  // Clip the control signal to avoid saturation
  if(u_m1>max_u)
  u_m1 = max_u;
  if (u_m1<-max_u)
  u_m1 = -max_u;

  return u;

  #else
  return setPoint;
  #endif

}
