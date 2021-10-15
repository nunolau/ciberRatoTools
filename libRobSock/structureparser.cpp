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
$Id: structureparser.cpp,v 1.5 2005/02/17 11:09:23 lau Exp $
*/

#include "structureparser.h"

#include <iostream>
#include <qstring.h>

using std::cerr;

static bool readAttributeInt(const QXmlAttributes &attr, const char *attrName, int *var)
{
	const QString &attrVal = attr.value(QString(attrName));
	if (!attrVal.isNull()) {
		*var = attrVal.toInt();
		return true;
	}
	return false;
}

static bool readAttributeUInt(const QXmlAttributes &attr, const char *attrName, unsigned int *var)
{
	const QString &attrVal = attr.value(QString(attrName));
	if (!attrVal.isNull()) {
		*var = attrVal.toUInt();
		return true;
	}
	return false;
}

static bool readAttributeDouble(const QXmlAttributes &attr, const char *attrName, double *var)
{
	const QString &attrVal = attr.value(QString(attrName));
	if (!attrVal.isNull()) {
		*var = attrVal.toDouble();
		return true;
	}
	return false;
}

static bool readAttributeBool(const QXmlAttributes &attr, const char *attrName, bool *var,
		              const char *strTrue, const char *strFalse)
{
	const QString &attrVal = attr.value(QString(attrName));
	if (!attrVal.isNull())
	{
		if (attrVal == strTrue ) {
			*var = true;
			return true;
		}
		else if (attrVal == strFalse) {
			*var = false;
		        return true;
	        }
		else return false;
	}
	return false;
}

static bool readAttributeBoolOnOff(const QXmlAttributes &attr, const char *attrName, bool *var)
{
	return readAttributeBool(attr, attrName, var, "On", "Off");
}

static bool readAttributeBoolYesNo(const QXmlAttributes &attr, const char *attrName, bool *var)
{
	return readAttributeBool(attr, attrName, var, "Yes", "No");
}

bool StructureParser::startDocument()
{
    //cout.form("-------------------- startDocument() called\n");
    return TRUE;
}

bool StructureParser::endDocument()
{
    //cout.form("-------------------- endDocument() called\n");
	return TRUE;
}

