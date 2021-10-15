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

#ifndef CBTARGET_H
#define CBTARGET_H

/**
  *@author Nuno Lau, Artur Pereira & Andreia Melo
  */

#include "cbpoint.h"

/**
 * Models the target zone positioned inside the labirith.
 */
class cbTarget
{
public:
	cbTarget();
	~cbTarget();

	void setCenter(cbPoint &);
	void setRadius(double);

	cbPoint &Center();
	double Radius();

	bool contains(cbPoint &pt, double margin);

private:
	cbPoint center;
	double radius;
};

#endif
