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
#ifndef _CIBER_ROBLINK_
#define _CIBER_ROBLINK_

#include <qobject.h>
#include <assert.h>

#include <stdarg.h>

#include "cmeasures.h"
#include "csimparam.h"
#include "netif.h"

#include "structureparser.h"

#include <iostream>

using std::cerr;

class CRobLink  
#ifdef CIBERQTAPP
: public QObject
#endif
{
#ifdef CIBERQTAPP
    Q_OBJECT
#endif
public:
    CRobLink(char *rob_name, int rob_id, char *host);
    CRobLink(char *rob_name, int rob_id, double IRSensorAngle[], char *host);
    CRobLink(char *rob_name, int rob_id, double height, char *host); // for RobotBeacon
    virtual ~CRobLink();
    //int ReadSensors();
    void DriveMotors(double lPow,double rPow);
    void Say(char * msg);
    void SetReturningLed(bool val);
    void SetVisitingLed(bool val);
    void Finish(void);

	inline int status() { return Status; }
	
	inline unsigned int time() { return measures.time; }
	inline bool   IRSensorReady(int i) { if(i>=0 && i < NUM_IR_SENSORS) return measures.IRSensorReady[i]; else return false;}
	inline double IRSensor(int id) { return measures.IRSensor[id]; }
	inline int    nBeacons(void) { 
		//cerr << "croblink::nBeacons = " << simParam.nBeacons << "\n";
		return simParam.nBeacons; }
	inline bool   beaconReady(unsigned int i) { if(i<simParam.nBeacons) return measures.beaconReady[i]; else return false;}
	inline struct beaconMeasure beacon(unsigned int i) { assert(i<simParam.nBeacons); return measures.beacon[i]; }
	inline bool   compassReady() { return measures.compassReady; }
	inline double compass() { return measures.compass; }
	inline bool   groundReady() { return measures.groundReady; }
	inline int    ground() { return measures.ground; }
	inline bool   collisionReady() { return measures.collisionReady; }
    inline bool   collision() { return measures.collision; }
	inline bool   scoreReady() { return measures.scoreReady; }
    inline int    score() { return measures.score; }
    inline bool   gpsReady() { return measures.gpsReady; }
    inline bool   gpsDirReady() { return measures.gpsDirReady; }
	inline bool   newMessage(int from) { return measures.hearMessage[from-1]!=QString(); }
	inline QString   message(int from) { return measures.hearMessage[from-1]; }

	void requestGround();
	void requestCompass();
	void requestBeacon(int id);
	void requestObstacle(int id);
	void requestSensors(int nReqs, va_list ap);

	inline bool start() { return measures.start; }
	inline bool stop() { return measures.stop; }
	inline bool endLed() { return measures.endLed; }
	inline bool returningLed() { return measures.returningLed; }
	inline bool visitingLed() { return measures.visitingLed; }

	inline int cycleTime() { return simParam.cycleTime; }
	inline int finalTime() { return simParam.simTimeFinal; }
	inline int keyTime() { return simParam.keyTime; }
	inline double beaconNoise() { return simParam.beaconNoise; }
	inline double compassNoise() { return simParam.compassNoise; }
	inline double motorsNoise() { return simParam.motorsNoise; }
	inline double obstacleNoise() { return simParam.obstNoise; }

	inline double beaconAperture() { return simParam.beaconAperture; }

	inline unsigned int nReqPerCycle() { return simParam.nReqPerCycle; }

	inline unsigned int compassLatency() { return simParam.compassLatency; }
	inline unsigned int groundLatency() { return simParam.groundLatency; }
	inline unsigned int obstLatency() { return simParam.obstLatency; }
	inline unsigned int collisionLatency() { return simParam.collisionLatency; }
	inline unsigned int beaconLatency() { return simParam.beaconLatency; }
	inline bool compassRequestable() { return simParam.compassRequestable; }
	inline bool groundRequestable() { return simParam.groundRequestable; }
	inline bool obstRequestable() { return simParam.obstRequestable; }
	inline bool collisionRequestable() { return simParam.collisionRequestable; }
	inline bool beaconRequestable() { return simParam.beaconRequestable; }

	inline double posx() { return measures.x; }
	inline double posy() { return measures.y; }
	inline double posdir() { return measures.dir; }

#ifdef CIBERQTAPP
signals:
    void NewMessage();
public slots:
#endif
    int ReadSensors();

protected:
     void send_register_message(char *robot_name, int robId);
     void send_register_message(char *robot_name, int robId, double IRSensorAngles[]);
     void send_robotbeacon_register_message(char *rob_name,int rob_id, double height);
     void parse_server_reply(void);

private:
	CMeasures measures;	// measures sent by simulator
	CSimParam simParam;	// simulation parameters sent after registration
    int Status;	

    Port port;			// communication port
  
};

#endif
