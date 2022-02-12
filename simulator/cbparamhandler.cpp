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
 * class cbParamHandler
 */
 
#include "cbparamhandler.h"

#include <qstring.h>

cbParamHandler::cbParamHandler(cbParameters *parStart)
{
	if(parStart!=0)
	   param = new cbParameters(*parStart);
	else
	   param = new cbParameters;
}
 
bool cbParamHandler::startDocument()
{
//	param = 0;
    return TRUE;
}

bool cbParamHandler::endDocument()
{
	return TRUE;
}

bool cbParamHandler::startElement( const QString&, const QString&, const QString& qName, 
                                    const QXmlAttributes& attr)
{
	/* process begin tag */
	const QString &tag = qName;

	if (param==0 && tag != "Parameters") return false;

	if (tag == "Parameters")
	{
//		param = new cbParameters;
		/* process attributes */
		const QString &simtime = attr.value(QString("SimTime"));
		if (!simtime.isNull()) param->simTime = simtime.toUInt();
		const QString &cycletime = attr.value(QString("CycleTime"));
		if (!cycletime.isNull()) param->cycleTime = cycletime.toUInt();
		const QString &keytime = attr.value(QString("KeyTime"));
		if (!keytime.isNull()) param->keyTime = keytime.toUInt();
		//Noise
		const QString &compassnoise = attr.value(QString("CompassNoise"));
		if (!compassnoise.isNull()) param->compassNoise = compassnoise.toDouble();
		const QString &beaconnoise = attr.value(QString("BeaconNoise"));
		if (!beaconnoise.isNull()) param->beaconNoise = beaconnoise.toDouble();
		const QString &obstaclenoise = attr.value(QString("ObstacleNoise"));
		if (!obstaclenoise.isNull()) param->obstacleNoise = obstaclenoise.toDouble();
		const QString &motorsnoise = attr.value(QString("MotorsNoise"));
		if (!motorsnoise.isNull()) param->motorsNoise = motorsnoise.toDouble();

        const QString &gps = attr.value(QString("GPS"));
        if (!gps.isNull())
        {
            if( gps == "On") param->GPSOn = true;
            else param->GPSOn = false;
        }

        const QString &beacon = attr.value(QString("BeaconSensor"));
        if (!beacon.isNull())
        {
            if( beacon == "On") param->beaconSensorOn = true;
            else param->beaconSensorOn = false;
        }
        const QString &compass = attr.value(QString("CompassSensor"));
        if (!compass.isNull())
        {
            if( compass == "On") param->compassSensorOn = true;
            else param->compassSensorOn = false;
        }
		const QString &gpsLinNoise = attr.value(QString("GPSLinNoise"));
		if (!gpsLinNoise.isNull()) param->gpsLinNoise = gpsLinNoise.toDouble();
		const QString &gpsDirNoise = attr.value(QString("GPSDirNoise"));
		if (!gpsDirNoise.isNull()) param->gpsDirNoise = gpsDirNoise.toDouble();

        const QString &scoreSensor = attr.value(QString("ScoreSensor"));
        if (!scoreSensor.isNull())
        {
            if( scoreSensor == "On") param->scoreSensorOn = true;
            else param->scoreSensorOn = false;
        }

		//Requests
		const QString &reqPCycle = attr.value(QString("NRequestsPerCycle"));
		if (!reqPCycle.isNull()) param->nReqPerCycle = reqPCycle.toUInt();
		const QString &obstacleRequestable = attr.value(QString("ObstacleRequestable"));
		if (!obstacleRequestable.isNull()) param->obstacleRequestable = (obstacleRequestable=="On"?true:false);
		const QString &beaconRequestable = attr.value(QString("BeaconRequestable"));
		if (!beaconRequestable.isNull()) param->beaconRequestable = (beaconRequestable=="On"?true:false);
		const QString &compassRequestable = attr.value(QString("CompassRequestable"));
		if (!compassRequestable.isNull()) param->compassRequestable = (compassRequestable=="On"?true:false);
		const QString &groundRequestable = attr.value(QString("GroundRequestable"));
		if (!groundRequestable.isNull()) param->groundRequestable = (groundRequestable=="On"?true:false);
		const QString &collisionRequestable = attr.value(QString("CollisionRequestable"));
		if (!collisionRequestable.isNull()) param->collisionRequestable = (collisionRequestable=="On"?true:false);

		//Latencies
		const QString &obstacleLatency = attr.value(QString("ObstacleLatency"));
		if (!obstacleLatency.isNull()) {
			param->obstacleLatency = obstacleLatency.toUInt();
		}
		const QString &beaconLatency = attr.value(QString("BeaconLatency"));
		if (!beaconLatency.isNull()) param->beaconLatency = beaconLatency.toUInt();
		const QString &compassLatency = attr.value(QString("CompassLatency"));
		if (!compassLatency.isNull()) param->compassLatency = compassLatency.toUInt();
		const QString &groundLatency = attr.value(QString("GroundLatency"));
		if (!groundLatency.isNull()) param->groundLatency = groundLatency.toUInt();
		const QString &collisionLatency = attr.value(QString("collisionLatency"));
		if (!collisionLatency.isNull()) param->collisionLatency = collisionLatency.toUInt();

		const QString &beaconAperture = attr.value(QString("BeaconAperture"));
		if (!beaconAperture.isNull()) param->beaconAperture = beaconAperture.toDouble();

        //Scores
        const QString &returnTimePenalty = attr.value(QString("ReturnTimePenalty"));
        if (!returnTimePenalty.isNull()) param->returnTimePenalty = returnTimePenalty.toInt();
        const QString &arrivalTimePenalty = attr.value(QString("ArrivalTimePenalty"));
        if (!arrivalTimePenalty.isNull()) param->arrivalTimePenalty = arrivalTimePenalty.toInt();
        const QString &collisionWallPenalty = attr.value(QString("CollisionWallPenalty"));
        if (!collisionWallPenalty.isNull()) param->collisionWallPenalty = collisionWallPenalty.toInt();
        const QString &collisionRobotPenalty = attr.value(QString("CollisionRobotPenalty"));
        if (!collisionRobotPenalty.isNull()) param->collisionRobotPenalty = collisionRobotPenalty.toInt();
        const QString &targetReward = attr.value(QString("TargetReward"));
        if (!targetReward.isNull()) param->targetReward = targetReward.toInt();
        const QString &homeReward = attr.value(QString("HomeReward"));
        if (!homeReward.isNull()) param->homeReward = homeReward.toInt();

		const QString &labfn = attr.value(QString("Lab"));
		if (!labfn.isNull()) param->labFilename = labfn;
		const QString &gridfn = attr.value(QString("Grid"));
		if (!gridfn.isNull()) param->gridFilename = gridfn;

	}
    return TRUE;
}

bool cbParamHandler::endElement( const QString&, const QString&, const QString& qName)
{
	/* process end tag */
	const QString &tag = qName;
	if (tag == "Parameters")
	{
	}
    return TRUE;
}

void cbParamHandler::setDocumentLocator(QXmlLocator *)
{
}


/* extra functions */

cbParameters *cbParamHandler::parsedParameters()
{
	return param;
}
