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

#ifndef CRGRID_H
#define CRGRID_H
/*! \class CRGrid
 *  \brief Implementation of the start positions
 *
 *  An object of this type is to be added to the lab we'll be using during the
 *  contest to define the start grid for the robots.
 */

#include"crvertice.h"
#include<vector>

using namespace std;

/*! \struct CRGridElement
 * This structure defines an element of the start grid
 */
typedef struct 
{
		/*! position is a point in the lab
		 */
       	CRVertice position;
		/*! direction is an angle in degrees that defines the orientation
		 */
        float direction;
} CRGridElement;                                                                      

class CRGrid
{
	public:
		/*! This is the constructor.
		 */
		CRGrid( void );

		/*! This is the destructor.
		 */
		~CRGrid( void );

		/*! With this we add one CRGridElement to the grid
			\param element is the CRGridElement 
			\sa CRGridElement
		 */
		int addPosition( CRGridElement *element );

		/*! Returns the number of start positions available in the grid
		 *  \sa addPosition( CRGridElement *element )
		 */
		int howManyPositions( void );

		/*! Returns the CRGridElement number index
		 *  \sa howManyPositions( void )
		 *  \sa CRGridElement
		 */
		CRGridElement* getPosition( int index );

	private:
		vector<CRGridElement> elementList;
		int numberOfElements;

};

#endif
