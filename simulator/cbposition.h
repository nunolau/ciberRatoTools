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

#ifndef CB_POSITION_H
#define CB_POSITION_H


/**
  *@author Nuno Lau, Artur Pereira & Andreia Melo
  */

#include "cbpoint.h"

#include <math.h>

#ifndef M_PI
#ifdef MicWindows
#define M_PI 3.14159265358979
#endif
#endif


/*!
	\class cbPosition
	\brief Represents a point plus direction.
*/

class cbPosition
{
public:
	cbPosition();
	~cbPosition();

	void setCoord(cbPoint &);
	void setRadDirection(double);
	inline void setRadianDirection(double d) { direction = d; }

	void set(double x, double y, double dir);
	
	void setDegDirection(double);

	cbPoint &Coord();
	double X() const;
	double Y() const;
	double radianDirection();
	double degreeDirection();
	inline double Direction() { return direction; }
	inline double directionInDegrees() { return direction*(180/M_PI); }

private:
	cbPoint coord;
	double direction;	// in radians
};

#endif
