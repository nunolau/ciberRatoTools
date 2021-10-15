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
#include "cmeasures.h"

#include <iostream>

CMeasures::CMeasures(int nBeacons) : beaconReady(nBeacons), beacon(nBeacons)
{
	time = 0;

	ground    = -1;
	compass   = 0.0;
	collision = false;

	for(int b=0;b<nBeacons;b++)
	{
		beaconReady[b]=false;
		beacon[b].beaconVisible=false;
		beacon[b].beaconDir=0.0;
	}

	for(int i=0;i<NUM_IR_SENSORS;i++)
	{
		IRSensor[i] = 0.0;
		IRSensorReady[i]=false;
	}

	compassReady=false;
	groundReady=false;
    collisionReady=false;
    gpsReady=false;
    gpsDirReady=false;
    scoreReady = arrivalTimeReady = returningTimeReady = collisionsReady =false;
    score=0;
    arrivalTime=0;
    returningTime=0;
    collisions=0;
}

void CMeasures::showValues()
{
/*	cout.form("<Measures Time=\"%u\">\n", time);
	cout.form("\t<Sensors Compass=\"%g\" Beacon=\"%g\"\n", compass, beacon);
	cout.form("\t\t\tCollision=\"%s\" Ground=\"%s\">\n", collision?"On":"Off", ground?"On":"Off");
	cout.form("\t\t<IRSensors Left=\"%g\" Center=\"%g\" Right=\"%g\"/>\n",
				IRSensor[1], IRSensor[0], IRSensor[2]);
	cout.form("\t</Sensors>\n");
	cout.form("\t<Buttons Start=\"%s\" Stop=\"%s\"/>\n", start?"On":"Off", stop?"On":"Off");
	cout.form("\t<Leds EndLed=\"%s\"/>\n", endLed?"On":"Off");
	cout.form("</Measures>\n");
*/
}
