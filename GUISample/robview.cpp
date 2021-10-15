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

/* robview.cpp
 *
 * Widget that displays robot sensors
 *
 * For more information about the CiberRato Robot Simulator 
 * please see http://microrato.ua.pt/ or contact us.
 */

#include <math.h>
#include <iostream>
using std::cerr;

#include "../libRobSock/RobSock.h"
#include "robview.h"

#ifndef M_PI
#ifdef MicWindows
#define M_PI 3.14159265358979
#endif
#endif



SensorObstItem::SensorObstItem(QGraphicsScene *scene, 
                               double posx, double posy, double dir, double un)
                               : QGraphicsEllipseItem(posx,posy,0, 0, 0, scene)
{

    setStartAngle((int)((dir+60)*16));
    setSpanAngle(60*16);

    setBrush(QBrush("Green"));
    setVisible(true);
    setZValue(12);

	unit=un;
	Dist=0.0;
}

#define MAXDIST 1.0 

void SensorObstItem::setDist(double measure) 
{
    double NewDist;

    if(measure>1/MAXDIST) NewDist=1/measure*unit;
    else NewDist=MAXDIST*unit;
    if(NewDist!=Dist)
    {
        double x = rect().x() - (NewDist - Dist);
        double y = rect().y() - (NewDist - Dist);
        setRect(x, y, NewDist*2, NewDist*2);
        Dist=NewDist;
    }
}

RobScene::RobScene(double irSensorAngles[NUM_IR_SENSORS])
{
    unit=80;
    scene_sizex=3*unit;
    scene_sizey=(int)(3*unit);
	rob_radius=unit/2;

    rob_x = scene_sizex/2 - rob_radius;
    rob_y = scene_sizey/2 - rob_radius;

    setSceneRect(0, 0, scene_sizex, scene_sizey);
    setBackgroundBrush(Qt::white);

    QGraphicsEllipseItem *rob=new QGraphicsEllipseItem(rob_x,rob_y,rob_radius*2,rob_radius*2, 0, this);
    rob->setBrush(QBrush("Blue"));
    rob->setVisible(true);

    compassLine=new QGraphicsLineItem(0, this);
    compassLine->setLine(rob_x + rob_radius, rob_y + rob_radius,
                         rob_x + rob_radius, rob_y + rob_radius);
    compassLine->setZValue(10);
    compassLine->setVisible(true);

    for(int b=0; b<GetNumberOfBeacons();b++) {
        beaconLine.push_back(new QGraphicsLineItem(0, this));
        beaconLine[b]->setLine(rob_x + rob_radius, rob_y + rob_radius,
                               rob_x + rob_radius, rob_y + rob_radius);
        beaconLine[b]->setZValue(11);
        beaconLine[b]->setPen(QPen("Yellow"));
        beaconLine[b]->setVisible(true);
    }

    for(int i=0; i < NUM_IR_SENSORS; i++) {
        sensorObst[i]=new SensorObstItem(this,
                                         (rob_x + rob_radius) - rob_radius*sin(irSensorAngles[i]/180.0*M_PI),
                                         (rob_y + rob_radius) - rob_radius*cos(irSensorAngles[i]/180.0*M_PI),
                                         irSensorAngles[i],unit);
   }

    QGraphicsView view (this);
    view.setCacheMode(QGraphicsView::CacheBackground);
}

void RobScene::redrawRobot(void)
{
    if(IsCompassReady()) {
        double compass=GetCompassSensor()/180.0*M_PI;
        compassLine->setLine(rob_x + rob_radius,rob_y + rob_radius,
                             rob_x + rob_radius + 2.0*rob_radius*sin(-compass),
                             rob_y + rob_radius - 2.0*rob_radius*cos(-compass));
        compassLine->setVisible(true);
    }
    else
        compassLine->setVisible(false);

    for(int b=0; b<GetNumberOfBeacons(); b++) {
        //cerr << "redrawRobot beacon " << b << " of " << GetNumberOfBeacons() << " ready " << IsBeaconReady(b) << " visible " <<GetBeaconSensor(b).beaconVisible << "\n";
        if(IsBeaconReady(b) && GetBeaconSensor(b).beaconVisible) {
            //cerr << "redrawRobot seeing beacon " << b << " at " << GetBeaconSensor(b).beaconDir << "\n";
            double beacon=GetBeaconSensor(b).beaconDir/180.0*M_PI;
            beaconLine[b]->setLine(rob_x + rob_radius, rob_y + rob_radius,
                                   rob_x + rob_radius + 1.6*rob_radius*sin(-beacon),
                                   rob_y + rob_radius - 1.6*rob_radius*cos(-beacon));
            beaconLine[b]->setVisible(true);
        }
        else beaconLine[b]->setVisible(false);
    }

    for(unsigned int i = 0; i < NUM_IR_SENSORS; i++) {
        if(IsObstacleReady(i)) {
            double val=GetObstacleSensor(i);
            sensorObst[i]->setDist(val);
            sensorObst[i]->setVisible(true);
        }
        else sensorObst[i]->setVisible(false);
    }

    update();
}

RobView::RobView(double irSensorAngles[NUM_IR_SENSORS], char *robName)
{
    setWindowTitle(robName);
    QIcon ic(QCoreApplication::applicationDirPath() + "/guilogo.png");
    setWindowIcon(ic);

    robScene=new RobScene(irSensorAngles);
    setScene(robScene);
    resize(sizeHint());
    setMaximumSize(sizeHint());
    setMinimumSize(sizeHint());
}

void RobView::redrawRobot(void)
{
    robScene->redrawRobot();
}
