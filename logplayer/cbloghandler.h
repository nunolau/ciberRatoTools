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
#ifndef _CB_LOG_HANDLER_
#define _CB_LOG_HANDLER_

#include <qxml.h>

#include "cbposition.h"
#include "cbrobot.h"
#include "cblab.h"
#include "cbgrid.h"
#include "cbparameters.h"

#include <vector>

using std::vector;

class cbLabHandler;
class cbGridHandler;
class cbParamHandler;

class QString;

class cbLogHandler : public QXmlDefaultHandler
{
public:
    cbLogHandler (QXmlReader *rd) {reader=rd; labHandler=0;}

	/*! \enum Type
	 *  This enum type represent the object received.
	 */
	enum Type {UNKNOWN, LAB, GRID, PARAM};
	
    bool startDocument();
    bool endDocument();
    bool startElement( const QString&, const QString&, const QString& , const QXmlAttributes& );
    bool endElement( const QString&, const QString&, const QString& );
	void setDocumentLocator(QXmlLocator *);

	/* extra functions */
    vector< vector <cbRobot> > *parsedLog();

	cbLab * getLab() {return lab;};
	/*! This function returns one grid.
	 */
	cbGrid * getGrid(){return grid;};
	/*! This function returns parsed parameters.
	 */
	cbParameters * getParameters(){return param;};
	/*! This function returns one robot.
	 */
	cbRobot * getRobot();
	/*! This function returns the type of object received.
	 */
	Type objectType();


private:
	vector< vector<cbRobot> > *log;
	cbRobot robot;
	cbPosition position;
	int time;	
	cbLab    *lab;		
	cbGrid   *grid;		
	cbParameters  *param;		

        QXmlReader *reader;
	Type type;

	cbLabHandler   *labHandler;
	cbGridHandler  *gridHandler;
	cbParamHandler *paramHandler;
};     

#endif
