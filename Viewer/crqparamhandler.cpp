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

#include "crqparamhandler.h"
#include <iostream>
#include <stdlib.h>
#include <QString>

using namespace std;

bool CRQParamHandler::startDocument()
	{
	paramObject = 0;

    return TRUE;
	}

bool CRQParamHandler::endDocument()
{
    return TRUE;
}

bool CRQParamHandler::startElement( const QString&, const QString&, 
                                    const QString& qName, const QXmlAttributes& attr)
{
	/* process begin tag */

    const QString &tag = qName;

    if( tag == "Viewer" )
    {
        if((paramObject = new CRMainParameters()) == NULL )
        {
            cerr << "Erro a criar o objecto parameters\n";
            return false;
        }

        // process attributes
        const QString host = attr.value( QString( "Host" ));
        if ( !host.isNull() )
            paramObject->serverAddr = host;

        const QString port = attr.value( QString( "Port" ));
        if ( !port.isNull() )
            paramObject->port = port.toUShort();

        const QString lowerColor = attr.value ( QString( "Lowercolor" ));
        if ( !lowerColor.isNull() )
            paramObject->lowerColor = lowerColor;

        const QString higherColor = attr.value( QString( "Highercolor" ));
        if ( !higherColor.isNull() )
            paramObject->higherColor = higherColor;

        const QString control = attr.value( QString( "Control" ));
        if ( !control.isNull() )
            paramObject->control = control[0].toAscii();

        const QString autoC = attr.value( QString( "AutoConnect" ));
        if ( !autoC.isNull() )
            paramObject->autoConnect = autoC[0].toAscii();

        const QString autoS = attr.value( QString( "AutoStart" ));
        if ( !autoS.isNull() )
            paramObject->autoStart = autoS[0].toAscii();

        return true;
    }
	else
		return false;
}


void CRQParamHandler::setDocumentLocator( QXmlLocator * )
{

}


CRMainParameters * CRQParamHandler::parameters()
{
	return paramObject;
}
