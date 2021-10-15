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

#include "cbclient.h"

#include <QUdpSocket>
#include <QHostAddress>

#include <iostream>
#include <stdio.h>

using std::cerr;

#define REPLYMAXSIZE 4096

cbClient::cbClient() : QUdpSocket()
{
    bind();
}

cbClient::~cbClient()
{
}

/*!
	Send the OK reply message to client.
*/
bool cbClient::Reply(QHostAddress &a, unsigned short &p, cbParameters *param)
{
    //cout.form("Sending reply for client to %s:%hd\n", a.toString().toLatin1().constData(), p);
    /* set peer address and peer port */
    address = a;
	port = p;

	/* constructing reply message */
	char reply[REPLYMAXSIZE];
	int cnt;
	cnt = sprintf(reply, "<Reply Status=\"Ok\">\n\t");
	cnt += param->toXml(reply+cnt, REPLYMAXSIZE-cnt);
	cnt += sprintf(reply+cnt, "</Reply>\n");

    /* send reply to client */
    if (writeDatagram(reply, cnt+1, address, port) != cnt+1)
	{
		cerr << "Fail replying to client\n";
		return false;
    }
    //cout << "Reply sent\n" << reply;
	return true;
}

/*!
	Send the Refused reply message to client.
*/
bool cbClient::Refuse(QHostAddress &a, unsigned short &p)
{
	//cout.form("Sending refuse for client to %s:%hd\n", a.toString().latin1(), p);
	/* set peer address and peer port */
	address = a;
	port = p;

	/* constructing reply message */
	char reply[256];
	int cnt;
	cnt = sprintf(reply, "<Reply Status=\"Refused\"></Reply>\n");

    /* send reply to client */
    if (writeDatagram(reply, cnt+1, address, port) != cnt+1)
	{
		cerr << "Fail replying to client\n";
		return false;
    }
    //cout << "Reply sent\n" << reply;
	return true;
}


/*!
	Send xml message to client.
*/
bool cbClient::send(const char *xml, unsigned int cnt)
{
    if (writeDatagram(xml, cnt, address, port) != (int)cnt)
    {
        //cerr << "Fail sending xml message to client\n";
		//cerr << xml;
		return false;
    }

	return true;
}
