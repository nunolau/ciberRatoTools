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
#include "csimparam.h"

#include <iostream>
#include <math.h>

CSimParam::CSimParam()
{

	obstNoise=0.0; 
	beaconNoise=0.0; 
	motorsNoise=0.0; 
    compassNoise=0.0;
    simTimeFinal=1500;
    keyTime=1500;
	cycleTime=80;
	nBeacons=0;

	obstLatency=1; 
	beaconLatency=1; 
	groundLatency=1; 
	compassLatency=1;
	collisionLatency=1;

	nReqPerCycle = 2;

	obstRequestable=false; 
	beaconRequestable=false; 
	groundRequestable=false; 
	compassRequestable=false;
	collisionRequestable=false;

	beaconAperture = M_PI/3;
}

void CSimParam::showValues()
{
/*	cout.form("<Parameters");
	cout.form(" SimTime=\"%d\" CycleTime=\"%d\"\n", simTimeFinal, cycleTime);
	cout.form("\t\tObstacleNoise=\"%g\" BeaconNoise=\"%g\" CompassNoise=\"%g\"\n", 
				obstNoise, beaconNoise, compassNoise);
	cout.form("\t\tMotorsNoise=\"%g\"/>\n", motorsNoise);*/
}
