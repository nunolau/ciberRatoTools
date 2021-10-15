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

#include "crlab.h"

/* **************************************************************************
 * * The Lab...                                                             *
 * **************************************************************************
 */

CRLab::CRLab( )
{
	labGrid = NULL;
	
	newLab();
}

/*CRLab::CRLab( istream *file )
{
	newLab();
	if ( loadLabFile( file ) != 0)
		{
			cerr << "Failed while parsing the file." << endl;
			exit(1);
		}

}*/
	
CRLab::~CRLab()
{}

int CRLab::newLab()
{
	// Begin the cleaning process...
	
	labsize = CRVertice( 28, 14 );	// Default Value
	//Target = CRTarget( CRVertice(0, 0), 0.0 );

	wallList.clear();	  // No more walls
	beaconList.clear();   // No more beacons
	targetList.clear();   // No more targets
	robotArray.clear();   // No more Robots
	robotArray.resize(3); // This is the default value

	if (labGrid!=NULL) {
						delete labGrid;	// No more start positions
						labGrid = NULL;
						}

	strcpy( labname, "NonameLab" );
	strcpy( labunits, "UnknownUnits" );
	return (0);
}

/*int CRLab::loadLabFile( istream *file )  // Load an already made Lab
{
	char word[20];
	int c, exit=0;
	int (*parserFunction)( istream *file ) == NULL;

    if (!file) 
		{
			cerr << "ERROR: Cannot open stream" << endl;
			return(-1);
		}
	while ( !file.eof() && !exit)
		{ 
			file >> word;
			for(c=0; c < N_KEY_WORDS && strcmp( word, keyWord[c] ) !=0 ; c++);

			if (c != N_KEY_WORDS)  // If not END keyword
				if (c < N_KEY_WORDS) // This is a valid parser
					{
						parserFunction = parsers[c];
						(*parserFunction)( file ); // call the parser with the stream
					}
			else
				{ // END detected
					exit = -1;
				}  
		}
return (0);
}
*/

/*int CRLab::saveLabFile( istream *file )	// Saves your work
{
	return(0);
}*/
 
int CRLab::addWall( vector<CRVertice> *verticeVector, float height )
{
	// Lets add a wall
	
	wallList.push_back( CRWall(verticeVector, height) );
	return(0);
}

int CRLab::addWall( CRWall *wall )
{
	wallList.push_back(*wall); // Desperdica memoria!
	return(0);

}
int CRLab::addBeacon( CRVertice location, float height )
{
	// Lets add a beacon to our lab
	beaconList.push_back( CRBeacon(location, height) );
	return(0);
}

int CRLab::addTarget( CRVertice position, float radius )
{
	targetList.push_back( CRTarget(position, radius) );
	return (0);
}

int CRLab::addGrid( CRGrid *startGrid )
{
	// Adding a start spot
	if (startGrid == NULL) return -1;

	if (labGrid == NULL)
		labGrid = startGrid;
	else
		{
			delete labGrid;
			labGrid = startGrid;
		}
	robotArray.clear();
	robotArray.resize( startGrid->howManyPositions() );

	return(0);
}

int CRLab::addRobot( CRRobot* robot )
{
	if ( ( (labGrid != NULL) &&
		 (robot->id() <= grid()->howManyPositions()) &&
		 (robot->id() > 0) ) ||

		 ( (labGrid == NULL) &&
		 (robot->id() <= 3) &&
		 (robot->id() > 0) )
	   ) //valid robotID?
		{
			if ( robotArray[ robot->id()-1 ] == NULL ) // Add or update?
			{
				// We have an addRobot procedure
				robotArray[ robot->id()-1 ] = robot;
			}
			else // we have a simple updateRobot procedure
			{
				if ( robot->state() == CRRobot::REMOVED )
					{
						// Goodbye
						delete robotArray[ robot->id() -1 ];
						robotArray[ robot->id() -1 ] = NULL;
					}
				else
					{
						robotArray[ robot->id() -1 ]->setX( robot->x() );
						robotArray[ robot->id() -1 ]->setY( robot->y() );
						robotArray[ robot->id() -1 ]->setDirection( robot->direction() );
						robotArray[ robot->id() -1 ]->setScore( robot->score() );
						robotArray[ robot->id() -1 ]->setState( robot->state() );
						robotArray[ robot->id() -1 ]->setCollisions( robot->collisions() );
						robotArray[ robot->id() -1 ]->setCollision( robot->collision() );
						robotArray[ robot->id() -1 ]->setCurrentTime( robot->currentTime() );
					}

			}
		}
	return 0;
}

int CRLab::setSize( CRVertice size )
{
	// Setting the lab size WidthxHeight
	labsize = size;
	return(0);

}

int CRLab::setHeight( float height )
{
	labsize.setY( height );
	return(0);
}

int CRLab::setWidth( float width )
{
	labsize.setX( width );
	return(0);
}

int CRLab::setName( const char *name )
{
	strcpy(labname, name);
	return(0);
}

int CRLab::setUnits( char *units )
{
	strcpy(labunits, units);
	return(0);
}

vector<CRWall>*    CRLab::wallListRef()
{
	return (&wallList);
}

CRGrid* CRLab::grid()
{
	return (labGrid);
}

vector<CRBeacon>*  CRLab::beaconListRef()
{
	return (&beaconList);
}

vector<CRTarget>*  CRLab::targetListRef()
{
	return (&targetList);
}

//CRTarget	CRLab::target()
//{
	//return Target;
//}

char* CRLab::labName()
{
	return labname;
}

char* CRLab::labUnits()
{
	return labunits;
}

CRVertice CRLab::labSize()
{
	return labsize;
}

CRRobot* CRLab::robot( int id )
{
	if ( (labGrid != NULL) &&
		 ( id <= grid()->howManyPositions()) && id > 0 ) //valid robotID?
			return robotArray[ id -1 ];

	else if ( (id > 0) && (id <= 3) ) return robotArray[ id -1 ];

	return NULL;
}
