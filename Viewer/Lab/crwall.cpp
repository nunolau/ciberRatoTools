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

#include"crwall.h"
/* **************************************************************************
 * * Walls definition (Set of vertices with an height)                      *
 * **************************************************************************
 */

CRWall::CRWall( )
{
	vList.clear();
	wHeight = 0.0;
}

CRWall::CRWall( vector<CRVertice> *points, float wallHeight) // Automatic process
{
	vList = *points;
    wHeight=wallHeight;
}
CRWall::~CRWall()
{}

void CRWall::addCorner( CRVertice vertex )
{
	vList.push_back( vertex );

}
vector<CRVertice>* CRWall::wallVectRef()
{
 return (&vList);
}


void CRWall::setWallHeight( float height )
{
	wHeight=height;
}

float CRWall::wallHeight()
{
	return wHeight;
}
