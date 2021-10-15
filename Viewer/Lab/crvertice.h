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

#ifndef CRVERTICE_H
#define CRVERTICE_H

/*! \class CRVertice
 *  \brief This class implement one basic information, one vertice.
 *
 *  This class is the support for others classes, like the walls, beacon,
 *  target, robots, etc. It is only the defenition of two coordinates,
 *  x and y.
 */
class CRVertice
{
public:
	/*! This is the constructor.
	 * \param x the coordinate x of the point.
	 * \param y the coordinate y of the point.
	 */ 
	CRVertice(float x, float y);
	/*! This is one empty constructor.
	 */
	CRVertice();
	/*! This is the destructor.
	 */
	~CRVertice();
	/*! This function will set the x coordinate of the point.
	 * \param x the coordinate x of the point.
	 */
    void setX(float x);
	/*! This function will set the y coordinate of the point.
	 * \param y the coordinate y of the point.
	 */
    void setY(float y);
	/*! This function returns the x coordinate of the point.
	 */
    float x();
	/*! This function returns the y coordinate of the point.
	 */
    float y();
 
private:
	float xf,yf; 
};
#endif
