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
/*
 * cbParameters.cpp
 */

#include "cbparameters.h"
#include "cbmotor.h"
#include "cbsensor.h"
#include "cbrobot.h"

#include <stdio.h>
#include <stdlib.h>

cbParameters::cbParameters()
{
    // WARNING: Most of These value may be overwriten by the ones provided in XML
    //          by the default parameters file in cbsimulator.cpp
        
	simTime         = 2000;   
	cycleTime       = 50;     
	keyTime         = 1500;  
	GPSOn           = cbRobot::GPSOn;
	beaconSensorOn  = cbRobot::beaconSensorOn;
	compassSensorOn = cbRobot::compassSensorOn;
	scoreSensorOn   = cbRobot::scoreSensorOn;
	showActions     = cbRobot::showActions;

	//Noise
	motorsNoise           = cbMotor::noise;
    compassNoise          = cbCompassSensor::noise;
    beaconNoise           = cbBeaconSensor::noise;
    obstacleNoise         = cbIRSensor::noise;
    gpsLinNoise           = cbGPSSensor::noiseLin;
    gpsDirNoise           = cbGPSSensor::noiseAng;

	//Requests
	nReqPerCycle=4;
	obstacleRequestable   = cbIRSensor::sensorRequestable; 
	beaconRequestable     = cbBeaconSensor::sensorRequestable; 
	compassRequestable    = cbCompassSensor::sensorRequestable; 
	groundRequestable     = cbGroundSensor::sensorRequestable;
	collisionRequestable  = cbCollisionSensor::sensorRequestable;
	gpsRequestable        = cbGPSSensor::sensorRequestable;

	//Latencies
	obstacleLatency    = cbIRSensor::sensorLatency; 
	beaconLatency      = cbBeaconSensor::sensorLatency; 
	compassLatency     = cbCompassSensor::sensorLatency; 
	groundLatency      = cbGroundSensor::sensorLatency;
	collisionLatency   = cbCollisionSensor::sensorLatency;
	gpsLatency         = cbGPSSensor::sensorLatency;

	beaconAperture = cbBeaconSensor::sensorAperture;

    //Scores
    returnTimePenalty = cbRobot::returnTimePenalty;
    arrivalTimePenalty = cbRobot::arrivalTimePenalty;
    collisionWallPenalty = cbRobot::collisionWallPenalty;
    collisionRobotPenalty = cbRobot::collisionRobotPenalty;
    targetReward = cbRobot::targetReward;
    homeReward = cbRobot::homeReward;
}

cbParameters::~cbParameters()
{
}

int cbParameters::toXml(char *buff, int len)
{
	int cnt = sprintf(buff, "<Parameters SimTime=\"%u\" CycleTime=\"%u\"\n"
			"\t\tCompassNoise=\"%g\" BeaconNoise=\"%g\" ObstacleNoise=\"%g\"\n"
			"\t\tMotorsNoise=\"%g\" KeyTime=\"%u\"\n"
			"\t\tGPS=\"%s\" GPSLinNoise=\"%g\" GPSDirNoise=\"%g\" \n"
			"\t\tBeaconSensor=\"%s\" \n"
			"\t\tCompassSensor=\"%s\" \n"
                        "\t\tScoreSensor=\"%s\" ShowActions=\"%s\" NBeacons=\"%d\" \n",
			simTime, cycleTime, 
			compassNoise, beaconNoise, obstacleNoise, motorsNoise,
			keyTime, (GPSOn?"On":"Off"), gpsLinNoise, gpsDirNoise,
			(beaconSensorOn?"On":"Off"),
			(compassSensorOn?"On":"Off"),
                        (scoreSensorOn?"On":"Off"),(showActions?"True":"False"),
			nBeacons);

	cnt = cnt + sprintf(buff+cnt, 
			"\t\tNRequestsPerCycle=\"%d\" \n"
			"\t\tObstacleRequestable=\"%s\" BeaconRequestable=\"%s\" \n"
			"\t\tGroundRequestable=\"%s\" CompassRequestable=\"%s\"\n"
			"\t\tCollisionRequestable=\"%s\"\n",
			nReqPerCycle,
			(obstacleRequestable?"On":"Off"), (beaconRequestable?"On":"Off"),
			(groundRequestable?"On":"Off"), (compassRequestable?"On":"Off"),
			(collisionRequestable?"On":"Off"));

	cnt = cnt + sprintf(buff+cnt, 
			"\t\tObstacleLatency=\"%d\" BeaconLatency=\"%d\" \n"
			"\t\tGroundLatency=\"%d\" CompassLatency=\"%d\"\n"
			"\t\tCollisionLatency=\"%d\"\n",
			obstacleLatency, beaconLatency,
			groundLatency, compassLatency, collisionLatency);

	cnt = cnt + sprintf(buff+cnt, 
			"\t\tBeaconAperture=\"%f\"\n",
			beaconAperture);

    cnt = cnt + sprintf(buff+cnt,
            "\t\tReturnTimePenalty=\"%d\" ArrivalTimePenalty=\"%d\" \n"
            "\t\tCollisionWallPenalty=\"%d\" CollisionRobotPenalty=\"%d\" \n"
            "\t\tTargetReward=\"%d\" HomeReward=\"%d\"\n",
            returnTimePenalty, arrivalTimePenalty,
            collisionWallPenalty, collisionRobotPenalty,
            targetReward, homeReward);

    if(!labFilename.isNull())
        cnt = cnt + sprintf(buff + cnt, "\t\tLab=\"%s\"\n", labFilename.toLatin1().constData());;
    if(!gridFilename.isNull())
        cnt = cnt + sprintf(buff + cnt, "\t\tGrid=\"%s\"\n", gridFilename.toLatin1().constData());;

	cnt = cnt + sprintf(buff + cnt, "/>\n"); 

    if(cnt > len -1 ) {
        fprintf(stderr,"cbParameters::toXml message too long\n");
        abort();
    }
	return cnt;
}
