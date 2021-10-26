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

#ifndef CB_MOTOR_H
#define CB_MOTOR_H

/*! \file cbmotor.h
	\brief Defini��o dos motores que actuam as rodas dos rob�s.

	Os motores s�o caracterizados por uma pot�ncia de entrada, uma pot�ncia
	de sa�da e um coeficiente de ru�do.
	Na vers�o actual a pot�ncias de sa�da depende da pot�ncia de entrada e
	do valor anterior da pot�ncia. O valor � sa�da � o valor da entrada
	filtrado atrav�s de um filtro passa-baixo.
*/
class cbMotor
{
public:	// class data members
	static double noise;
        cbMotor(void);

public:	// member functions
	void setInPower(double);
	double outPower();
	inline double lastOutPower() { return outpower; }
	inline double inPower() { return inpower; }


private:	// object data members
	double inpower, outpower;
	double prevpower;
  double a;         // TF time constant
};

#endif
