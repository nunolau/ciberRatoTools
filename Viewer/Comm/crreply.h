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

#ifndef _CIBER_RATO_CRREPLY_
#define _CIBER_RATO_CRREPLY_

/*! \struct crreply
 * \brief This struct represent one reply message.
 */

typedef struct crreply
{
	/*! Status of the reply message from the simulator.
	 *  Ok == true, NotOk == false.
	 */
	bool status;
	/*! Simulation parameters. Noise levels, simulation and cycle times, etc.
	 */
	struct crparameters *parameters;
} CRReply;

	/*! \struct crparameters
	 * \brief All the simulation parameters are received into a structure
	 * like this.
	 */
typedef struct crparameters
{
	/*! Each simulation cycle time.
	 */
	unsigned int cycleTime;
	/*! Total simulation time.
	 */
	unsigned int simTime;
	/*! Compass noise level.
	 */
	unsigned int compassTime;
	/*! Beacon noise level.
	 */
	double beaconNoise;
	/*! Obstacle sensors noise level.
	 */
	double obstacleNoise;
	/*! Motors noise level (error).
	 */
	double motorsNoise;
} CRParameters;

#endif
