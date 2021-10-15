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
#ifndef _CIBER_MEASURES_
#define _CIBER_MEASURES_

#include "RobSock.h"
#include <vector>
#include <QString>

#define NUM_IR_SENSORS 4

using std::vector;

class CMeasures
{
public:
    CMeasures(int nBeacons);
	void showValues();

public:
    bool    compassReady;
    double  compass; 
    bool    IRSensorReady[NUM_IR_SENSORS];
    double  IRSensor[NUM_IR_SENSORS]; 
    vector <bool>   beaconReady;
    vector <struct beaconMeasure> beacon; 
    unsigned int 	time;

    bool    groundReady;
    int     ground;
    bool    collisionReady;
    bool    collision, 
			start, 
			stop, 
			endLed,
			returningLed,
			visitingLed;
    double x,y,dir;

    bool scoreReady;
    unsigned int score;
    bool arrivalTimeReady;
    unsigned int arrivalTime;
    bool returningTimeReady;
    unsigned int returningTime;
    bool collisionsReady;
    unsigned int collisions;
    bool gpsReady;
    bool gpsDirReady;


    QString  hearMessage[10];
};

#endif
