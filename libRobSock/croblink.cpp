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
// CRobLink implementation

#include "croblink.h"
#include "structureparser.h"

#include <iostream>

#ifdef CIBERQTAPP
#include <qsocketnotifier.h>
#endif
#include <qxml.h>

using namespace std;

#define MSGMAXSIZE (4096)


/*!
 * Composes register message and sends it to server.
 */
void CRobLink::send_register_message(char *rob_name,int rob_id)
{
    // register in server
	char xml[MSGMAXSIZE];
    const char fmt[] = "<Robot Name=\"%s\" Id=\"%d\"></Robot>";
	sprintf(xml, fmt, rob_name, rob_id);

    if(port.send_info(xml, strlen(xml)+1)!=true)
    {
        // cerr << "Failed Send Init" << endl;
		Status=-1;
		return;
    }
}

void CRobLink::send_register_message(char *rob_name,int rob_id, double irSensorAngles[])
{
    // register in server
	char xml[MSGMAXSIZE];

    int n = sprintf(xml, "<Robot Name=\"%s\" Id=\"%d\">",
                    rob_name, rob_id);

    for(int i=0; i < NUM_IR_SENSORS; i++)
        n += sprintf(xml+n,"<IRSensor Id=\"%d\" Angle=\"%g\"/>",
                     i, irSensorAngles[i]);

	sprintf(xml+n,"</Robot>");

    if(port.send_info(xml, strlen(xml)+1)!=true)
    {
        // cerr << "Failed Send Init" << endl;
		Status=-1;
		return;
    }
}

/*!
 * Composes register message and sends it to server.
 */
void CRobLink::send_robotbeacon_register_message(char *rob_name,int rob_id, double height)
{
    // register in server
	char xml[MSGMAXSIZE];
    const char fmt[] = "<RobotBeacon Name=\"%s\" Id=\"%d\" Height=\"%g\"/>";
	sprintf(xml, fmt, rob_name, rob_id, height);

    if(port.send_info(xml, strlen(xml)+1)!=true)
    {
        // cerr << "Failed Send Init" << endl;
		Status=-1;
		return;
    }
}

/*!
 * Waits for server reply and parses status, simulation parameters and
 * assigns the new UDP port to this robot.
 */
void CRobLink::parse_server_reply(void)
{
    // get reply confirming or denying registration 
    char xml[MSGMAXSIZE];
    int recv_ret = port.recv_info(xml, MSGMAXSIZE);
    if(recv_ret == -1)
    {
        cerr << "Failed Init confirmation" << recv_ret << endl;
		Status = -1;
		return;
    }
    //cerr << "XML=\"" << xml <<"\"\nXMLEND\n";

	/* set source of xml document */
	QXmlInputSource source;
	source.setData(QString(xml));

	/* set parser handler */
    StructureParser handler(simParam.nBeacons);


	/* parse xml document with handler */
    QXmlSimpleReader reader;
    reader.setContentHandler(&handler);
    if( !reader.parse(source) ) {
       Status=-1;
       return;
    }


    simParam = *(handler.getSimParam());
    simParam.showValues();

    port.SetRemote(port.GetLastSender());
}

CRobLink::CRobLink(char *rob_name, int rob_id, char *host) : measures(0), port(6000,host,0)
{
    Status = 0;

    if(!port.init())
	{
        // cerr << "Failed socket init" << endl;
		Status=-1;
		return;
    }

    send_register_message(rob_name, rob_id);
    if( Status != 0 ) return;

    parse_server_reply();
    if( Status != 0 ) return;

#ifdef CIBERQTAPP
    QSocketNotifier *notifier=new QSocketNotifier(port.socketfd,QSocketNotifier::Read);

    QObject::connect(notifier,SIGNAL(activated(int)),this,SIGNAL(NewMessage()));

    notifier->setEnabled(true);
#endif

    Status = 0;
}

CRobLink::CRobLink(char *rob_name, int rob_id, double irSensorAngles[], char *host) :  measures(0), port(6000,host,0)
{
    Status = 0;

    if(!port.init())
	{
        // cerr << "Failed socket init" << endl;
		Status=-1;
		return;
    }

    send_register_message(rob_name,rob_id,irSensorAngles);
    if( Status != 0 ) return;

    parse_server_reply();
    if( Status != 0 ) return;

#ifdef CIBERQTAPP
    QSocketNotifier *notifier=new QSocketNotifier(port.socketfd,QSocketNotifier::Read);

    QObject::connect(notifier,SIGNAL(activated(int)),this,SIGNAL(NewMessage()));

    notifier->setEnabled(true);
#endif

    Status = 0;
}

CRobLink::CRobLink(char *rob_name, int rob_id, double height, char *host) : measures(0), port(6000,host,0) 
{
    Status = 0;

    if(!port.init())
	{
        // cerr << "Failed socket init" << endl;
		Status=-1;
		return;
    }

    send_robotbeacon_register_message(rob_name, rob_id, height);
    if( Status != 0 ) return;

    parse_server_reply();
    if( Status != 0 ) return;

#ifdef CIBERQTAPP
    QSocketNotifier *notifier=new QSocketNotifier(port.socketfd,QSocketNotifier::Read);

    QObject::connect(notifier,SIGNAL(activated(int)),this,SIGNAL(NewMessage()));

    notifier->setEnabled(true);
#endif

    Status = 0;
}

