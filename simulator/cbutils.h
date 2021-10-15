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

/**
 * return a random number.
 * repeated calls to this function with the same mean and stddev
 * result in a sequence of random numbers with normal distribution
 * mean mean and standard deviation stddev
 */
double randNormal(double mean, double stddev);

/**
 * return a random number with uniform distribuition between min and max.
 * repeated calls to this function with the same min and max
 * result in a sequence of random numbers with uniform distribution
 */
double randUniform(double min, double max);

