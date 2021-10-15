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

#ifndef CB_ROBOT_ACTION_H
#define CB_ROBOT_ACTION_H

#include <vector>
#include <qstring.h>

using std::vector;

/**
  *@author Nuno Lau, Artur Pereira & Andreia Melo
  */

/**
 * models the action of a robot
 */
class cbRobotAction
{
public:
    cbRobotAction(){leftMotor=0.0;rightMotor=0.0;endLed=false;returningLed=false;
                    leftMotorChanged=false;rightMotorChanged=false;
                    endLedChanged=false;returningLedChanged=false;visitingLedChanged=false;}

    void reset(void);

public: // data members
	double leftMotor, rightMotor;
	bool endLed, returningLed, visitingLed;
	bool leftMotorChanged, rightMotorChanged, 
             endLedChanged, returningLedChanged, 
             visitingLedChanged, sayReceived;

	vector<QString> sensorRequests;

        QString sayMessage;
};

#endif
