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

#include "cbutils.h"
#include "cbsensor.h"
#include "cbbeacon.h"
#include "cbrobot.h"
#include "cblab.h"

#include <stdlib.h>
#include <iostream>
#include <math.h>
#ifndef M_PI
#ifdef MicWindows
#define M_PI 3.14159265358979
#endif
#endif

using std::cerr;

cbMeasure::cbMeasure(void)
{
}

cbBoolMeasure::cbBoolMeasure(bool val) 
{
	value=val;
}

cbIntMeasure::cbIntMeasure(int val) 
{
	value=val;
}

cbDoubleMeasure::cbDoubleMeasure(double val) 
{
	value=val;
}

cbBeaconMeasure::cbBeaconMeasure(struct beaconMeasure val) 
{
	value=val;
}

cbGPSMeasure::cbGPSMeasure(struct GPSMeasure val) 
{
	value=val;
}

cbSensor::cbSensor(cbRobot *rob, QString sId)
{
	robot=rob;
	requested   = false;
    requestable = true;
	//requestable = false; //DEBUG

	strId = sId;

	setFifoLatency(0);
}

cbSensor::~cbSensor()
{
}

void cbSensor::setFifoLatency(unsigned int fLatency) {
	unsigned int fSize = fLatency + 1;
	if(measuresFIFO.size()<fSize) {
		for(unsigned int i=measuresFIFO.size(); i < fSize; i++)
			measuresFIFO.push(0);
	}
	else {
		while(measuresFIFO.size() > fSize)
			measuresFIFO.pop();
	}
}

void cbSensor::pushMeasure(cbMeasure *value) {
	measuresFIFO.push(value);
}

void cbSensor::popMeasure(void) {
	delete readMeasure();
	measuresFIFO.pop();
}

cbMeasure* cbSensor::readMeasure(void) {
	return measuresFIFO.front();
}

/*******************************************************/
// cbcbollisionSensor

cbCollisionSensor::cbCollisionSensor(cbRobot *rob, QString sId) : cbSensor(rob,sId)
{
	value=false;
}

cbCollisionSensor::~cbCollisionSensor()
{
}

void cbCollisionSensor::update()
{
	popMeasure();
	update(robot->hasCollide());

	pushMeasure(new cbBoolMeasure(value));
}

/*******************************************************/
// cbGroundSensor

cbGroundSensor::cbGroundSensor(cbRobot *rob, QString sId) : cbSensor(rob,sId)
{
	value=-1;
}

cbGroundSensor::~cbGroundSensor()
{
}

void cbGroundSensor::update()
{
	popMeasure();
	int v;
	if(robot->getSimulator()->Lab()->nTargets()==0)
	{
		v=-1;
	}
	else {
		v=-1;
	       for(unsigned i=0; i<robot->getSimulator()->Lab()->nTargets();i++)
	       {
	           cbTarget *t = robot->getSimulator()->Lab()->Target(i);
	           if(t->contains(robot->Center(), ROBOT_RADIUS)) {
			   v=i;
		   }
				   
	       }
	}
	//cout.form("target contains = %s\n", v?"Yes":"No");
	value = v;

	pushMeasure(new cbIntMeasure(value));
}
/*******************************************************/
// cbCompassSensor

cbCompassSensor::cbCompassSensor(cbRobot *rob, QString sId) : cbSensor(rob,sId)
{
	ideal=value=degrees=0.0;
}

cbCompassSensor::~cbCompassSensor()
{
}

void cbCompassSensor::update()
{
	popMeasure();

	double dir = robot->Dir();
	update(dir);
	//cout.form("compassSensor.update(%g)\n", dir);
	
	pushMeasure(new cbDoubleMeasure(degrees));
}

/*!
	update orientation read by sensor based on
	real orientation of robot.
	Currently, just some noise is added to the real value.
*/
void cbCompassSensor::update(double orientation)
{
	/* ideal value */
	ideal = orientation;
	/* noisy value */
	double randNoise = randNormal(0.0,noise);
	value = orientation + randNoise;
	if (value > M_PI) value -= (2*M_PI); else if (value < -M_PI) value += (2*M_PI);
	/* noisy value in degrees round to integer */
	degrees = floor(value*180/M_PI + 0.5);
}

