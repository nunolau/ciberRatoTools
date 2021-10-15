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

#ifndef CBPOINT_H
#define CBPOINT_H

/**
  *@author Nuno Lau, Artur Pereira & Andreia Melo
  */

/*!
	\class cbPoint
	\brief Stores the cartesian coordinates of a point, and make
		available some point operation.
*/	
class cbPoint
{
public:
	cbPoint();
	cbPoint(double xi, double yi);
	~cbPoint();

	inline void set(double a, double b) { x=a; y=b; }
	void setX(double);
	void setY(double);

	double X() const;
	double Y() const;

	double distance(cbPoint &);
	inline double distance(cbPoint *pt) { return distance(*pt); }
	double distance(double, double);

	double angle(void);
	double angle(cbPoint &);
	inline double angle(cbPoint *pt) { return angle(*pt); }

	cbPoint & normalize(void);
	cbPoint & rotate(double angle);

	inline bool operator==(const cbPoint &p) { return p.x==x && p.y==y; }
	cbPoint operator-(const cbPoint &other);
	cbPoint operator+(const cbPoint &other);
	cbPoint operator*(const double scale);

public:
	double x, y;
};


/*!
	\class cbPolarPoint
	\brief Stores the polar coordinates of a point.
*/
class cbPolarPoint
{
public:
	cbPolarPoint();
	~cbPolarPoint();

public:
	double ro, theta;
};
#endif
