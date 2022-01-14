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
////////////////////////////////////////////////
// RobSock.cpp
////////////////////////////////////////////////


#include <assert.h>
#include <iostream>

#include <stdarg.h>
#include <locale.h>

#include "RobSock.h"

#include "croblink.h"

static CRobLink *robLink=0;

/* Init */
void *Link(void)
{
    assert(robLink!=0);
    return robLink;
}


int InitRobot(char *rob_name, int rob_id, char *host)
{
    assert(robLink==0);
    robLink=new CRobLink(rob_name, rob_id, host);
    setlocale(LC_ALL,"C");
    return robLink->status();
}

int InitRobot2(char *rob_name, int rob_id, double IRSensorAngles[NUM_IR_SENSORS], char *host)
{
    assert(robLink==0);
    robLink=new CRobLink(rob_name, rob_id, IRSensorAngles, host);
    setlocale(LC_ALL,"C");
    return robLink->status();
}

int InitRobotBeacon(char *rob_name, int rob_id, double height, char *host)
{
    assert(robLink==0);
    robLink=new CRobLink(rob_name, rob_id, height, host);
    setlocale(LC_ALL,"C");
    return robLink->status();
}

int ReadSensors(void)
{
    assert(robLink!=0);
    return robLink->ReadSensors();
}

/* Time */
unsigned int GetTime(void)
{
    assert(robLink!=0);
    return robLink->time();
}

/* Sensors */

bool IsObstacleReady(int id)
{
    assert(robLink!=0);
    return robLink->IRSensorReady(id);
}

double GetObstacleSensor(int id)
{
    assert(robLink!=0);
    return (double)(robLink->IRSensor(id));
}

int GetNumberOfBeacons(void)
{
    assert(robLink!=0);
    return (robLink->nBeacons());
}

bool IsBeaconReady(int id)
{
    assert(robLink!=0);
    return robLink->beaconReady(id);
}

struct beaconMeasure GetBeaconSensor(int id)
{
    assert(robLink!=0);
    return (robLink->beacon(id));
}

bool IsCompassReady(void)
{
    assert(robLink!=0);
    return robLink->compassReady();
}

double GetCompassSensor(void)
{
    assert(robLink!=0);
    return (double)(robLink->compass());
}

bool NewMessageFrom(int from)
{
    assert(robLink!=0);
    return robLink->newMessage(from);
}

char* GetMessageFrom(int from)
{
    assert(robLink!=0);
    QByteArray latinMsg = robLink->message(from).toLatin1();
    return (char *)latinMsg.constData();
}

bool IsGPSReady(void)
{
    assert(robLink!=0);
    return robLink->gpsReady();
}

bool IsGPSDirReady(void)
{
    assert(robLink!=0);
    return robLink->gpsDirReady();
}

double GetX(void)
{
    assert(robLink!=0);
    return (double)(robLink->posx());
}

double GetY(void)
{
    assert(robLink!=0);
    return (double)(robLink->posy());
}

double GetDir(void)
{
    assert(robLink!=0);
    return (double)(robLink->posdir());
}

bool IsGroundReady(void)
{
    assert(robLink!=0);
    return robLink->groundReady();
}

int GetGroundSensor(void)
{
    assert(robLink!=0);
    return robLink->ground();
}

bool IsBumperReady(void)
{
    assert(robLink!=0);
    return robLink->collisionReady();
}

bool GetBumperSensor(void)
{
    assert(robLink!=0);
    return robLink->collision();
}

bool IsScoreReady(void)
{
    assert(robLink!=0);
    return robLink->scoreReady();
}

int GetScoreSensor(void)
{
    assert(robLink!=0);
    return robLink->score();
}


void RequestGroundSensor(void)
{
    assert(robLink!=0);
    robLink->requestGround();
}

void RequestCompassSensor(void)
{
    assert(robLink!=0);
    robLink->requestCompass();
}