/*******************************************************/
// cbBeaconSensor

cbBeaconSensor::cbBeaconSensor(cbRobot *rob, QString sId) : cbSensor(rob,sId)
{
	measure.beaconVisible=false;
	measure.beaconDir=0.0;

	ideal=value=0.0;
	beaconToFollow=0;

	latency = 1;
	cycToMeasure=latency;
	ready=false;
}

cbBeaconSensor::~cbBeaconSensor()
{
}

/*!
	update sensor measure based on real angular direction
	of the beacon.
	Currently, it just add some noise to the real measure.
*/
void cbBeaconSensor::update()
{
	popMeasure();

	cbBeacon *b = robot->getSimulator()->Lab()->Beacon(beaconToFollow);
	cbLab *lab=robot->getSimulator()->Lab();
	double delta = robot->Center().angle(b->Center()) - robot->Dir();

	if (delta > M_PI) delta -= (2*M_PI);
	else if (delta < -M_PI) delta += (2*M_PI);

	if(cycToMeasure>1) {
		cycToMeasure--;  // no update, wait cycToMeasureCycles
		ready = false;
		resetBeaconVisible();  // invalidate Measure
	}
	else {
             double distRobotToBeacon = robot->Center().distance(b->Center());
             if( distRobotToBeacon > 1e10 ) {   // BEACON_DISTANCE_LIMIT 5.0 for CiberRato competitions
	         resetBeaconVisible();
             }
             else {
	     //check if there is a wall hiding beacon
	         double distShadow = lab->wallDistanceAboveHeight(robot->Center(),robot->Center().angle(b->Center()),b->Height());
	         if( distShadow !=-1 && distShadow < robot->Center().distance(b->Center())) 
	              resetBeaconVisible();
	         else {
	             measure.beaconVisible=true;
	             /* ideal value */
	             ideal = delta;
	             /* noisy value */
	             double randNoise = randNormal(0.0,noise);
	             value = delta + randNoise;
	             if (value > M_PI) value -= 2*M_PI; else if (value < -M_PI) value += 2*M_PI;

	             // check sensor aperture
                     //if(fabs(value) <= M_PI/3)
                     if(fabs(value) <= sensorAperture)
	                 /* noisy value in degrees round to integer */
	                 measure.beaconDir = floor(value*180.0/M_PI + 0.5);
	             else
                         resetBeaconVisible();
                 }
	     }

	     cycToMeasure = latency;
	     ready=true;
	}
	//cerr << "beacon_update ready = " << ready << " dir = " << measure.beaconDir << " visible = " << measure.beaconDir << "\n";
	
	pushMeasure(new cbBeaconMeasure(measure));
}

/*******************************************************/
/* IRSensor */

cbIRSensor::cbIRSensor(cbRobot *rob, QString sId) : cbSensor(rob,sId)
{
	value=ideal=0.0;
}

cbIRSensor::~cbIRSensor()
{
}

/*!
	Update sensor measure.
	Update sensor output based on real obstacle 
	distance and random noise.
	Sensor output saturates at 100.0.
*/
void cbIRSensor::update(double distance)
{
	/* determine sensor ideal output based on distance */
	if (distance > 0.01) ideal = 1.0 / distance;
	else ideal = 100.0;
	/* real output is ideal output plus random noise */
	double randNoise = randNormal(0.0,noise);
	/* round to 0.1 precision */
	value = floor(10.0*(ideal + randNoise)+0.5)/10.0;
}

