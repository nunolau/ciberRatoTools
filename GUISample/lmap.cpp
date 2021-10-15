/*
    This file is part of ciberRatoToolsSrc.

    Copyright (C) 2001-2020 Universidade de Aveiro

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
 * class LMap
 */
 
#include <qstring.h>

#include "lmap.h"

LMap::LMap()
{
    for(int r=0; r < CELLROWS * 2 - 1; r++) {
        for(int c=0; c < CELLCOLS * 2 - 1; c++) {
            lmap[r][c]=' ';
        }
    }
}
 
bool LMap::startDocument()
{
    return TRUE;
}

bool LMap::endDocument()
{
	return TRUE;
}

bool LMap::startElement( const QString&, const QString&, const QString& qName, 
                                    const QXmlAttributes& attr)
{
	/* process begin tag */
	const QString &tag = qName;

	if (tag == "Row")
	{
        int row=0;
		const QString &pos = attr.value(QString("Pos"));
		if (!pos.isNull()) row = pos.toInt();
		const QString &pattern = attr.value(QString("Pattern"));
        const QChar *spec = pattern.data();
        int col=0;
		while (!spec->isNull()) {
            if(row % 2 == 0) { // only vertical walls are allowed here
                if(spec->toAscii()=='|') {                 
                    lmap[row][(col+1)/3*2-1] = '|';
                }
            }
            else {// only horizontal walls are allowed at odd rows 
                if(col % 3 == 0) { // if there is a wall at this collumn then there must also be a wall in the next one
                    if(spec->toAscii()=='-') {  
                        lmap[row][col/3*2] = '-';
                    }
    
                }
            }
            spec++;
            col++;
        }
	}
    return TRUE;
}

bool LMap::endElement( const QString&, const QString&, const QString& )
{
    return TRUE;
}

void LMap::setDocumentLocator(QXmlLocator *)
{
}

void LMap::printMap()
{
    for(int r=CELLROWS * 2 - 2; r >=0 ; r--) {
        for(int c=0; c < CELLCOLS * 2 - 1; c++) {
            printf("%c",lmap[r][c]);
        }
        printf("\n");
    }
}
