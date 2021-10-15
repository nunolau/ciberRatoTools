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

#include "crqcommhandler.h"
#include <iostream>
#include <QString>

bool CRQCommHandler::startDocument()
{
	// Initialize all elements with null
	lab = NULL;
	grid = NULL;
	gridElement = NULL;
	wall = NULL;
	vertice = NULL;
	beacon = NULL;
	target = NULL;
	robot = NULL;
	type = UNKNOWN;

    return TRUE;
}

bool CRQCommHandler::endDocument()
{
	return TRUE;
}

bool CRQCommHandler::startElement( const QString&, const QString&,
                                   const QString& qName,
                                   const QXmlAttributes& attr)
{
    const QString &tag = qName;
	switch (type) 	//Type defined in .h as enum.
	{
        case UNKNOWN:
        {
			// process begin tag 
            if( tag == "Lab" )
            {
                type = LAB;			//Next time startElement will process one LAB
                lab = new CRLab(); 	// Create a new lab
                // process attributes
                const QString name = attr.value(QString("Name"));
                if( !name.isNull() )
                    lab->setName( name.toAscii() );

                const QString width = attr.value(QString("Width"));
                if( !width.isNull() )
                    lab->setWidth( width.toFloat() );

                const QString height = attr.value(QString("Height"));
                if( !height.isNull() )
                    lab->setHeight( height.toFloat() );
            }

			else if( tag == "Grid" )
            {
                type = GRID;	//Next time startElement will process one GRID
                grid = new CRGrid();
            }

			else if( tag == "Robot" )
            {
                type = ROBOT;  //Next time startElement will process one ROBOT
                robot = new CRRobot();
                // process attributs
                const QString name = attr.value( QString( "Name" ) );
                if( !name.isNull() )
                    robot->setName( name.toAscii() );

                const QString id = attr.value( QString( "Id" ) );
                if( !id.isNull() )
                    robot->setId( id.toInt() );

                const QString score = attr.value( QString( "Score" ) );
                if( !score.isNull() )
                    robot->setScore( score.toInt() );

                const QString collisions =  attr.value( QString( "Collisions" ) );
                if( !collisions.isNull() )
                    robot->setCollisions( collisions.toInt() );

                const QString collision =  attr.value( QString( "Collision" ) );
                if( !collisions.isNull() )
                    robot->setCollision( collision.toAscii() );

                const QString state =  attr.value( QString( "State" ) );
                if( !state.isNull() )
                {
                    if (state == "Stopped" )
                        robot->setState( CRRobot::STOPPED );

                    else if (state == "Running" )
                        robot->setState( CRRobot::RUNNING );

                    else if (state == "Waiting" )
                        robot->setState( CRRobot::WAITINGOTHERS );

                    else if (state == "Removed" )
                        robot->setState( CRRobot::REMOVED );

                    else if (state == "Finished" )
                        robot->setState( CRRobot::FINISHED );

                    else if (state == "Returning" )
                        robot->setState( CRRobot::RETURNING );
                }

                const QString time =  attr.value( QString( "Time" ) );
                if( !time.isNull() )
                    robot->setCurrentTime( time.toInt() );

                const QString arrivalTime =  attr.value( QString( "ArrivalTime" ) );
                if( !arrivalTime.isNull() )
                    robot->setArrivalTime( arrivalTime.toInt() );

                const QString returnTime =  attr.value( QString( "ReturningTime" ) );
                if( !returnTime.isNull() )
                    robot->setReturnTime( returnTime.toInt() );
            }
            else if( tag == "Restart" )
            {
                type = RESTART;
            }
            else // Not a robot, lab or grid
            {
					cerr << "Received one invalid tag!\n";
                    return FALSE;
            }
            break;
        } // End of case UNKNOWN

		case LAB:			// if received element was one  Lab
        {
    		if (tag == "Wall")
            {
                wall = new CRWall;

                /* process attributes */
                const QString height = attr.value(QString("Height"));
                if (!height.isNull())
                    wall->setWallHeight( height.toFloat() );
            }
    		else if (tag == "Beacon")
            {
                vertice = new CRVertice;
                beacon = new CRBeacon( *vertice );
                /* process attributes */
                const QString x = attr.value(QString("X"));
                if (!x.isNull())
                    vertice->setX( x.toFloat() );

                const QString y = attr.value(QString("Y"));
                if (!y.isNull())
                    vertice->setY( y.toFloat() );

                const QString height = attr.value(QString("Height"));
                if (!height.isNull())
                    lab->addBeacon( *vertice, height.toFloat() );
                else
                    lab->addBeacon( *vertice );
            }

    		else if (tag == "Target")
            {
                target = new CRTarget;
                vertice = new CRVertice;
                /* process attributes */
                const QString x = attr.value(QString("X"));
                if (!x.isNull())
                    vertice->setX( x.toFloat() );

                const QString y = attr.value(QString("Y"));
                if (!y.isNull())
                    vertice->setY( y.toFloat() );

                const QString radius = attr.value(QString("Radius"));
                if (!radius.isNull())
                    lab->addTarget( *vertice, radius.toFloat() );
                else
                    lab->addTarget( *vertice );
            }
    		else if (tag == "Corner")
            {
                vertice = new CRVertice;
                // process attributes
                const QString x = attr.value(QString("X"));
                if (!x.isNull())
                    vertice->setX( x.toFloat() );

                const QString y = attr.value(QString("Y"));
                if (!y.isNull())
                    vertice->setY( y.toFloat() );
            }
			break;
			}  // End os element Lab

		case GRID:   // if received element was one Grid
        {
			if( tag == "Position" )
            {
                gridElement = new CRGridElement();
                // Process attributs
                const QString x = attr.value(QString("X"));
                if (!x.isNull())
                    gridElement->position.setX( x.toFloat() );

                const QString y = attr.value(QString("Y"));
                if (!y.isNull())
                    gridElement->position.setY( y.toFloat() );

                const QString dir = attr.value(QString("Dir"));
                if (!dir.isNull())
                    gridElement->direction = dir.toFloat();

                grid->addPosition( gridElement ); // Add one position to the grid
            }
			break;
        } // End of element Grid

		case ROBOT:  // if received element was one 
        {
			if( tag == "Position" )
            {
                // Process attributs
                const QString x = attr.value( QString( "X" ));
                if (!x.isNull())
                    robot->setX( x.toFloat() );

                const QString y = attr.value(QString("Y"));
                if (!y.isNull())
                    robot->setY( y.toFloat() );

                const QString dir = attr.value(QString("Dir"));
                if (!dir.isNull())
                    robot->setDirection( dir.toFloat() );
            }
			break;
        } // End of element Robot
        case RESTART: // TODO
            break;
	}

    return TRUE;

}

bool CRQCommHandler::endElement( const QString&, const QString&, const
								QString& qName)
{
	/* process end tag */

    const QString &tag = qName;

	switch (type)
	{
        case UNKNOWN:
        {
            break;
        }
		case LAB:
        {
    		if (tag == "Wall")
				lab->addWall( wall );
    		else if (tag == "Corner")
                wall->addCorner( *vertice );

			break;
        }
		case GRID:
        {
				// Does Nothing
			break;
        }
		case ROBOT:
        {
				// Does Nothing
			break;
        }
		case RESTART:
        {
				// Does Nothing
			break;
        }
	}
    return TRUE;
}

CRLab * CRQCommHandler::getLab( void )
{
	return lab;
}

CRRobot * CRQCommHandler::getRobot( void )
{
	return robot;
}

CRGrid * CRQCommHandler::getGrid( void )
{
	return grid;
}

void CRQCommHandler::setDocumentLocator(QXmlLocator *)
{

}

CRQCommHandler::Type CRQCommHandler::objectType()
{
	return type;
}