/*!
	Update infra-red sensors.
	update length measure of every infra-red sensor based on
	real distance to nearest obstacle.
*/
void cbIRSensor::update(void)
{
	popMeasure();
	/* update infra-red sensors */
	//cout.form("Updating IRSensors for robot[%u,%g,%g,%g]\n", id, X(), Y(), Dir());
	
		/* determine absolute sensor position */
	cbPolarPoint pp = position();
	double x = robot->X() + pp.ro * cos(pp.theta + robot->Dir());
	double y = robot->Y() + pp.ro * sin(pp.theta + robot->Dir());
	cbPoint p;
	p.set(x,y);
	double theta = robot->Dir() + pp.theta;
	if (theta > M_PI) theta -= (2*M_PI);
	else if (theta < -M_PI) theta += (2*M_PI);

		//cout.form("Sensor[%u], RelativePos[%g,%g], AbsolutePos[%g,%g], Dir[%g]\n",
				//i, pp.ro, pp.theta, x, y, theta);

	/* get distance to neareast wall point cover by the sensor */
	cbLab *lab = robot->getSimulator()->Lab();
	double min = lab->wallDistance(p,theta);

	double dist = lab->wallDistance(p,theta+M_PI/6);
	if (dist != -1 && (min == -1 || dist < min)) min = dist;

	dist = lab->wallDistance(p,theta-M_PI/6);
	if (dist != -1 && (min == -1 || dist < min)) min = dist;

	dist = lab->cornerDistance(p,theta,M_PI/6);
	if (dist != -1 && (min == -1 || dist < min)) min = dist;

    /* check presence of other robots in sensor action cone */
    vector<cbRobot*> *others = &(robot->getSimulator()->Robots());
    for (unsigned r=0; r<others->size() && !cbRobot::ignoreOthers; r++)
	{
		cbRobot *other = (*others)[r];
		if (other == 0) continue;
		
		/* skip robot if it was removed or if it is the same */
		if (other->state() == cbRobot::REMOVED || other == robot) continue;

		/* Determine angular difference between robot position
		 * and sensor central radial line. */
		double phi = p.angle(other->Center());
		double delta = fabs(theta-phi);
		if (delta > M_PI) delta = 2*M_PI-delta;
		
		/* determine distance from sensor to other robot center. */
		double D = p.distance(other->Center());

		/* determina a distancia angular desde que o centro do
		 * robot deixa de ser visto pelo sensor ate que o robot
		 * deixa de ser visto por completo, ou seja, considera-se
		 * o círculo do robot tangente a linha limite do cone de
		 * visão do sensor. */
		double margin = asin(ROBOT_RADIUS/D);
		
		/* determine distance from sensor to robot */
		if (delta > M_PI/6+margin)	// robot is not seen
		{
			dist = -1;
		}
		else if (delta <= M_PI/6) // robot center is seen
		{
			dist = D - ROBOT_RADIUS;
		}
		else // robot is seen but its center is not
		{
			double psi = delta - M_PI/6;
			double L2 = D*sin(psi);
			dist = D*cos(psi) - sqrt(ROBOT_RADIUS*ROBOT_RADIUS - L2*L2);
		}

		/* update current minimal distance */
		if (dist != -1 && (min == -1 || dist < min)) min = dist;
	}

	/* update sensor measure */
	update(min);
	//cout.form("robot[%u,%g,%g,%g].irSensor[%u].update(%g); value = %g\n", 
			//id, X(), Y(), Dir(), i, min, irSensors[i].Value());
	pushMeasure(new cbDoubleMeasure(value));
}

/*******************************************************/
// cbGPSSensor

cbGPSSensor::cbGPSSensor(cbRobot *rob, QString sId) : cbSensor(rob,sId)
{
	value.x = 0.0;
	value.y = 0.0;
	value.degrees = 0.0;
}

cbGPSSensor::~cbGPSSensor()
{
}

void cbGPSSensor::update()
{
        GPSMeasure ideal;
	popMeasure();

	ideal.x = robot->X();
	ideal.y = robot->Y();
	ideal.degrees = robot->Degrees();

	update(ideal);
	//cout.form("compassSensor.update(%g)\n", dir);
	
	pushMeasure(new cbGPSMeasure(value));
}


/*!
	update orientation read by sensor based on
	real orientation of robot.
	Currently, just some noise is added to the real value.
*/
void cbGPSSensor::update(GPSMeasure ideal)
{
	/* noisy value */
	value.x = ideal.x + randNormal(0.0,noiseLin) + offsetX;
	value.y = ideal.y + randNormal(0.0,noiseLin) + offsetY;
	value.degrees = ideal.degrees + randNormal(0.0,noiseAng) + offsetDeg;

    /* truncate to precision */
    value.x = floor(value.x*10.0+0.5)/10.0;
    value.y = floor(value.y*10.0+0.5)/10.0;
	value.degrees = floor(value.degrees + 0.5);

    while (value.degrees > 180.0) value.degrees -= 360.0;
    while (value.degrees < -180.0) value.degrees += (360.0);
}

