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

#ifndef CRLAB_H
#define CRLAB_H
#include"crvertice.h"
#include"crwall.h"
#include"crtarget.h"
#include"crbeacon.h"
#include"crgrid.h"
#include"crrobot.h"
#include<vector>
#include<iostream>

using namespace std;

#define MAXLABNAME 25

/*! \class CRLab 
 *  \brief This class stores the real information about the lab. This
 *  information includes the name, the units, etc.
 *
 *  Each lab may contain the following: walls, robots, grid, target and a
 *  beacon.
 *  All items may be changed, deleted, created, without the need to destroy
 *  the lab itself.
 *  It is also possible to cleanup the lab without destroing it.
 *
 *  \sa CRWall
 *  \sa CRRobot
 *  \sa CRGrid
 *  \sa CRTarget
 *  \sa CRBeacon
 * 
 */
class CRLab
{
public:
	/*! Contructor for the old file format.
	 *  Not used anymore.
	 *  \param file The file stream to be opened.
	 */
	CRLab( istream *file );

	/*! Constructor for the empty lab.
	 */
	CRLab( );

	/*! Destructor. */
	~CRLab( ); 

	/*! newLab cleans the lab by removing all the items from
	 * the vectors and setting the default values for the vars.
	 */
	int newLab();

	/*! loadLabFile loads a file in the old file format. It's here but it's not
	 * used anymore.
	 * \param file The file stream to be opened.
	 */
    int loadLabFile( istream *file );  

	/*! saveLabFile saves the current lab to a file. Not implemented!
	 * 	\param file The file to be saved.
	 */
    int saveLabFile( istream *file );  
 
	/*! addWall adds a wall in the complex format of vector and height.
	 * We recomend using the other function because its more easy to use.
	 * \param points A vector of CRVertices.
	 * \param wallHeight the wall height to be compared with the beacon height.
	 * \sa CRVertice
	 */
    int addWall( vector<CRVertice> *points, float wallHeight=0.0 );   

	/*! addWall adds a previously created wall. It's easy to use by a parser
	 * than the other addWall function.
	 * \param wall A wall object.
	 * \sa CRWall
	 */
    int addWall( CRWall *wall );							

	/*! addBeacon adds a beacon to the lab.
	 * \param pos The beacon position.
	 * \param beaconHeight The beacon height.
	 */
    int addBeacon( CRVertice pos , float beaconHeight=1.0 ); 

	/*! addGrid adds a grid object to the lab. By default an empty lab will
	 * have 3 grid positions but it can by changed by this object.
	 * \param startGrid The grid object.
	 * \sa CRGrid
	 */
    int addGrid( CRGrid *startGrid );       

	/*! addTarget specifies where the robots should stop.
	 * \param pos  marks the spot.
	 * \param radius defines the area of a circle.
	 * \sa CRVertice
	 */
	int addTarget ( CRVertice pos, float radius=2.0 );
	
	/*! addRobot adds a robot to the lab. Be careful not to add more robots 
	 * than the number defined by the grid or 3 by default.
	 * \param robot is the robot object.
	 * \sa CRRobot
	 */
	int addRobot ( CRRobot *robot ); 

	/*! setSize defines the lab size .
	 * \param size as two values x() == Width and y() == Height.
	 * \sa CRVertice
	 */
	int setSize( CRVertice size );

	/*! setHeight redefines the y() value of the lab size.
	 * \param height is the lab height.
	 */
	int setHeight( float height );

	/*! setWidth redefines the x() value of the lab size.
	 * \param width is the lab width.
	 */
	int setWidth( float width );

	/*! setName is used to name the lab. It can be anything to a max of
	 * MAXLABNAME size.
	 * \param name is a pointer to the name.
	 */
	int setName( const char *name );

	/*! setUnits is used to define the lab units. It can be anything because 
	 * the dimentions are floats. Another simple explanation: It is just a
	 * string.
	 *
	 * \param string is a pointer to the units string.
	 */
	int setUnits( char *string );
		
	/*! wallListRef() returns one pointer to the walls vector.
	 */
	vector<CRWall>    *wallListRef(); 
	/*! grid() Returns one pointer to the grid.
	 */
	CRGrid* 		  grid();		

	/*! beaconListRef() Returns the beacon vector.
	 */
	vector<CRBeacon>  *beaconListRef();
	/*! target() Returns the target position. Usually it is the same as the
	 * beacon.
	 */
	vector<CRTarget>  *targetListRef();		
	/*! robot Returns a pointer to the robot referenced by the id.
	 * \param id The number of the robot. It must exist, otherwise
	 * NULL is returned.
	 */
	CRRobot*		  robot( int id );

	/*! labName Returns the lab name.
	 */
	char* labName();			
	/*! labUnits Returns the lab units.
	 */
	char* labUnits();		
	/*! labSize Returns the lab size.
	 */
	CRVertice labSize();			

private:
    vector<CRWall> wallList;
	vector<CRBeacon> beaconList;
	vector<CRTarget> targetList;
	vector<CRRobot*> robotArray;

    CRGrid *labGrid;
	//CRTarget Target;
	CRVertice labsize;					// WIDTHxHEIGHT

	char labname[MAXLABNAME];
	char labunits[MAXLABNAME];
};
#endif
