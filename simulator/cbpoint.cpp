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

#include <math.h>
#ifndef M_PI
#ifdef MicWindows
#define M_PI 3.14159265358979
#endif
#endif

#include "cbpoint.h"

cbPoint::cbPoint()
{
	x = y = 0.0;
}

cbPoint::cbPoint(double xi, double yi)
{
	x = xi;
	y = yi;
}

cbPoint::~cbPoint()
{
}

void cbPoint::setX(double xx)
{
	x = xx;
}

void cbPoint::setY(double yy)
{
	y = yy;
}

double cbPoint::X() const
{
	return x;
}

double cbPoint::Y() const
{
	return y;
}

double cbPoint::distance(cbPoint &p)
{
	double xx = x - p.x;
	double yy = y - p.y;
	return sqrt(xx*xx + yy*yy);
}

double cbPoint::distance(double px, double py)
{
	double xx = x - px;
	double yy = y - py;
	return sqrt(xx*xx + yy*yy);
}

double cbPoint::angle(void)
{
	if (x == 0.0) return (y > 0.0) ? M_PI/2.0 : -M_PI/2;
	return atan2(y, x);
}

double cbPoint::angle(cbPoint &p)
{
	if (x == p.x) return (p.y > y) ? M_PI/2.0 : -M_PI/2;
	return atan2(p.y-y, p.x-x);
}

cbPoint &cbPoint::normalize(void)
{
	if(x*x+y*y==0.0) return *this;

	double size=sqrt(x*x+y*y);
	x/=size;
	y/=size;

	return *this;
}

cbPoint &cbPoint::rotate(double angle)
{
	double prev_x=x, prev_y=y;
	x=prev_x*cos(angle)-prev_y*sin(angle);
	y=prev_x*sin(angle)+prev_y*cos(angle);

	return *this;
}

cbPoint cbPoint::operator+(const cbPoint &other)
{
    return cbPoint(x+other.x,y+other.y); 
}

cbPoint cbPoint::operator-(const cbPoint &other)
{
    return cbPoint(x-other.x,y-other.y); 
}

cbPoint cbPoint::operator*(const double scale)
{
    return cbPoint(x*scale,y*scale); 
}

/*************************************/

cbPolarPoint::cbPolarPoint()
{
	ro = theta = 0.0;
}

cbPolarPoint::~cbPolarPoint()
{
}
