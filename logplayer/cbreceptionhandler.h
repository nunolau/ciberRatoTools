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
#ifndef _CB_RECEPTION_HANDLER_
#define _CB_RECEPTION_HANDLER_

#include <qxml.h>

class QString;
class QXmlLocator;

class cbView;
class cbPanel;

class cbReceptionHandler : public QXmlDefaultHandler
{
public:
	enum Type { UNKNOWN, VIEW, PANEL, ROBOT};
	cbReceptionHandler(QXmlSimpleReader *xmlParser);

    bool parse(void *data);
    
    bool startDocument();
    bool endDocument();
    bool startElement( const QString&, const QString&, const QString& , const QXmlAttributes& );
    bool endElement( const QString&, const QString&, const QString& );
	void setDocumentLocator(QXmlLocator *);

	cbView *viewObject();
	cbPanel *panelObject();
	Type objectType();

private:
        QXmlInputSource xmlSource;
        QXmlSimpleReader *xmlParser;

	cbView *view;
	cbPanel *panel;
	Type type;
};                   

#endif
