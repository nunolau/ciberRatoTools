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


#include <string.h>
#include <iostream>
#include"crrobot.h"

using namespace std;

CRRobot::CRRobot( void )
{
	setName( "Player" );
	setCollision( "False" );
	setId( 0 );
	setScore( 0 );
	setCollisions( 0 );
	setX( 0.0 );
	setY( 0.0 );
	setDirection( 0.0 );
	setCurrentTime( 0 );
}

CRRobot::~CRRobot( void )
{}

void CRRobot::setName( const char *name )
{
	strcpy(robotName, name);
}

char* CRRobot::name( void )
{
	return robotName;
}

void CRRobot::setId( int id )
{
	robotId = id;
}

int CRRobot::id( void )
{
	return robotId;
}

void CRRobot::setX( float x )
{
	robotPosition.setX( x );
}

void CRRobot::setY( float y )
{
	robotPosition.setY( y );
}

void CRRobot::setDirection( float direction )
{
	robotDirection = direction;
}

void CRRobot::setCollisions( unsigned value )
{
	robotCollisions = value;
}

void CRRobot::setCollision( const char *collision )
{
	strcpy(robotCollision, collision);
}

unsigned CRRobot::collisions( void )
{
	return robotCollisions;
}

char* CRRobot::collision( void )
{
	return robotCollision;
}

float CRRobot::x( void )
{
	return robotPosition.x();
}

float CRRobot::y( void )
{
	return robotPosition.y();
}

float CRRobot::direction( void )
{
	return robotDirection;
}

void CRRobot::setScore( int score )
{
	robotScore = score;
}

int CRRobot::score( void )
{
	return robotScore;
}

void CRRobot::setCurrentTime( int time )
{
	robotCurrentTime = time;
}

int CRRobot::currentTime( void )
{
	return robotCurrentTime;
}

void CRRobot::setArrivalTime( int time )
{
	robotArrivalTime = time;
}

int CRRobot::arrivalTime( void )
{
	return robotArrivalTime;
}

void CRRobot::setReturnTime( int time )
{
	robotReturnTime = time;
}

int CRRobot::returnTime( void )
{
	return robotReturnTime;
}

void CRRobot::setState( States value )
{
	robotState = value;
}

CRRobot::States CRRobot::state( void )
{
	return robotState;
}

const char * CRRobot::stateAsString( void )
{
    static const char *strState[] =
    {
        "Stopped", "Running", "Waiting", "Removed", "Finished", "Returning"
    };

    return strState[state()];
}
