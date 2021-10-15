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
 * class cbLogHandler
 */
 
#include "cblabhandler.h"
#include "cbgridhandler.h"
#include "cbparamhandler.h"

#include "cbloghandler.h"

#include <qstring.h>
 
bool cbLogHandler::startDocument()
{
    log = 0;

    lab=0;
    grid=0;
    param=0;

    labHandler = 0;
    gridHandler = 0;
    paramHandler = 0;


    type = UNKNOWN;
    return TRUE;
}

bool cbLogHandler::endDocument()
{	
	if(labHandler!=0) {
	    lab = labHandler->parsedLab();
	    delete labHandler;
	    labHandler=0;
	}

	if(gridHandler!=0) {
	    grid = gridHandler->parsedGrid();
	    delete gridHandler;
	    gridHandler=0;
	}

	if(paramHandler!=0) {
	    param= paramHandler->parsedParameters();
	    delete paramHandler;
	    paramHandler=0;
	}



	return TRUE;
}

bool cbLogHandler::startElement( const QString&, const QString&, const QString& qName, 
                                    const QXmlAttributes& attr)
{
	/* process begin tag */
	const QString &tag = qName;
	if (tag == "Log")
	{
		log = new vector< vector <cbRobot> >;
	}
	else if (tag == "Lab")
	{
		type = LAB;			//Next time startElement will process one LAB

		labHandler=new cbLabHandler( reader, this, attr);
		reader->setContentHandler(labHandler);
	}
	else if (tag == "Grid")
	{
		type = GRID;			//Next time startElement will process one GRID

		gridHandler=new cbGridHandler( reader, this, attr);
		reader->setContentHandler(gridHandler);
	}	
	else if (tag == "Parameters")
	{
		type = PARAM;			//Next time startElement will process one PARAM

		paramHandler = new cbParamHandler( reader, this, attr);
		reader->setContentHandler(paramHandler);
	}
	else if (tag == "LogInfo")
	{
		//fprintf(stderr,"pushing robsEmpty\n");
		vector<cbRobot> robsEmpty;
		log->push_back(robsEmpty);
		const QString &timeAttr = attr.value(QString("Time"));
		if (!timeAttr.isNull()) time=timeAttr.toInt();
	}
	else if (tag == "Robot")
	{
		//fprintf(stderr,"start Robot tag\n");
		int robId=-1;

		const QString &idAttr = attr.value(QString("Id"));
		if (!idAttr.isNull()) { 
			robId=idAttr.toInt();
		        robot.setId(robId);
		}
		else return FALSE;   // parse error

		robot.setTime(time);
		const QString &nameAttr = attr.value(QString("Name"));
		if (!nameAttr.isNull()) { 
                robot.setName(nameAttr.toAscii());
		}

		const QString &stateAttr = attr.value(QString("State"));
		if (!stateAttr.isNull()) { 
                robot.setState(stateAttr.toAscii());
		}
	}
	else if (tag == "Pos")
	{
		double x=0.0, y=0.0, dir=0.0;
		//fprintf(stderr,"start Pos tag\n");

		const QString &xAttr = attr.value(QString("X"));
		if (!xAttr.isNull()) x=xAttr.toDouble();
		const QString &yAttr = attr.value(QString("Y"));
		if (!yAttr.isNull()) y=yAttr.toDouble();
		const QString &dirAttr = attr.value(QString("Dir"));
		if (!dirAttr.isNull()) dir=dirAttr.toDouble()/180.0*M_PI;

		position.set(x,y,dir);
		robot.setPosition(position);
	}
	else if (tag == "Scores")
	{
		unsigned int score=0, arrivalTime=0, returningTime=0, collisionCount=0;
		QString visitedMask;
		bool collision=false;
		//fprintf(stderr,"start Scores tag\n");

		const QString &scoreAttr = attr.value(QString("Score"));
		if (!scoreAttr.isNull()) score=scoreAttr.toInt();
		const QString &arrivalTimeAttr = attr.value(QString("ArrivalTime"));
		if (!arrivalTimeAttr.isNull()) arrivalTime=arrivalTimeAttr.toInt();
		const QString &returningTimeAttr = attr.value(QString("ReturningTime"));
		if (!returningTimeAttr.isNull()) returningTime=returningTimeAttr.toInt();
		const QString &collisionsAttr = attr.value(QString("Collisions"));
		if (!collisionsAttr.isNull()) collisionCount=collisionsAttr.toInt();
		const QString &collisionAttr = attr.value(QString("Collision"));
		if (!collisionAttr.isNull()) if(collisionAttr=="True") collision=true;
		const QString &visitedMaskAttr = attr.value(QString("VisitedMask"));
		if (!visitedMaskAttr.isNull()) visitedMask=visitedMaskAttr;

		robot.setScore(score);
		robot.setArrivalTime(arrivalTime);
		robot.setReturningTime(returningTime);
		robot.setCollisionCount(collisionCount);
		if(collision) robot.setCollision();
		else robot.resetCollision();
		robot.setVisitedMask(visitedMask);
	}
        return TRUE;
}

bool cbLogHandler::endElement( const QString&, const QString&, const QString& qName)
{
	/* process end tag */
	const QString &tag = qName;
	if (tag == "Log")
	{
		//simulator->setLab(lab);
	}
	else if (tag == "LogInfo")
	{
	}
	else if (tag == "Robot")
	{
		//fprintf(stderr,"pushing new robot into %d\n",log->size()-1);
		(*log)[log->size()-1].push_back(robot);
		//fprintf(stderr,"pushed %d robots \n",(*log)[log->size()-1].size());
	}
	else if (tag == "Pos")
	{
	}
    return TRUE;
}

void cbLogHandler::setDocumentLocator(QXmlLocator *)
{
}

/* extra functions */

vector < vector< cbRobot > > *cbLogHandler::parsedLog()
{
	return log;
}
