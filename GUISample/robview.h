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

/* robview.h
 *
 * Interface of Widget that displays robot sensors
 *
 * For more information about the CiberRato Robot Simulator 
 * please see http://microrato.ua.pt/ or contact us.
 */

#include <QtGui>

#include <vector>

using std::vector;

#define NUM_IR_SENSORS 4

class SensorObstItem: public QGraphicsEllipseItem
{
public:
      SensorObstItem(QGraphicsScene *scene, double posx, double posy, double dir, double un);
      void setDist(double measure);
private:
      double Dist;
      double unit;
};

class RobScene: public QGraphicsScene
{
public:
    RobScene(double irSensorAngles[]);
    void redrawRobot(void);
private:
    QGraphicsLineItem *compassLine;
    vector<QGraphicsLineItem *> beaconLine;
    SensorObstItem *sensorObst[NUM_IR_SENSORS];

    double unit, scene_sizex, scene_sizey, rob_radius, rob_x, rob_y;
};

class RobView: public QGraphicsView
{
  Q_OBJECT
public:
    RobView(double irSensorAngles[], char *rob_name);
public slots:
    void redrawRobot(void);
private:
    RobScene *robScene;
};

