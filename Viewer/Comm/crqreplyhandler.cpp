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

#include "crqreplyhandler.h"
#include <iostream>
#include <stdlib.h>
#include <qstring.h>

using namespace std;

bool CRQReplyHandler::startDocument()
{
	replyObject = 0;
    return TRUE;
}

/*---------------------------------------------------------------------------*/
bool CRQReplyHandler::endDocument()
{
    return TRUE;
}

/*---------------------------------------------------------------------------*/
bool CRQReplyHandler::startElement( const QString&, const QString&, 
  const QString& qName, const QXmlAttributes& attr)
{
	/* process begin tag */
    const QString &tag = qName;

    if( tag == "Reply" )
    {
        replyObject = new CRReply;	// falta testar retorno
        // process attributes
        const QString status = attr.value( QString( "Status" ));
        if ( !status.isNull() )
        {
            if( status == "Ok" )
                replyObject->status = true;
            else
                replyObject->status = false;
        }
    }
	else if( tag == "Parameters" )
    {
        replyObject->parameters = new CRParameters;	// falta testar retorno
        // process attributes
        const QString cycleTime = attr.value( QString( "CycleTime" ));
        if( !cycleTime.isNull() )
            replyObject->parameters->cycleTime = cycleTime.toUInt();

        const QString simTime = attr.value( QString( "SimTime" ));
        if( !simTime.isNull() )
            replyObject->parameters->simTime = simTime.toUInt();

        const QString compassTime = attr.value (QString( "CompassTime" ));
        if( !compassTime.isNull() )
            replyObject->parameters->compassTime = compassTime.toUInt();

        const QString obstacleNoise = attr.value(QString("ObstacleNoise"));
        if( !obstacleNoise.isNull() )
            replyObject->parameters->obstacleNoise =
              obstacleNoise.toDouble();

        const QString motorsNoise = attr.value (QString( "MotorsNoise" ));
        if( !motorsNoise.isNull() )
            replyObject->parameters->motorsNoise = motorsNoise.toDouble();
    }
	else
    {
        cerr << "Failure request: invalid message...\n";
        return false;
    }

	return true;
}

/*---------------------------------------------------------------------------*/
void CRQReplyHandler::setDocumentLocator( QXmlLocator * )
{

}

/*---------------------------------------------------------------------------*/
CRReply * CRQReplyHandler::reply()
{
	return replyObject;
}

