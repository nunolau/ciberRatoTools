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
/*
 * class cbLogplayer
 */

#include <stdlib.h>

#include <iostream>
#include <fstream>

#include <qvector.h>
#include <QGraphicsScene>
#include <qapplication.h>
#include <QTextEdit>

#include "cbposition.h"
#include "cbparameters.h"

#include "cblab.h"

#include "cbreceptionist.h"
#include "cbview.h"
#include "cbgrid.h"

#include "cblogplayer.h"


using std::cerr;
using std::cout;

cbLogplayer::cbLogplayer()
{
	lab = 0;
	log = 0;
	curCycle = 0;
	endCycle = 3000; // provisório
	cycle = 75;

	curState = nextState = STOPPED;

	logIndex=0;
}

cbLogplayer::~cbLogplayer()
{
}

void cbLogplayer::setLab(cbLab *l)
{
	lab = l;
}

void cbLogplayer::setGrid(cbGrid *g)
{
	/* set the new grid */
	grid = g;
	/* resize robot array to new grid size */
}

void cbLogplayer::setParameters(cbParameters *p)
{
	param = p;
	cycle = p->cycleTime;
	endCycle = p->simTime;
}

void cbLogplayer::setReceptionist(cbReceptionist *r)
{
	receptionist = r;
}

unsigned int cbLogplayer::curTime()
{
	return curCycle;
}

unsigned int cbLogplayer::simTime()
{
	return endCycle;
}

unsigned int cbLogplayer::cycleTime()
{
	return cycle;
}

const char *cbLogplayer::curStateAsString()
{
	static const char *sas[] = { "Stopped", "Running" };
	return sas[curState];
}

void cbLogplayer::step()
{
	CheckIn();
	ViewCommands();
	UpdateViews();
	if(curState==RUNNING) {
		logIndex++;
	}
	UpdateState();

	if(logIndex==log->size()) exit(0);
}

/*
 * Private auxiliary member functions
 */

/*!
	Process registration requests of all
	clients waiting at reception.
*/
void cbLogplayer::CheckIn()
{
	while (receptionist->CheckIn())
	{
		cbClientForm &form = receptionist->Form();
		int cnt;
		switch (form.type)
		{
			case cbClientForm::VIEW:
				//cout << "View form is going to be processed\n";
				cnt = views.size();
				views.resize(cnt+1);
				views[cnt] = form.client.view;
				views[cnt]->Reply(form.addr, form.port, param);
				cout << "viewer has been registered\n";
				//gui->messages->insertLine("viewer has been registered");
				break;
			case cbClientForm::UNKNOWN:
				cerr << "UNKNOWN form was received, and discarded\n";
				//gui->messages->insertLine("UNKNOWN form was received, and discarded");
				// a refused replied must be sent
				break;
			case cbClientForm::NOBODY:
				cerr << "NOBODY form was received, and discarded\n";
				//gui->messages->insertLine("NOBODY form was received, and discarded");
				break;
			default:   //PANEL and ROBOT
				break;
		}
	}
}

/*!
	Execute every pending view command.
*/
void cbLogplayer::ViewCommands()
{
	cbCommand command;
	char xml[16*4096];
	unsigned int cnt;
	for (unsigned int i=0; i<views.size(); i++)
	{
		while (views[i]->readCommand(&command))
		{
			switch (command.type)
			{
				case cbCommand::START:
					//cout << "View command = Start\n";
					nextState = RUNNING;
					break;
				case cbCommand::STOP:
					//cout << "View command = Stop\n";
					nextState = STOPPED;
					break;
				case cbCommand::LABRQ:
					//cout << "View command = LabReq\n";
					cnt = lab->toXml(xml, sizeof(xml));
					views[i]->send(xml, cnt+1);
					break;
				case cbCommand::GRIDRQ:
					//cout << "View command = GridReq\n";
					cnt = grid->toXml(xml, sizeof(xml));
					views[i]->send(xml, cnt+1);
					break;
				case cbCommand::ROBOTDEL:
					//cout << "View command = RobotDel\n";
					break;
				case cbCommand::UNKNOWN:
					//cout << "View command = Unknown\n";
					break;
			}
		}
	}
}
	

/*!
	Send status of every robot to every view.
*/
void cbLogplayer::UpdateViews()
{
	char xml[1024];
	vector <cbRobot> &robots = (*log)[logIndex];
	for (unsigned int i=0; i<robots.size(); i++)
	{
		cbRobot &robot = robots[i];
		unsigned int n = robot.toXml(xml, sizeof(xml));
		for (unsigned int j=0; j<views.size(); j++)
		{
			cbView *view = views[j];
			view->send(xml, n+1);
		}
	}
}

void cbLogplayer::WriteLog()
{
	for (unsigned int i=0; i<(*log).size(); i++) {
		fprintf(stderr,"t %d\n",i);
		for (unsigned int j=0; j<(*log)[i].size(); j++)
		{
			fprintf(stderr,"id=%d (%f,%f)\n",
					(*log)[i][j].Id(),
					(*log)[i][j].X(),(*log)[i][j].Y());
		}
	}

}


/*!
	Update state of simulator and update active state of every robot.
	If next state is equal to current one do nothing.
*/
void cbLogplayer::UpdateState()
{
	if (nextState != curState)
		curState = nextState;

}

