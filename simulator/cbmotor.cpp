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

/*! \file cbmotor.cpp
	\brief Definição dos motores que actuam as rodas dos robôs.

	Os motores são caracterizados por uma potência de entrada, uma potência
	de saída e um coeficiente de ruído.
	Na versão actual as potências de entrada e saída são as mesmas. 
	Quer isto dizer que os motores conseguem comutar instantaneamente
	de uma qualquer potência para outra.
*/

#include "cbutils.h"
#include "cbmotor.h"

#include <stdlib.h>
#include <iostream>

#define MAX_POWER 0.15

cbMotor::cbMotor(void)
{
   inpower=outpower=prevpower=0.0;
}

void cbMotor::setInPower(double p)
{
	if (p > MAX_POWER) p = MAX_POWER;
	else if (p < -MAX_POWER) p = -MAX_POWER;
	inpower = p;
}


/*!
 * Determines and returns the power of the motor in each cycle.
 * Should be called only once per cycle!
 */
double cbMotor::outPower()
{
	double noisepow = randNormal(100.0, noise) / 100.0;

	outpower = (0.5*inpower + 0.5*prevpower) * noisepow;
	prevpower = outpower;

	return outpower;
}

