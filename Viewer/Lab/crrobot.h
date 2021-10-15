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

#ifndef CRROBOT_H
#define CRROBOT_H
/*! \class CRRobot
 *	\brief Implements a way to store the robot data in each object.
 *
 *	This is the robot class... It can be expanded so it can be used inside the
 *	simulator.
 */

#include"crvertice.h"
#define MAXROBOTNAME 25 /*!< defines the string size for the robots name */

class CRRobot
{
	public:
		/*! \enum States
		 * \brief Gives the possible robot states
		 */
		enum 	  States {STOPPED, RUNNING, WAITINGOTHERS, REMOVED, FINISHED, RETURNING};

		/*! This is the constructor.
		 */
		CRRobot( void );
	
		/*! This is the destructor.
		 */
		~CRRobot( void );
	
		/*! Sets the robot name.
		 * \param name a string with the robot name. The Maximum allowed
		 * size is MAXROBOTNAME.
		 * \sa name
		 */
		void setName( const char *name );

		/*! Returns the robot name.
		 * \sa setName
		 */
		char*  name( void );
	
		/*! Sets the robot id.
		 *  \param id an integer between 0 and grid.howManyElements().
		 * 	\sa howManyElements()
		 */
		void setId( int id );
	
		/*! Returns the robot id.
		 *  \param id an integer between 0 and grid.howManyElements().
		 * 	\sa howManyElements()
		 */
		int id( void );

		/*! Sets the robot X coordinate.
		 * \sa x
		 */
		void setX( float x );

		/*! Sets the robot Y coordinate.
		 * \sa y
		 */
		void setY( float y );

		/*! Sets the robot direction in degrees.
		 * \sa direction
		 */
		void setDirection( float direction );

		/*! Sets the number of collisions that occured.
		 * \param value is the collisions number.
		 * \sa collisions
		 */
		void setCollisions( unsigned value );
		
		/*! Set the collision state to the robot.
		 * \param collision YES or NO
		 */
		void setCollision( const char *collision );
		
		/*! Returns the number os collisions for this robot.
		 * \sa setCollisions( unsigned value )
		 */
		unsigned collisions( void );

		/*! Returns the state of collision (YES or NO)
		 */
		char* collision( void );

		/*! This is the X coordinate of the robot position.
		 * \sa setX
		 */
		float x( void );
		/*! This is the Y coordinate of the robot position.
		 * \sa setY
		 */
		float y( void );
		/*! Returns the current robot orientation (direction) in degrees.
		 * \sa setDirection
		 */
		float direction( void );

		/*! Sets or updates the robot score.
		 * \param score Any integer number.
		 * \sa score
		 */
		void setScore( int score );
		/*! Returns the current robot score.
		 * \sa setScore
		 */
		int score( void );

		/*! Sets the current simulation cycle.
		 * \param time the number of the current simulation cycle.
		 * \sa currentTime
		 */
		void setCurrentTime( int time );

		/*! Sets the current arrival time. This means the time that robot
		 * takes to finish the first goal!
		 * \param time The time passed.
		 * \sa arrivalTime
		 */
		void setArrivalTime( int time );

		/*! Sets the current return time. This means the time that robot
		 * takes to finish the second goal!
		 * \param time The time passed.
		 * \sa returnTime
		 */
		void setReturnTime( int time );

		/*! Returns the current simulation cycle (time).
		 * \sa setCurrentTime
		 */
		int currentTime( void );

		/*! Returns the arrival time.
		 * \sa setArrivalTime
		 */
		int arrivalTime( void );

		/*! Returns the return time.
		 * \sa setReturnTime
		 */
		int returnTime( void );

		/*! This changes the robot state.
		 * \param value can be one of the values in the States enum.
		 * \sa state
		 */
		void setState( States value );
		/*! Returns the current state.
		 * \sa setState
		 */
		States state( void );
        /*! Returns the current state as strin.
         * \sa setState
         */
        const char * stateAsString( void );

		
	private:

		char robotName[MAXROBOTNAME];
		char robotCollision[8];
		int  robotId;
		int  robotScore;
		int  robotCurrentTime;
		int  robotArrivalTime;
		int  robotReturnTime;

		CRVertice robotPosition;
		float	  robotDirection;
		unsigned 	  robotCollisions;
		States	  robotState;
		
};
#endif
