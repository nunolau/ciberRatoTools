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

#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#ifdef MicWindows
#define M_PI 3.14159265358979
#endif
#endif

/*! 
 * Returns a random number with a normal distribution (in successive calls)
 * of mean mean and standard deviation stddev.
 * Uses the Box-Muller transform
 */
double randNormal(double mean, double stddev)
{
	double x,y,r;
	
	do {
	        x = 2.0 * ((double)rand() / ((double)RAND_MAX + 1.0)) - 1.0;
	        y = 2.0 * ((double)rand() / ((double)RAND_MAX + 1.0)) - 1.0;
		r = x*x + y*y;
	} while( r > 1.0 );

	return x*sqrt((-2.0*log(r))/r)*stddev+mean;
}

double randUniform(double min, double max)
{

	return min + ((double)rand() / ((double)RAND_MAX + 1.0)) * (max - min) ;
}

