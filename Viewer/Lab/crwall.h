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
#include<vector>
#ifndef CRWALL_H
#define CRWALL_H

using namespace std;

/*! \class CRWall
 * \brief This class implements one wall
 *
 * A wall is a set of points with an height.
 */
class CRWall
{
public:
	/*! Constructor. Builds a new empty wall.
	 */
	CRWall( ); 
	/*! Constructor. Builds a wall with the following parameters.
	 * \param points are the set of CRVertices.
	 * \param wallHeight is the height to be compared to the beacon.
	 */
	CRWall( vector<CRVertice> *points, float wallHeight=0.0 ); // Automatic process
	/*! Destructor.
	 */
	~CRWall(); // Erases the vector

	/*! Returns a pointer to the CRVertices.
	 */
	vector<CRVertice> *wallVectRef(); // Returns the pointer to the vector List

	/*! Sets the wall height to a new value.
	 * \param wallHeight is the new height.
	 */
	void setWallHeight( float wallHeight );
	/*! Returns the current wall height.
	 */
	float wallHeight();

	/*! Adds a new CRVertice to the vertices vector.
	 * \param vertex is the new vertex.
	 */
	void addCorner( CRVertice vertex );

private:
	vector<CRVertice> vList;	
	float wHeight;
};
#endif
