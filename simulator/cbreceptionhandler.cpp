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
#include "cbreceptionhandler.h"

#include "cbview.h"
#include "cbpanel.h"
#include "cbrobot.h"
#include "cbrobotbeacon.h"
#include "netif.h"

#include <iostream>
#include <qstring.h>

using std::cerr;

cbReceptionHandler::cbReceptionHandler(QXmlSimpleReader *parser)
{
	robot = 0;
	robotBeacon = 0;
	panel = 0;
	view = 0;
	xmlParser=parser;
}
 
bool cbReceptionHandler::startDocument()
{
	robot = 0;
	robotBeacon = 0;
	panel = 0;
	view = 0;
    return true;
}

bool cbReceptionHandler::endDocument()
{
	return true;
}

bool cbReceptionHandler::startElement( const QString&, const QString&, const QString& qName, const QXmlAttributes& attr)
{
	/* process begin tag */
	const QString &tag = qName;
	if (tag == "View")
	{
		type = VIEW;
		view = new cbView;
	}
	else if (tag == "Panel")
	{
		type = PANEL;
		panel = new cbPanel;
	}
	else if (tag == "Robot")
	{
		type = ROBOT;

		robot = new cbRobot(irSensorDefaultAngles);

		/* process attributes */
        const QString &name = attr.value(QString("Name"));
        if (!name.isNull()) robot->setName(name.toLatin1().constData());
		const QString &id = attr.value(QString("Id"));
		if (!id.isNull()) robot->setId(id.toUInt());
	}
	else if (tag == "RobotBeacon")
	{
		type = ROBOTBEACON;

		robotBeacon = new cbRobotBeacon(irSensorDefaultAngles);

		/* process attributes */
        const QString &name = attr.value(QString("Name"));
        if (!name.isNull()) robotBeacon->setName(name.toLatin1().constData());
		const QString &id = attr.value(QString("Id"));
		if (!id.isNull()) robotBeacon->setId(id.toUInt());
		const QString &height = attr.value(QString("Height"));
		if (!height.isNull()) robotBeacon->setHeight(height.toDouble());
	}
	else if (tag == "IRSensor")
	{
		unsigned int id=0;
		double irSensorAngle;

		/* process IRSensor attributes */
		/* get sensor id */
		const QString &irId = attr.value(QString("Id"));
		if (!irId.isNull()) {


			id=irId.toUInt();

		        /* get sensor angle */
			const QString &irAngle = attr.value(QString("Angle"));
			if (!irAngle.isNull()) {
				irSensorAngle=irAngle.toDouble()/180.0*M_PI;

				if(robot!=0) {
					/* update robot */
					robot->setIRSensorAngle(id,irSensorAngle);
				}
				else return false;
			}
		}
	}
	else
	{
		type = UNKNOWN;
		return false;
	}
    return true;
}

bool cbReceptionHandler::endElement( const QString&, const QString&, const QString& qName)
{
	/* process end tag */
	const QString &tag = qName;
	if (tag == "View")
	{
		if (view == 0)
		{
			cerr << "View tag arrived but view==0\n";
			return false;
		}
	}
	else if (tag == "Panel")
	{
		if (panel == 0)
		{
			cerr << "Panel tag arrived but panel==0\n";
			return false;
		}
	}
	else if (tag == "Robot")
	{
		if (robot == 0)
		{
			cerr << "Robot tag arrived but robot==0\n";
			return false;
		}
	}
	else if (tag == "RobotBeacon")
	{
		if (robotBeacon == 0)
		{
			cerr << "RobotBeacon tag arrived but robotBeacon==0\n";
			return false;
		}
	}
	else if (tag == "IRSensor") {}
	else
	{
		cerr << "Unknown tag\n";
		return false;
	}
    return true;
}

void cbReceptionHandler::setDocumentLocator(QXmlLocator *)
{
	return ;
}

cbReceptionHandler::Type cbReceptionHandler::objectType()
{
	return type;
}

cbRobot *cbReceptionHandler::robotObject()
{
	return robot;
}

cbRobotBeacon *cbReceptionHandler::robotBeaconObject()
{
	return robotBeacon;
}

cbPanel *cbReceptionHandler::panelObject()
{
	return panel;
}

cbView *cbReceptionHandler::viewObject()
{
	return view;
}


bool cbReceptionHandler::parse(void *data, int datasize)
{
     //check MicMouseServer binary protocol
     if(datasize==sizeof(CommMessage) && 
        ntohs(((CommMessage *)data)->comm)==NEWROBOT_COMM)
     {
         type = ROBOT;
         CommMessage *pmsg=(CommMessage *)data;
         robot=new cbRobotBin;
         robot->setName(pmsg->u.rob_name);
         robot->setId(0);
         return true;
     }

     //parse xml
     xmlParser->setContentHandler(this);
     xmlSource.setData(QByteArray((const char *)data));

     return xmlParser->parse(xmlSource);
}

