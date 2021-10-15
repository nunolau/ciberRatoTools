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
#ifndef CRBEACON_H
#define CRBEACON_H

/*! \class CRBeacon
 *  \brief This class implement one beacon. 
 *
 *  The beacon is only one point (x, y) and one height. It is used to
 *  define the the finish spot of a lab. In the real Micro-Rato environment
 *  the beacon emits Infra-Red light that allows the robots to determine
 *  where the finish is.
 */


class CRBeacon
{
public:
	/*! This is the constuctor
	 *  \param pos is the position of the beacon in the lab.
	 *  \param Height is the height of the beacon relative to walls.
	 */
	CRBeacon( CRVertice pos, float Height=1.0 );
	/*! This is the destructor.
	 */
	~CRBeacon();
	/*! This function will set the beacon position in the lab.
	 *  \param pos is the positon of the beacon on the lab.
	 */
	void setBeacon( CRVertice pos ); 
	/*! This function returns the position of the beacon in the lab.
	 */
	CRVertice beacon(); 
	/*! This function will set the beacon height.
	 *  \param Height is the height of the beacon.
	 */
	void setBeaconHeight( float Height );
	/*! This function returns the beacon height.
	 */
	float beaconHeight();

private:
	CRVertice bPosition;
	float bHeight;
};
#endif
