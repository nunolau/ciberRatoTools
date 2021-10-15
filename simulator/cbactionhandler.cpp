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
 * class cbActionHandler
 */

#include <iostream>
 
#include "cbactionhandler.h"
#include "cbrobotaction.h"

#include <qstring.h>

using std::cerr;
 
bool cbActionHandler::startDocument()
{
    action.reset();
    return TRUE;
}

bool cbActionHandler::endDocument()
{
	return TRUE;
}

bool cbActionHandler::startElement( const QString&, const QString&, const QString& qName, const QXmlAttributes& attr)
{
	/* process begin tag */
	const QString &tag = qName;
        activeTag=tag;
	if (tag == "Actions")
	{
		/* process attributes */
		const QString &leftmotor = attr.value(QString("LeftMotor"));
		if (!leftmotor.isNull())
		{
			action.leftMotorChanged = true;
			action.leftMotor = leftmotor.toDouble();
		}
		const QString &rightmotor = attr.value(QString("RightMotor"));
		if (!rightmotor.isNull())
		{
			action.rightMotorChanged = true;
			action.rightMotor = rightmotor.toDouble();
		}
		const QString &endled = attr.value(QString("EndLed"));
		if(!endled.isNull()) {
		   	action.endLedChanged = true;
		        if (endled == "On") action.endLed = true;
			else action.endLed = false;
	        }
		const QString &returningled = attr.value(QString("ReturningLed"));
		if(!returningled.isNull()) {
			action.returningLedChanged = true;
		        if (returningled == "On") action.returningLed = true;
			else action.returningLed = false;
		}
		const QString &visitingled = attr.value(QString("VisitingLed"));
		if(!visitingled.isNull()) {
			action.visitingLedChanged = true;
		        if (visitingled == "On") action.visitingLed = true;
			else action.visitingLed = false;
		}
	}
	else if (tag == "SensorRequests") {
		for(int a=0; a < attr.length(); a++) {
			const QString &val = attr.value(a); 
			if(!val.isNull() && (val == "Yes")) {
				action.sensorRequests.push_back(attr.qName(a));
			}
		}
	}
	else if (tag == "Say") {
	}
    return TRUE;
}

bool cbActionHandler::endElement( const QString&, const QString&, const QString& qName)
{
	/* process end tag */
	const QString &tag = qName;
	if (tag != "Actions" 
	    && tag != "SensorRequests" && tag!="Say")
	{
		return false;
	}
    return true;
}

bool cbActionHandler::startCDATA()
{
    //fprintf(stderr,"startCDATA\n");
    return TRUE;
}

bool cbActionHandler::endCDATA()
{
    //fprintf(stderr,"endCDATA\n");
    return TRUE;
}

bool cbActionHandler::characters(const QString& data)
{
        if(activeTag=="Say")
        {
             action.sayMessage+=data;
             action.sayReceived=true;
        }
       //fprintf(stderr,"characters tag=%s\n",activeTag.latin1());
        return TRUE;
}

void cbActionHandler::setDocumentLocator(QXmlLocator *)
{
}


/* extra functions */

cbRobotAction &cbActionHandler::parsedAction()
{
	return action;
}

