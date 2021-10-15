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
 * class cbGridHandler
 */
 
#include "cbgridhandler.h"
#include "cbgrid.h"

#include <QString>
 
bool cbGridHandler::startDocument()
{
	point = cbPoint();
	pos = cbPosition();
	grid = 0;
    return TRUE;
}

bool cbGridHandler::endDocument()
{
	return TRUE;
}

bool cbGridHandler::startElement( const QString&, const QString&, const QString& qName, const QXmlAttributes& attr)
{
	/* process begin tag */
	const QString &tag = qName;

	if (grid==0 && tag != "Grid") return false;

	if (tag == "Grid" && grid==0)
	{
		grid = new cbGrid;
	}
	else if (tag == "Position" && grid!=0)
	{
		pos = cbPosition();
		point = cbPoint();
		/* process attributes */
		const QString &x = attr.value(QString("X"));
		if (!x.isNull()) point.setX(x.toDouble());
		const QString &y = attr.value(QString("Y"));
		if (!y.isNull()) point.setY(y.toDouble());
		const QString &direction = attr.value(QString("Dir"));
		if (!direction.isNull()) pos.setDegDirection(direction.toDouble());
	}
    return TRUE;
}

bool cbGridHandler::endElement( const QString&, const QString&, const QString& qName)
{
	/* process end tag */
	const QString &tag = qName;
	if (tag == "Grid")
	{
	}
	else if (tag == "Position")
    {
        pos.setCoord(point);
        grid->append(pos);
	}
    return TRUE;
}

void cbGridHandler::setDocumentLocator(QXmlLocator *)
{
}


/* extra functions */

cbGrid *cbGridHandler::parsedGrid()
{
	return grid;
}
