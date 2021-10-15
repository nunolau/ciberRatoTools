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
#ifndef _CB_RECEPTIONIST_
#define _CB_RECEPTIONIST_

/*!
	\class cbReceptionist
	\brief Socket based class, point of registration of new robots and new views.

	This class implements a socket and a parser for the initial tag of an arriving
	xml message.
	Depending on the initial tag, an appropriate parser handler is assigned to
	the xml parser.
*/

#define XMLMAX 1024

#include <QUdpSocket>
#include <QHostAddress>
#include <qxml.h>

#include <iostream>

class QXmlSimpleReader;

class cbRobot;
class cbRobotBeacon;
class cbView;
class cbPanel;

struct cbClientForm
{
	enum {NOBODY, VIEW, PANEL, ROBOT, ROBOTBEACON, UNKNOWN} type;
	union 
	{
		cbRobot *robot;
		cbRobotBeacon *robotBeacon;
		cbView *view;
		cbPanel *panel;
	} client;
	QHostAddress addr;
	unsigned short port;
};

class cbReceptionist : public QUdpSocket
{
public:
	/* constructor and destructor */
	cbReceptionist(unsigned int port);
	~cbReceptionist();

	/* added functionality */
	bool CheckIn(void);
	cbClientForm &Form();
	bool bad();
	//void setXmlParser(QXmlSimpleReader *);
	//void setXmlSource(QXmlInputSource *);

private: // data members
	char xmlBuff[XMLMAX];		// buffer for xml messages
	bool status;
	QXmlSimpleReader *xmlParser;
	QXmlInputSource xmlSource;
	cbClientForm form;
};

#endif
