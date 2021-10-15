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

/**
  *@author Nuno Lau, Artur Pereira & Andreia Melo
  */

#include "cbposition.h"

#include <math.h>

cbPosition::cbPosition()
{
	coord = cbPoint();
	direction = 0.0;
}

cbPosition::~cbPosition()
{
}

void cbPosition::setCoord(cbPoint &p)
{
	coord = p;
}

void cbPosition::setRadDirection(double r)
{
	direction = r;
}

void cbPosition::setDegDirection(double d)
{
	direction = (d * M_PI) / 180;
}

cbPoint &cbPosition::Coord()
{
	return coord;
}

double cbPosition::X() const
{
	return coord.X();
}

double cbPosition::Y() const
{
	return coord.Y();
}

double cbPosition::radianDirection()
{
	return direction;
}

double cbPosition::degreeDirection()
{
	return (180 * direction) / M_PI;
}

void cbPosition::set(double x, double y, double dir)
{
	direction = dir;
	coord.x = x;
	coord.y = y;
}
