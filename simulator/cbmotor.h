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
	\brief Definição dos motores que actuam as rodas dos robôs.

	Os motores são caracterizados por uma potência de entrada, uma potência
	de saída e um coeficiente de ruído.
	Na versão actual a potências de saída depende da potência de entrada e 
	do valor anterior da potência. O valor à saída é o valor da entrada
	filtrado através de um filtro passa-baixo.
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
};

#endif
