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
	\brief Defini��o dos motores que actuam as rodas dos rob�s.

	Os motores s�o caracterizados por uma pot�ncia de entrada, uma pot�ncia
	de sa�da e um coeficiente de ru�do.
	Na vers�o actual as pot�ncias de entrada e sa�da s�o as mesmas.
	Quer isto dizer que os motores conseguem comutar instantaneamente
	de uma qualquer pot�ncia para outra.
*/

#include "cbutils.h"
#include "cbmotor.h"

#include <stdlib.h>
#include <iostream>

// PF: MAX_POWER set to 1
#define MAX_POWER 3

cbMotor::cbMotor(void)
{
   inpower=outpower=prevpower=0.0;
   a=0.1;
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
  static unsigned int counter=0;
	double noisepow = randNormal(100.0, noise) / 100.0;

  counter++;


#if 0
  // At time=100, change the time constant
  if(counter == 201){
    a = a/2;
  }
#endif

// PF: changed transfer function
// outpower = (0.5*inpower + 0.5*prevpower) * noisepow;

  outpower = (a*inpower + (1-a)*prevpower);
	prevpower = outpower;

	return outpower;
}
