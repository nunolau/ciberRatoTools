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
#ifndef _CB_SIMULATOR_
#define _CB_SIMULATOR_
/*!
	\class cbSimulator
	\brief The main object of the CiberRato simulator.

*/


#include "ui_logplayerGUI.h"
#include "cbrobot.h"

#include <qobject.h>
#include <qvector.h>
#include <iostream>
#include <vector>

using std::vector;
using std::istream;

class cbPosition;
class cbParameters;

class cbLab;
class cbGrid;

class cbView;
class cbPanel;
class cbReceptionist;

class cbLogplayer : public QObject
{
Q_OBJECT
public:
	cbLogplayer();
	~cbLogplayer();

	enum State {STOPPED=0, RUNNING};

	void setLab(cbLab *);
    void setGrid(cbGrid *);
    void setLog(vector< vector <cbRobot> > *l) { log=l;}
	void setParameters(cbParameters *);
    void setReceptionist(cbReceptionist *);
    void setGUI(Ui_logplayerGUI *g) { gui=g;}


    void WriteLog(void);

    inline cbLab *Lab() { return lab;}
    inline Ui_logplayerGUI *GUI(){ return gui;}

	unsigned int curTime();
	unsigned int simTime();
	unsigned int cycleTime();


    const char *curStateAsString();
    inline State state() { return (curState);}
    inline State getNextState() { return (nextState);}

public slots:
	void step();

private: // data members
	unsigned int curCycle;		// current simulation cycle
	unsigned int endCycle;		// last simulation cycle
	unsigned int cycle;			// length in miliseconds of a cycle
	
	vector <vector <cbRobot> > *log;
	cbLab *lab;					// the lab
	cbGrid *grid;				// the grid
	cbParameters *param;		// global simulation parameters
	
	cbReceptionist *receptionist; // the receptionist

	vector<cbView *> views;
	vector<cbPanel *> panels;

	State curState, nextState;	// current and next states

    istream *logStream;

	unsigned int logIndex;

    Ui_logplayerGUI *gui;
	
private: // member functions
	void CheckIn();
	void ViewCommands();
	void PanelCommands();
	void UpdateViews();
	void UpdateState();
};

#endif