CRobLink::~CRobLink()
{
}

int CRobLink::ReadSensors()
{
	char xml[4096];
    int n = port.recv_info(xml, 4096);
	if (n == -1) return n;

	//cerr << "ReadSensors: " << "\"" << xml << "\"";
	
	/* set source of xml document */
	QXmlInputSource source;
	source.setData(QString(xml));

	/* set parser handler */
    StructureParser handler(simParam.nBeacons);

    //cerr << "ReadSensors: nBeacons=" << simParam.nBeacons << "\n";

	/* parse xml document with handler */
    QXmlSimpleReader reader;
    reader.setContentHandler(&handler);
    reader.parse(source);

	///////////////////////////////////////////////////
	measures = *(handler.getMeasures());  
	//measures.showValues();
	///////////////////////////////////////////////////
	
//    for(unsigned int i=0; i<5;i++)
//       if (measures.hearMessage[i]!=QString())
//           printf("ReadSensors: Message From %d: \"%s\"\n", i, measures.hearMessage[i].latin1());

    return n;
}

void CRobLink::requestGround()
{
    char xml[128];
    const char fmt[] = "<Actions> <SensorRequests Ground=\"Yes\" /> </Actions>\n";
    unsigned int n = sprintf(xml,"%s", fmt);
    port.send_info(xml,n+1);
    //cout << xml;
}

void CRobLink::requestCompass()
{
    char xml[128];
    const char fmt[] = "<Actions> <SensorRequests Compass=\"Yes\" /> </Actions>\n";
    unsigned int n = sprintf(xml, "%s", fmt);
    port.send_info(xml,n+1);
    //cout << xml;
}

void CRobLink::requestBeacon(int id)
{
    char xml[128];
    const char fmt[] = "<Actions> <SensorRequests Beacon%d=\"Yes\" /> </Actions>\n";
    unsigned int n = sprintf(xml, fmt, id);
    port.send_info(xml,n+1);
    //cout << xml;
}

void CRobLink::requestObstacle(int id)
{
    char xml[128];
    const char fmt[] = "<Actions> <SensorRequests IRSensor%d=\"Yes\" /> </Actions>\n";
    unsigned int n = sprintf(xml, fmt, id);
    port.send_info(xml,n+1);
    //cout << xml;
}

void CRobLink::requestSensors(int nReqs, va_list ap)
{
    char *sensId;
    char xml[2048]="<Actions>\n\t<SensorRequests ";
	int  s,n;

	n=strlen(xml);

	for(s=0; s < nReqs; s++) {
	   sensId = va_arg(ap,char *);
	   n += sprintf(xml+n,"%s=\"Yes\" ",sensId);
	}

	n+= sprintf(xml+n,"/>\n</Actions>");

    port.send_info(xml,n+1);
}

void CRobLink::DriveMotors(double lPow,double rPow)
{
    char xml[1024];
    const char fmt[] = "<Actions LeftMotor=\"%g\" RightMotor=\"%g\"/>\n";
	//sprintf(xml, fmt, lPow*1000.0+2000.5, rPow*1000.0+2000.5);
	unsigned int n = sprintf(xml, fmt, lPow, rPow);
    port.send_info(xml,n+1);
	//cout << xml;
}

void CRobLink::Say(char *msg)
{
    char xml[1024];
    const char fmt[] = "<Actions><Say><![CDATA[%s]]></Say></Actions>\n";
    //char *fmt = "<Actions> <Say Ground=\"Yes\"/> </Actions>";
    unsigned int n = sprintf(xml, fmt, msg);
    port.send_info(xml,n+1);
	//cout << xml;
}

void CRobLink::SetReturningLed(bool val)
{
    char xml[128];
    const char fmt[] = "<Actions LeftMotor=\"%g\" RightMotor=\"%g\" ReturningLed=\"%s\"/>\n";
	//sprintf(xml, fmt, lPow*1000.0+2000.5, rPow*1000.0+2000.5, "Off");
	unsigned int n = sprintf(xml, fmt, 0.0, 0.0, (val?"On":"Off"));
    port.send_info(xml,n+1);
	//cout << xml;
}

void CRobLink::SetVisitingLed(bool val)
{
    char xml[128];
    const char fmt[] = "<Actions LeftMotor=\"%g\" RightMotor=\"%g\" VisitingLed=\"%s\"/>\n";
	//sprintf(xml, fmt, lPow*1000.0+2000.5, rPow*1000.0+2000.5, "Off");
	unsigned int n = sprintf(xml, fmt, 0.0, 0.0, (val?"On":"Off"));
    port.send_info(xml,n+1);
	//cout << xml;
}

void CRobLink::Finish(void)
{
	char xml[] = "<Actions LeftMotor=\"0.0\" RightMotor=\"0.0\" EndLed=\"On\"/>\n";
	unsigned int n = strlen(xml);
	//cout << xml;
    port.send_info(xml,n+1);
}

