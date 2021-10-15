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

#include <iostream>
#include <qstring.h>

using std::cerr;

cbReceptionHandler::cbReceptionHandler(QXmlSimpleReader *parser)
{
	panel = 0;
	view = 0;
	xmlParser=parser;
}
 
bool cbReceptionHandler::startDocument()
{
	panel = 0;
	view = 0;
    return true;
}

bool cbReceptionHandler::endDocument()
{
	return true;
}

bool cbReceptionHandler::startElement( const QString&, const QString&, const QString& qName, const QXmlAttributes&)
{
	/* process begin tag */
	const QString &tag = qName;
	if (tag == "View")
	{
		type = VIEW;
		view = new cbView;
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

cbPanel *cbReceptionHandler::panelObject()
{
	return panel;
}

cbView *cbReceptionHandler::viewObject()
{
	return view;
}


bool cbReceptionHandler::parse(void *data)
{
     xmlParser->setContentHandler(this);
     xmlSource.setData(QByteArray((const char *)data));
     return xmlParser->parse(xmlSource);
}

