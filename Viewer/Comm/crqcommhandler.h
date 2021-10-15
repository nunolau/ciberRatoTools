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

#ifndef _CIBER_RATO_CRQCOMMHANDLER_
#define _CIBER_RATO_CRQCOMMHANDLER_

/*! \class CRQCommHandler
 *  \brief This class implements one simple parser for information in XML
 *  format.
 *  This is one parser prepared to receive information that represents one
 *  robot, one lab or one grid.
 */

#include <qxml.h>
#include "../Lab/crrobot.h"
#include "../Lab/crgrid.h"
#include "../Lab/crlab.h"
#include "../Lab/crwall.h"
#include "../Lab/crtarget.h"
#include "../Lab/crvertice.h"
#include "../Lab/crbeacon.h"

class QString;
class QXmlLocator;

class CRQCommHandler : public QXmlDefaultHandler
{
public:
	/*! \enum Type
	 *  This enum type represent the object received.
	 */
	enum Type {UNKNOWN, LAB, GRID, ROBOT, RESTART};
	/*! This function will be called in the begining of the XML document.
	 */
    bool startDocument();
	/*! This function is called in the end of the XML document.
	 */
    bool endDocument();
	/*! This function is called when new tag arrive. It is inside this function,
	 * that all parsing is done. According to the tag received, a new object
	 * will be created.
	 */
    bool startElement( const QString&, const QString&, const QString& , 
					const QXmlAttributes& );
	/*! This function is called at the end of one tag. Inside, if is necessary, 
	 * some elements are added to anothers.
	 */
    bool endElement( const QString&, const QString&, const QString& );
	/*! For internal use only.
	 */
    void setDocumentLocator(QXmlLocator *);
	/*! This function returns one Lab.
	 */
	CRLab * getLab();
	/*! This function returns one grid.
	 */
	CRGrid * getGrid();
	/*! This function returns one robot.
	 */
	CRRobot * getRobot();
	/*! This function returns the type of object received.
	 */
	Type objectType();

private:
	CRGridElement *gridElement;
	CRGrid *grid;
	CRLab *lab;		
	CRWall *wall;
	CRVertice *vertice;
	CRBeacon *beacon;
	CRTarget *target;
	CRRobot *robot;	
	Type type;
};

#endif