bool StructureParser::startElement(const QString&, const QString&, 
                                   const QString& qName, 
                                   const QXmlAttributes& attr)
{
    //cout.form("-------------------- startElement(...) called\n");
    
	//cerr << "StartElement qName=" << qName << "\n";

	/* process begin tag */
	const QString &tag = qName;
        activeTag=tag;
	if (tag == "Reply")
	{
		/* process attributes */
		const QString &status = attr.value(QString("Status"));
		if (!status.isNull())
		{
			if (status == "Ok")
				return true;
			else if (status == "Refused")
				return false;
		}
		return false;
	}
	else if (tag == "Parameters")
	{
		/* process attributes */
		//Noise
		readAttributeDouble(attr,"CompassNoise", &simParam.compassNoise);
		readAttributeDouble(attr, "BeaconNoise", &simParam.beaconNoise);
		readAttributeDouble(attr, "ObstacleNoise", &simParam.obstNoise);
		readAttributeDouble(attr, "MotorsNoise", &simParam.motorsNoise);
		
		//Time
		readAttributeUInt(attr, "SimTime", &simParam.simTimeFinal);
		readAttributeUInt(attr, "KeyTime", &simParam.keyTime);
		readAttributeUInt(attr, "CycleTime", &simParam.cycleTime);
		
		//NBeacons
		readAttributeUInt(attr, "NBeacons", &simParam.nBeacons);

		//Requests per Cycle
		readAttributeUInt(attr, "RequestsPerCycle", &simParam.nReqPerCycle);
		//Requestables
		readAttributeBoolOnOff(attr, "ObstacleRequestable", &simParam.obstRequestable);
		readAttributeBoolOnOff(attr, "BeaconRequestable", &simParam.beaconRequestable);
		readAttributeBoolOnOff(attr, "GroundRequestable", &simParam.groundRequestable);
		readAttributeBoolOnOff(attr, "CompassRequestable", &simParam.compassRequestable);
		readAttributeBoolOnOff(attr, "CollisionRequestable", &simParam.collisionRequestable);

		//Latencies
		readAttributeUInt(attr, "ObstacleLatency",  &simParam.obstLatency);
		readAttributeUInt(attr, "BeaconLatency",    &simParam.beaconLatency);
		readAttributeUInt(attr, "GroundLatency",    &simParam.groundLatency);
		readAttributeUInt(attr, "CompassLatency",   &simParam.compassLatency);
		readAttributeUInt(attr, "CollisionLatency", &simParam.collisionLatency);

		readAttributeDouble(attr, "BeaconAperture", &simParam.beaconAperture);

	}
	else if (tag == "Measures")
	{
		/* process attributes */
		readAttributeUInt(attr, "Time", &measures.time);
	}
	else if (tag == "Sensors")
	{
		/* process attributes */
		measures.compassReady =   readAttributeDouble(attr, "Compass", &measures.compass);
		measures.collisionReady = readAttributeBoolYesNo(attr, "Collision", &measures.collision);
		measures.groundReady =    readAttributeInt(attr, "Ground", &measures.ground);
	}

	else if (tag == "IRSensor")
	{
		/* process attributes */
		const QString &idStr = attr.value(QString("Id"));
		if (!idStr.isNull()) {
			unsigned int id = idStr.toUInt();

			if(id < NUM_IR_SENSORS) {
			    measures.IRSensorReady[id] = readAttributeDouble(attr, "Value", &measures.IRSensor[id]);
			}
			else return false;
		}
		else return false;

		
	}
	else if (tag == "BeaconSensor")
	{
		/* process attributes */
		const QString &idStr = attr.value(QString("Id"));
		if (!idStr.isNull()) {
			unsigned int id = idStr.toUInt();
			//cerr << "tagBeaconSensor got " << id;
			if(id<measures.beaconReady.size()) {
			    measures.beaconReady[id]=true; 
		            const QString &valueStr = attr.value(QString("Value"));
			    if(!valueStr.isNull()) {
			        if(valueStr=="NotVisible") {
			            //cerr << "not visible";
			            measures.beacon[id].beaconVisible = false;
			            measures.beacon[id].beaconDir = 0.0;
			        }
			        else{
			            measures.beacon[id].beaconDir = valueStr.toDouble();
			            measures.beacon[id].beaconVisible = true;
			            //cerr << " at " << measures.beacon[id].beaconDir;
			        }

			    }
			    else return false;
			}
			//cerr << "\n";
		}
		else return false;
	}
	else if (tag == "GPS")
	{
		/* process attributes */
		measures.gpsReady = readAttributeDouble(attr, "X", &measures.x);
		readAttributeDouble(attr, "Y", &measures.y);
		measures.gpsDirReady = readAttributeDouble(attr, "Dir", &measures.dir);
	}
	else if (tag == "Leds")
	{
		readAttributeBoolOnOff(attr, "EndLed", &measures.endLed);
		readAttributeBoolOnOff(attr, "ReturningLed", &measures.returningLed);
		readAttributeBoolOnOff(attr, "VisitingLed", &measures.visitingLed);
	}
	else if (tag == "Buttons")
	{
		readAttributeBoolOnOff(attr, "Start", &measures.start);
		readAttributeBoolOnOff(attr, "Stop", &measures.stop);
	}
	else if (tag == "Score")
	{
		measures.scoreReady         = readAttributeUInt(attr, "Score", &measures.score);
		measures.arrivalTimeReady   = readAttributeUInt(attr, "ArrivalTime", &measures.arrivalTime);
		measures.returningTimeReady = readAttributeUInt(attr, "ReturningTime", &measures.returningTime);
		measures.collisionsReady    = readAttributeUInt(attr, "Collisions", &measures.collisions);
	}
	else if (tag == "Message")
    {
		readAttributeUInt(attr, "From", &hearFrom);
    }
	else if (tag == "Row")
    {
        int row;
		readAttributeInt(attr, "Pos", &row);
		const QString &pattern = attr.value(QString("Pattern"));
        const QChar *spec = pattern.data();
        int col=0;
		while (!spec->isNull()) {
            if(row % 2 == 0) { // only vertical walls are allowed here
                if(spec->toAscii()=='|') {                 
                    map[row][(col+1)/3*2-1] = '|';
                }
            }
            else {// only horizontal walls are allowed at odd rows 
                if(col % 3 == 0) { // if there is a wall at this collumn then there must also be a wall in the next one
                    if(spec->toAscii()=='-') {  
                        map[row][col/3*2] = '-';
                    }
    
                }
            }
            spec++;
            col++;
        }
    }
    return true;
}

bool StructureParser::endElement( const QString&, const QString&, const QString& qName)
{
    //cout.form("-------------------- endElement(...) called\n");
    
	//cerr << "endElement qName=" << qName << "\n";

	
	/* process end tag */
	const QString &tag = qName;
        activeTag="";
	if (tag == "Reply")
	{
	}
	else if (tag == "Sensors")
	{
	}
	else if (tag == "Measures")
	{
	}
    return TRUE;
}

bool StructureParser::characters(const QString& data)
{
    //cout.form("-------------------- characters(...) called\n");
    if(activeTag=="Message" ) {
            //fprintf(stderr,"characters: tag=%s hearFrom=%d data=\"%s\"\n",activeTag.latin1(), hearFrom, data.latin1());
            measures.hearMessage[hearFrom-1]+=data;
    }
    return TRUE;
}

bool StructureParser::startCDATA()
{
    fprintf(stderr,"startCDATA\n");
    cdata=true;
    return TRUE;
}

bool StructureParser::endCDATA()
{
    fprintf(stderr,"endCDATA\n");
    cdata=false;
    return TRUE;
}

void StructureParser::setDocumentLocator(QXmlLocator *)
{
    //cout.form("-------------------- setDocumentLocator(...) called\n");
}
