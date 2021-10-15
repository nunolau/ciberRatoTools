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

#ifndef _CIBER_RATO_CRQREPLYHANDLER_
#define _CIBER_RATO_CRQREPLYHANDLER_

/*! \class CRQReplyHandler
 *  \brief This class implement one simple parser for information in the XML
 *  format.
 *  This is one parser prepared to receive information that represents only one
 *  reply message.
 */

#include <qxml.h>
#include "crreply.h"

class QString;
class QXmlLocator;

class CRQReplyHandler : public QXmlDefaultHandler
{
public:
	/*! This function will be called in the begining of the XML document.
	 */
    bool startDocument();
	/*! This function is called in the end of the XML document.
	 */
    bool endDocument();
	/*! This function is called when new tag arrive. It is inside this
	 * function that all parsing is done. According the tag received, a new
	 * objects is be created.
	 */
    bool startElement( const QString&, const QString&, const QString& , 
					const QXmlAttributes& );
	/*! For internal use only.
	 */
    void setDocumentLocator(QXmlLocator *);
	/*! This function returns one reply object.
	 */
	CRReply * reply(); // Returns the reply structure

private:

	CRReply *replyObject; 
};

#endif 
