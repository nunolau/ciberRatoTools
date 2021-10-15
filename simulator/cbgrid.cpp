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

#include "cbgrid.h"

#include <stdio.h>
#include <stdlib.h>

cbGrid::cbGrid()
{
}

cbGrid::~cbGrid()
{
}

/*!
	fill in xml buffer with grid as xml message.
	Returns the length of the message.
*/
int cbGrid::toXml(char *xml, int n)
{
    int cnt;
    cnt = sprintf(xml, "<Grid>\n");
    for (int i=0; i<count(); i++)
	{
		cbPosition pos = at(i);
        cnt += sprintf(xml+cnt, "\t<Position X=\"%g\" Y=\"%g\" Dir=\"%g\"/>\n",
                       pos.X(), pos.Y(), pos.directionInDegrees());
	}
    cnt += sprintf(xml+cnt, "</Grid>\n");

    if(cnt>n) {
        fprintf(stderr,"cbGrid::toXml message too long\n");
        abort();
    }
              
	return cnt;
}
