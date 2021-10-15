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
#ifndef _CB_VIEW_HANDLER_
#define _CB_VIEW_HANDLER_

#include <qxml.h>

#include "cbviewcommand.h"

class QString;
class QXmlLocator;

class cbView;
class cbRobot;
class cbPanel;

/**
 * SAX parser of messages from viewer
 */
class cbViewHandler : public QXmlDefaultHandler
{
public:
	cbViewHandler();

    bool startDocument();
    bool endDocument();
    bool startElement( const QString&, const QString&, const QString& , const QXmlAttributes& );
    bool endElement( const QString&, const QString&, const QString& );
	void setDocumentLocator(QXmlLocator *);

	cbCommand	&Command();

private:
	cbCommand	command;
};                   

#endif
