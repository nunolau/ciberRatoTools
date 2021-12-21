/*
    This file is part of ciberRatoToolsSrc.

    Copyright (C) 2001-2011 Universidade de Aveiro

    ciberRatoToolsSrc is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    ciberRatoToolsSrc is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/* RobSock.h
 *
 * Interface to libRobSock.a, the library that allows programming
 * CiberRato Robot Agents using C.
 *
 * For more information about the CiberRato Robot Simulator 
 * please see http://microrato.ua.pt/ or contact us.
 */

#ifndef ROBSOCK_H
#define ROBSOCK_H

#if defined(ROBSOCK_LIBRARY)
#  define ROBSOCK_EXPORT Q_DECL_EXPORT
#else
#  define ROBSOCK_EXPORT Q_DECL_IMPORT
#endif

#define CENTER 0
#define LEFT   1
#define RIGHT  2
#define OTHER1 3

#define CELLROWS 7
#define CELLCOLS 14


#ifdef __cplusplus
extern "C" 
{
#else
typedef unsigned char bool;
#endif

/**************************************************************************/
/************* Initialization *********************************************/
/**************************************************************************/

/*! Initializes Robot and Connects to Simulator 
 *  Parameters : 
 *          name - Robot name
 *          host - Host where simulator is running 
 *  Returns -1 in case of error
 */
extern int           InitRobot(char *name,int id, char *host);

/*! Initializes Robot and Connects to Simulator 
 *  Parameters : 
 *          name - Robot name
 *          host - Host where simulator is running 
 *          IRSensorAngles - contais the angles of the 4 IR Sensors 
 *                           with respect to the front of the robot (in degrees).
 *   Returns -1 in case of error
 */
extern int           InitRobot2(char *name,int id, double IRSensorAngles[4], char *host);

/*! Initializes Robot that also works as the beacon and Connects to Simulator 
 *  Parameters : 
 *          name - Robot name
 *          id   - Robot position in starting grid
 *          height - Height of beacon
 *          host - Host where simulator is running 
 *  Returns -1 in case of error
 */
extern int           InitRobotBeacon(char *name, int id, double height, char *host);


/**************************************************************************/
/************* Sensors ****************************************************/
/**************************************************************************/

/*! Gets the next Sensor Values sent by Simulator 
 *  if no message is present waits 
 *  Returns -1 in case of error 
 */
extern int           ReadSensors(void);

/*  The following functions access values that have been read by ReadSensors() 
 *  they do not read new values 
 */

/*  simulation time */
extern unsigned int   GetTime(void);

/*! Indicates if a new Obstacle measure from sensor id has arrived. 
 *  The value of GetObstacleSensor is invalid when IsObstacleReady returns false
 */
extern bool            IsObstacleReady(int id);

/*! GetObstacleSensor value is inversely proportional to obstacle distance  
 *  id may be one of LEFT, RIGHT, CENTER or OTHER1 
 */
extern double          GetObstacleSensor(int id); 
    
/*! Indicates if a new beacon measure has arrived. 
 *  The value of GetBeaconSensor is invalid when IsBeaconReady returns false
 */
extern bool            IsBeaconReady(int id);

struct beaconMeasure {
        bool   beaconVisible;  /* true if robot can see beacon */
        double beaconDir;      /* direction of beacon */
                               /*   only valid if beaconVisible is true */
};

/* GetNumberOfBeacons returns the number of beacons in the lab
 */
extern int GetNumberOfBeacons(void);     

/* GetBeaconSensor value is the direction of Beacon 
 * in Robot coordinates (-180.0, 180.0) 
 */
extern struct beaconMeasure GetBeaconSensor(int id);     
    
/*! Indicates if a new compass measure has arrived. 
 *  The value of GetCompassSensor is invalid when IsCompassReady returns false
 */
extern bool            IsCompassReady(void);

/* GetCompassSensor value is the direction of Robot in Ground 
 * coordinates (-180.0, 180.0) 
 */
extern double          GetCompassSensor(void);    
    
/*! Indicates if a new ground measure has arrived. 
 *  The value of GetGroundSensor is invalid when IsGroundReady returns false
 */
extern bool            IsGroundReady(void);

/* if robot is inside a target area returns the id of the area, otherwise returns -1 */
extern int            GetGroundSensor(void);     
    
/*! Indicates if a new bumper measure has arrived. 
 *  The value of GetBumperSensor is invalid when IsBumperReady returns false
 */
extern bool            IsBumperReady(void);

/* active when robot collides */
extern bool           GetBumperSensor(void);     

/*! Indicates if score can be retrieved using score sensor 
 */
bool IsScoreReady(void);

/* returns current score */
int GetScoreSensor(void);

/*! Indicates if a new GPS measure has arrived. 
 *  The value of GetX, GetY and GetDir is invalid when IsGPSReady returns false
 */
extern bool            IsGPSReady();
extern bool            IsGPSDirReady();


extern bool NewMessageFrom(int id);
extern char* GetMessageFrom(int id);

/* GPS sensor - can be used for debug, invoke simulator with "-gps" option */
extern double          GetX(void); 
extern double          GetY(void); 
extern double          GetDir(void);


/*
 Request a list of nReqs Sensors
 Sensors are identified by the following strings: 
    "Compass", "Ground", "Collision", "IRSensor0", IRSensor1", etc, "Beacon0", "Beacon1", etc
*/
void RequestSensors(int nReqs, ...);


/**************************************************************************/
/************* Buttons ****************************************************/
/**************************************************************************/

/* Start */   
extern bool           GetStartButton(void);

/* Stop */
extern bool           GetStopButton(void);

/**************************************************************************/
/************* Actions ****************************************************/
/**************************************************************************/

/* Drive right motor with rPow and left motor with lPow - Powers in (-0.15,0.15) */
extern void           DriveMotors(double lPow,double rPow);

/* Signal the end of phase 1 (go to target) */
extern void           SetReturningLed(bool val);

/* Set the state of visiting Led */
extern void           SetVisitingLed(bool val);

/* Finish the round */
extern void           Finish(void);

/* Broadcast message */
extern void           Say(char * msg);

/* Requests */
void RequestCompassSensor(void);
void RequestGroundSensor(void);
void RequestObstacleSensor(int Id);
void RequestBeaconSensor(int Id);


/**************************************************************************/
/************* Checking Actions *******************************************/
/**************************************************************************/

/* Verify if SetReturningLed() was executed */
extern bool           GetReturningLed(void);

/* Verify state of Visiting Led */
extern bool           GetVisitingLed(void);

/* Verify if Finish() was executed */
extern bool           GetFinished(void);

/**************************************************************************/
/************* Parameters *************************************************/
/**************************************************************************/

/* Return the simulation cycle time */
extern int GetCycleTime(void);

/* Return the total simulation time */
extern int GetFinalTime(void);

/* Return the key time */
extern int GetKeyTime(void);


/*****
        Functions returning noise levels
******/

/* Returns maximum additive noise of infra-red sensors */
extern double GetNoiseObstacleSensor(void);

/* Returns maximum additive noise of beacon angular direction */
extern double GetNoiseBeaconSensor(void);

/* Returns maximum additive noise of compass */
extern double GetNoiseCompassSensor(void);

/* Returns maximum multipicative noise of motors */
extern double GetNoiseMotors(void);

unsigned int  GetNumberRequestsPerCycle(void);

double GetBeaconAperture();

unsigned int GetBeaconLatency();
unsigned int GetIRLatency();
unsigned int GetGroundLatency();
unsigned int GetBumperLatency();

bool GetBeaconRequestable();
bool GetIRRequestable();
bool GetGroundRequestable();
bool GetBumperRequestable();

void ReadMap(char *filename, void *vmap);

#ifdef __cplusplus
}
#endif

#ifdef CIBERQTAPP

#include <qapplication.h>

extern void *        Link(void);

#endif /* CIBERQTAPP */

#endif /*ROBSOCK_H */
