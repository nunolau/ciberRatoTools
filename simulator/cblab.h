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

#ifndef CBLAB_H
#define CBLAB_H

/**
  *@author Nuno Lau, Artur Pereira & Andreia Melo, Miguel Rodrigues
  */

#include "cbwall.h"
#include "cbtarget.h"
#include "cbbeacon.h"

#include <vector>
using std::vector;

/**
 * models the labirinth where robots move
 */
class cbLab
{
public:
	cbLab();
	~cbLab();

	void setName(const char *);
	void setHeight(double);
	void setWidth(double);

    const char * Name (void);
    double Height(void) { return height; }
    double Width(void)  { return width;  }

    void addTarget(cbTarget *);
    unsigned int    nTargets(void) { return targets.size();}
    void addBeacon(cbBeacon *);
    unsigned int    nBeacons(void) { return beacons.size();}

	void addWall(cbWall *wall);

	double wallDistance(cbPoint &);
    double wallDistance(cbPoint &, double);
    double wallDistanceAboveHeight(cbPoint &p, double dir, double height);
	double cornerDistance(cbPoint &, double, double);

	inline cbTarget *Target(int i) { return targets[i]; }
	inline cbBeacon *Beacon(int i) { return beacons[i]; }

	int toXml(char *buff, int n);

    bool reachable(cbPoint i, cbPoint f);
    bool reachableRobot(cbPoint i, cbPoint f);

    unsigned int    nWalls(void) { return walls.size();}
    cbWall * Wall(int index) { return walls[index];}
private:
	
    const char *name;		// the name of the lab (default "NO NAME LAB")
	double height, width;	// the height and width (default 16.0 for both)

	/* the lab is assumed to have a rectangular border.
	 * By implementation reasons, this border is defined as a wall,
	 * with 4 corners. These corners are stored into the array
	 * in the following order: left-bottom, left-top, right-top and
	 * right-bottom.
	 * The left-bottom corner has coordinates 0,0. */
	//cbWall border;

	/* objects 'living' in lab */
	vector<cbBeacon *> beacons;		// the beacon
	vector<cbTarget *> targets;		// the target
    vector< cbWall * > walls;       // the walls
};

#endif
