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

#ifndef CRTARGET_H
#define CRTARGET_H
#include"crvertice.h"

/*! \class CRTarget
 * 	\brief This class implement the lab target area. 
 *
 * 	Is only one point and one radius.
 * 	The target area is circular and it's where the robots are supposed to stop
 * 	when they finish the lab.
 */

class CRTarget
{
public:
	/*! This is the constructor.
	 * \param pos is the position of the target area in the lab.
	 * \param radius is the radius of the target area.
	 */
	CRTarget( CRVertice pos, float radius );
	/*! This is one empty constructor.
	 */
	CRTarget( ); 					
	/*! This is the destructor.
	 */
	~CRTarget();
	/*! This function will set the position of the target area on the lab.
	 * \param pos the position of the target area in the lab.
	 */
	void setPosition( CRVertice pos );
	/*! This function retuns the position of the target area in the lab.
	 */
	CRVertice Position();           
	/*! This function will set the radius of the target area.
	 *  \param radius the radius of the target area.
	 */
	void setRadius( float radius );
	/*! This function returns the radius of the target area.
	 */
	float radius();   

private:
	CRVertice aPosition;
	float aRadius;
};
#endif
