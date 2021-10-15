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
 * class cbParamHandler
 */
 
#include "cbparamhandler.h"

#include <qstring.h>

cbParamHandler::cbParamHandler(QXmlReader *rd, 
		           QXmlDefaultHandler * const ph,
			   const QXmlAttributes &attr) {
	    parentHandler=ph;
	    reader=rd;

	    param = new cbParameters;

		const QString &simtime = attr.value(QString("SimTime"));
		if (!simtime.isNull()) param->simTime = simtime.toUInt();
		const QString &cycletime = attr.value(QString("CycleTime"));
		if (!cycletime.isNull()) param->cycleTime = cycletime.toUInt();
		const QString &compassnoise = attr.value(QString("CompassNoise"));
		if (!compassnoise.isNull()) param->compassNoise = compassnoise.toDouble();
		const QString &beaconnoise = attr.value(QString("BeaconNoise"));
		if (!beaconnoise.isNull()) param->beaconNoise = beaconnoise.toDouble();
		const QString &obstaclenoise = attr.value(QString("ObstacleNoise"));
		if (!obstaclenoise.isNull()) param->obstacleNoise = obstaclenoise.toDouble();
		const QString &motorsnoise = attr.value(QString("MotorsNoise"));
		if (!motorsnoise.isNull()) param->motorsNoise = motorsnoise.toDouble();
}
 
 
bool cbParamHandler::startDocument()
{
	param = 0;
    return TRUE;
}

bool cbParamHandler::endDocument()
{
	return TRUE;
}

bool cbParamHandler::startElement( const QString&, const QString&, const QString& qName, 
                                    const QXmlAttributes& attr)
{
	/* process begin tag */
	const QString &tag = qName;
	if (tag == "Parameters")
	{
		param = new cbParameters;
		/* process attributes */
		const QString &simtime = attr.value(QString("SimTime"));
		if (!simtime.isNull()) param->simTime = simtime.toUInt();
		const QString &cycletime = attr.value(QString("CycleTime"));
		if (!cycletime.isNull()) param->cycleTime = cycletime.toUInt();
		const QString &compassnoise = attr.value(QString("CompassNoise"));
		if (!compassnoise.isNull()) param->compassNoise = compassnoise.toDouble();
		const QString &beaconnoise = attr.value(QString("BeaconNoise"));
		if (!beaconnoise.isNull()) param->beaconNoise = beaconnoise.toDouble();
		const QString &obstaclenoise = attr.value(QString("ObstacleNoise"));
		if (!obstaclenoise.isNull()) param->obstacleNoise = obstaclenoise.toDouble();
		const QString &motorsnoise = attr.value(QString("MotorsNoise"));
		if (!motorsnoise.isNull()) param->motorsNoise = motorsnoise.toDouble();
	}
    return TRUE;
}

bool cbParamHandler::endElement( const QString&, const QString&, const QString& qName)
{
	/* process end tag */
	const QString &tag = qName;
	if (tag == "Parameters")
	{
		if(reader!=0)
		    reader->setContentHandler(parentHandler);
		
	}
    return TRUE;
}

void cbParamHandler::setDocumentLocator(QXmlLocator *)
{
}


/* extra functions */

cbParameters *cbParamHandler::parsedParameters()
{
	return param;
}
