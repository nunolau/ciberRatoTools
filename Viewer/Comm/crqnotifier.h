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

#ifndef _CIBER_RATO_CRQNOTIFIER_
#define _CIBER_RATO_CRQNOTIFIER_

/*! \class CRQNotifier
 *  \brief  This class implement one notifier for the communications socket.
 *  This notifier is monitoring the socket. When some information is received,
 *  one signal is emited and one function in the Comm is called.
 */

#include <qsocketnotifier.h>
#include "crqcomm.h"

class CRQNotifier : public QSocketNotifier
{
Q_OBJECT
public:
	/*! This is the constructor.
	 */
	CRQNotifier( CRQComm *comm );
	/*! This is the destructor.
	 */
	~CRQNotifier();
private:
	CRQComm *comm;
public slots:
	/*! When some information is received, this function calls the 
	 * the CRQComm dataControler function.
	 */
	void notification( int ); // Only calls the dataControler function of CRQComm
};


#endif
