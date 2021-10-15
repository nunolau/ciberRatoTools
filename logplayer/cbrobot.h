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

#ifndef CBROBOT_H
#define CBROBOT_H

#include <qstring.h>
#include "cbposition.h"

/**
  *@author Nuno Lau, Artur Pereira & Andreia Melo, Miguel Rodrigues
  */

#define MAX_POWER 0.1

#define ROBOT_RADIUS 0.5

class cbLogplayer;

class cbRobot
{
public:
	enum State {STOPPED=0, RUNNING, WAITINGOTHERS, RETURNING, FINISHED, REMOVED};
	cbRobot();
	virtual ~cbRobot();

	void setName(const char *name);
	const char *Name();
	void setId(unsigned int id);
	void setTime(unsigned int time) { simTime=time; };
	unsigned int Id();

	inline void setLogplayer(cbLogplayer *l) { logplayer = l; }

	void setLeftMotor(double);
	void setRightMotor(double);
        inline void setEndLed(bool l) { recEndLed=true; endLed = l; }
        void setReturningLed(bool l); 

        void resetReceivedFlags(void); 
        inline bool receivedLeftMotor(void) { return recLeftMotor; }; 
        inline bool receivedRightMotor(void) { return recRightMotor; }; 
        inline bool receivedEndLed(void) { return recEndLed; }; 
        inline bool receivedReturningLed(void) { return recReturningLed; }; 
        inline bool receivedAction(void) { return recReturningLed || recEndLed || recLeftMotor || recRightMotor; }; 

	inline bool endLedOn() { return endLed; }
	inline bool returningLedOn() { return returningLed; }

	inline void remove() { removed = true; }
	inline bool isRemoved() { return _state == REMOVED; }
	inline bool hasFinished() { return _state == FINISHED; }
	inline bool active() { return _state == STOPPED || 
                                      _state == RUNNING || 
                                      _state == RETURNING; }
	inline bool blocked() { return _state == STOPPED || _state == FINISHED; }
	void changeActiveState();

	inline void resetCollision() { collision = false; }
	inline void setCollision()   { collision = true; }
	inline bool hasCollide() { return collision; }

//	inline void setOnTarget(bool v) { onTarget = v; }
	bool isOnTarget();

	inline cbPoint &Center() { return curPos.Coord(); }

	inline double X() { return curPos.X(); }
	inline double Y() { return curPos.Y(); }
	inline double Dir() { return curPos.Direction(); }
	inline double Degrees() { return Dir() * 180 / M_PI; }

	inline cbPosition &position() { return curPos; }
	inline void setPosition(cbPosition &pos) { curPos = pos; }

	inline unsigned int Score() { return score; }
	void setScore(unsigned int s) { score=s; }
	inline unsigned int ArrivalTime() { return arrivalTime; }
	void setArrivalTime(unsigned int at) { arrivalTime=at; }
	inline unsigned int ReturningTime() { return returningTime; }
	void setReturningTime(unsigned int at) { returningTime=at; }
	inline unsigned int CollisionCount() { return collisionCount; }
	void setCollisionCount(unsigned int cc) { collisionCount=cc; }
	void setVisitedMask(QString vm) { visitedMask=vm; }

	unsigned int toXml(char *, unsigned int);

	inline State state() { return _state; }
	void   setState(const char *stateStr);

	void showAllAttributes();

protected:
	const char *name;
	unsigned int id;

	unsigned int score, scorePenalties, arrivalTime, returningTime, simTime;
	double distAtArrival;
	QString visitedMask;

	State _state;		// current state of robot
	State _unstoppedState;	// state of robot before stopped

        bool returningLed;
	bool endLed;

        bool recLeftMotor, recRightMotor, recReturningLed, recEndLed;

	bool removed;	// indicates that robot has been removed

	cbLogplayer *logplayer;

	cbPosition curPos;	// current position of robot
	double vel;	        // pretended linear velocity of robot 
	bool collision;		// indicates that next position results in a collision
	unsigned int collisionCount;	// number of collisions
};

#endif