void RequestBeaconSensor(int id)
{
    assert(robLink!=0);
    robLink->requestBeacon(id);
}

void RequestObstacleSensor(int id)
{
    assert(robLink!=0);
    robLink->requestObstacle(id);
}

void RequestSensors(int nReqs, ...)
{
    assert(robLink!=0);

    va_list ap;

    va_start(ap, nReqs);
    robLink->requestSensors(nReqs, ap);
    va_end(ap);
}


/* Buttons */
bool GetStartButton(void)
{
    assert(robLink!=0);
    return robLink->start();
}

bool GetStopButton(void)
{
    assert(robLink!=0);
    return robLink->stop();
}

bool GetFinished(void)
{
    assert(robLink!=0);
    return robLink->endLed();
}

bool GetReturningLed(void)
{
    assert(robLink!=0);
    return robLink->returningLed();
}

bool GetVisitingLed(void)
{
    assert(robLink!=0);
    return robLink->visitingLed();
}

// Commands
void DriveMotors(double lPow,double rPow)
{
    assert(robLink!=0);
    robLink->DriveMotors(lPow,rPow);
}

void SetReturningLed(bool val)
{
    assert(robLink!=0);
    robLink->SetReturningLed(val);
}

void SetVisitingLed(bool val)
{
    assert(robLink!=0);
    robLink->SetVisitingLed(val);
}

void Finish(void)
{
    assert(robLink!=0);
    robLink->Finish();
}

void Say(char *msg)
{
    assert(robLink!=0);
    robLink->Say(msg);
}
// Parameters
int GetCycleTime(void)
{
    assert(robLink!=0);
    return robLink->cycleTime();
}

int GetFinalTime(void)
{
    assert(robLink!=0);
    return robLink->finalTime();
}

int GetKeyTime(void)
{
    assert(robLink!=0);
    return robLink->keyTime();
}

unsigned int  GetNumberRequestsPerCycle(void)
{
    assert(robLink!=0);
    return (robLink->nReqPerCycle());
}

double GetNoiseObstacleSensor(void)
{
    assert(robLink!=0);
    return (double)(robLink->obstacleNoise());
}

double GetNoiseBeaconSensor(void)
{
    assert(robLink!=0);
    return (double)(robLink->beaconNoise());
}

double GetNoiseCompassSensor(void)
{
    assert(robLink!=0);
    return (double)(robLink->compassNoise());
}

double GetNoiseMotors(void)
{
    assert(robLink!=0);
    return (double)(robLink->motorsNoise());
}

double GetBeaconAperture()
{
    assert(robLink!=0);
    return (robLink->beaconAperture());
}

unsigned int GetBeaconLatency()
{
    assert(robLink!=0);
    return (robLink->beaconLatency());
}

unsigned int GetGroundLatency()
{
    assert(robLink!=0);
    return (robLink->groundLatency());
}

unsigned int GetIRLatency()
{
    assert(robLink!=0);
    return (robLink->obstLatency());
}

unsigned int GetBumperLatency()
{
    assert(robLink!=0);
    return (robLink->collisionLatency());
}

bool GetBeaconRequestable()
{
    assert(robLink!=0);
    return (robLink->beaconRequestable());
}

bool GetGroundRequestable()
{
    assert(robLink!=0);
    return (robLink->groundRequestable());
}

bool GetIRRequestable()
{
    assert(robLink!=0);
    return (robLink->obstRequestable());
}

bool GetBumperRequestable()
{
    assert(robLink!=0);
    return (robLink->collisionRequestable());
}

void ReadMap(char *filename, void *vmap)
{
	/* set source of xml document */
	QXmlInputSource source(new QFile(filename));

	/* set parser handler */
    StructureParser handler(1); // 1 is dummy

	/* parse xml document with handler */
    QXmlSimpleReader reader;
    reader.setContentHandler(&handler);
    reader.parse(source);

	memcpy(vmap, handler.map, (CELLROWS*2-1)*(CELLCOLS*2-1));
}
