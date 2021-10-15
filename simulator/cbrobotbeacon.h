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

#ifndef CBROBOTBEACON_H
#define CBROBOTBEACON_H

#include <iostream>

#include "cbrobot.h"
#include "cbbeacon.h"

using std::ostream;

/**
  *@author Nuno Lau, Artur Pereira & Andreia Melo
  */

/**
 * This class represents the robot state (name, position, score, actions, 
 * sensors, etc) inside the simulator.
 */
class cbRobotBeacon : public cbRobot, public cbBeacon
{
public:
	cbRobotBeacon(const double irSensorAngles[NUM_IR_SENSORS]);
	virtual ~cbRobotBeacon();

        cbPoint &Center();

	void Log(ostream &Log, bool withactions=true);

protected:

};

#endif
