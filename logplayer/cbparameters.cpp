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

#include <stdio.h>
#include <stdlib.h>

cbParameters::cbParameters()
{
	motorsNoise = compassNoise = beaconNoise = obstacleNoise = 0.0;
	simTime = 2000;
	cycleTime = 75;
}

cbParameters::~cbParameters()
{
}

int cbParameters::toXml(char *buff, int len)
{
	int cnt = sprintf(buff, "<Parameters SimTime=\"%u\" CycleTime=\"%u\"\n"
			"\t\tCompassNoise=\"%g\" BeaconNoise=\"%g\" ObstacleNoise=\"%g\"\n"
			"\t\tMotorsNoise=\"%g\"/>\n", simTime, cycleTime, 
			compassNoise, beaconNoise, obstacleNoise, motorsNoise);

        if(cnt > len -1 ) {
                fprintf(stderr,"cbParameters::toXml message too long\n");
                abort();
        }

	return cnt;
}
