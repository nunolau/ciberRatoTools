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

#ifndef CBWALL_H
#define CBWALL_H

/**
  *@author Nuno Lau, Artur Pereira & Andreia Melo
  */

#include "cbpoint.h"

#include <vector>
using std::vector;

/**
 * models a wall of the labirinth
 */
class cbWall
{
public:
	cbWall();
	~cbWall();

	void setHeight(double);
	void addCorner(cbPoint&);
	void addCorner(double, double);

	double Height();
	vector<cbPoint> &Corners();
	double  cornerAngle(unsigned int c);
	bool    convexCorner(unsigned int c);

	double distance(cbPoint &);
	double distance(cbPoint &, double theta);
	double cornerDistance(cbPoint &, double, double);

	inline unsigned int count() { return corners.size(); }

	inline cbPoint &operator[](int i) { return corners[i]; }

	void showCorners();

	bool orderCornersAntiClockwise(void);

private:
        void invertCornerOrder(void);

	double height;				// height of the wall
	vector<cbPoint> corners;	// corners of the wall
};

#endif
