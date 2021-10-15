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

#include"crvertice.h"
/* **************************************************************************
 * * Vertices (x,y)                                                         *
 * **************************************************************************
 */

CRVertice::CRVertice()
{
	xf=0.0;
	yf=0.0;
}
CRVertice::CRVertice(float x_value=0, float y_value=0)
{
	xf=x_value;
	yf=y_value;
}

CRVertice::~CRVertice()
{}

void CRVertice::setX(float x_value)
{
 xf=x_value; 
}

void CRVertice::setY(float y_value)
{
 yf=y_value; 
}

float CRVertice::x()
{
	return xf;
}

float CRVertice::y()
{
	return yf;
}

