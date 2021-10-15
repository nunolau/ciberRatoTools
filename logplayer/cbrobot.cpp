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

#include "cbrobot.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

using std::cerr;
using std::cout;

cbRobot::cbRobot() 
{
	name = "Demo";
	id = 0;
	simTime=0;
	score = 0;
	scorePenalties=0;
	arrivalTime=0;
	returningTime=0;
	distAtArrival=0.0;

	collision = false;
	collisionCount = 0;

	_state = STOPPED;
	_unstoppedState = RUNNING;
	removed=false;

	endLed = false;
        returningLed=false;

	vel=0.0;

}

cbRobot::~cbRobot()
{
}

void cbRobot::setName(const char *nm)
{
	name = strdup(nm);
}

const char *cbRobot::Name()
{
	return name;
}

void cbRobot::setId(unsigned int theId)
{
	id = theId;
}

unsigned int cbRobot::Id()
{
	return id;
}

void cbRobot::setReturningLed(bool l)
{ 
    recReturningLed=true;

    returningLed=l;
}

void cbRobot::resetReceivedFlags(void)
{ 
    recLeftMotor=recRightMotor=recReturningLed=recEndLed=false;
}

void cbRobot::changeActiveState()
{
	if (_state == RUNNING) _state = STOPPED;
	else if (_state == STOPPED) _state = RUNNING;
}

	static const char *StrState[] =
	{
		"Stopped", "Running", "Waiting", "Returning", "Finished", "Removed"
	};


/*!
	Fill in given xml buffer with robot state, that is, name, id, 
	score, number of collisions, the collision state, removed states, and current position.
	Return the length of the xml message.
*/
unsigned int cbRobot::toXml(char *xml, unsigned int len) // len = buffer size not used
{
	unsigned int n;
	n = sprintf(xml, "<Robot");
	/* add attributes */
	n += sprintf(xml+n, " Name=\"%s\"", name);
	n += sprintf(xml+n, " Id=\"%d\"", id);
	n += sprintf(xml+n, " Time=\"%u\"", simTime);
	n += sprintf(xml+n, " Score=\"%u\"", score);
	n += sprintf(xml+n, " ArrivalTime=\"%u\"", arrivalTime);
	n += sprintf(xml+n, " ReturningTime=\"%u\"", returningTime);
	n += sprintf(xml+n, " Collisions=\"%u\"", collisionCount);
	n += sprintf(xml+n, " Collision=\"%s\"", collision ? "True" : "False");
        n += sprintf(xml+n, " VisitedMask=\"%s\"",visitedMask.toAscii().constData());
	n += sprintf(xml+n, " State=\"%s\">\n", StrState[_state]);

	/* add position */
	double dir = curPos.directionInDegrees();
	n += sprintf(xml+n, "\t<Position X=\"%g\" Y=\"%g\" Dir=\"%g\"/>\n", curPos.X(), 
			curPos.Y(), dir);
	n += sprintf(xml+n, "</Robot>\n");

        if(n > len - 1) {
              fprintf(stderr, "cbRobot::toXml message is too long\n");
              abort();
        }

//	fprintf(stderr,"Robot : %s\n",xml);

	return n;
}


void cbRobot::setState(const char *newStateStr)
{
	unsigned int i;
	for(i=0;i<sizeof(StrState)/4;i++)
		if(strcmp(newStateStr,StrState[i])==0) break;
	_state=cbRobot::State(i);
}
