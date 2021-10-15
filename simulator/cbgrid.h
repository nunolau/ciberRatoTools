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

#ifndef CB_GRID_H
#define CB_GRID_H


/**
  *@author Nuno Lau, Artur Pereira & Andreia Melo, Miguel Rodrigues
  */

#include "cbposition.h"

#include <QVector>

/*!
	\class cbGrid
	\brief Represents an array of cbPositions with some
		additional functionality.
*/
class cbGrid : public QVector<cbPosition>
{
public:
	cbGrid();
	~cbGrid();

	int toXml(char *buff, int cnt);

private:
};

#endif
