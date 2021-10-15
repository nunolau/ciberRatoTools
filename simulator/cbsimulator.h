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

#include "cbsimulatorGUI.h"

#include <QObject>
#include <QVector>
#include <QTimer>
#include <iostream>
#include <vector>

using std::vector;
using std::ostream;

class cbPoint;
class cbPosition;
class cbParameters;

class cbLab;
class cbGrid;

class cbRobot;
class cbView;
class cbPanel;
class cbReceptionist;

class cbGraph;

class QGraphicsView;
class QGraphicsScene;

/**
 * Simulation kernel of the application.
 */
class cbSimulator : public QObject
{
Q_OBJECT
public:
	cbSimulator();
	~cbSimulator();

	enum State {INIT, STOPPED, RUNNING, FINISHED};

	void setLab(cbLab *);
	void setGrid(cbGrid *);
	void setParameters(cbParameters *);
	void setScoring(int sc);
	int  getScoring(void);
	void setReceptionist(cbReceptionist *);
    void setGUI(cbSimulatorGUI *g) { gui=g;}
    void setLogFilename(QString lfn) { logFilename=lfn; logging=true; }

	void setReceptionistAt(int port);

	bool getGPS(void);
	bool getBeaconSensor(void);
	bool getScoreSensor(void);
    bool isTimed(void);
    bool collisionsIgnored(void);
    bool isRegistrationAllowed(void);

    cbParameters * getParameters(void) {return param;}
    inline cbParameters * getDefaultParameters() {return defaultParam;}
    inline cbLab * getDefaultLab () {return defaultLab;}
    inline cbGrid * getDefaultGrid () {return defaultGrid;}

    int openLog(const char *logFilename); // returns -1 in case of error
    int closeLog(void);

    inline cbLab *Lab() { return lab;}
    inline cbGrid *Grid() { return grid; }
    inline vector<cbRobot*> &Robots() { return robots; }
	inline cbSimulatorGUI *GUI(){ return gui;}

    bool registerRobot(cbRobot *);

	unsigned int curTime();
	unsigned int simTime();
    unsigned int cycleTime();
    unsigned int keyTime();

    const char *curStateAsString();
    inline State state() const { return (curState);}
    inline State getNextState() const { return (nextState);}

	void buildGraph(void);
	void showGraph(int id);

    double calcDistMaxFromGridTo(cbPoint &p);
    void   setDistMaxFromGridToTarget(void);
    double getDistMaxToTarget(void) { return distMaxToTarget; }

	cbGraph *grAux;

    bool changeLab(QString labFilename);
    bool changeGrid(QString gridFilename);
    bool changeParameters(QString paramFilename);

    void saveConfiguration(QString paramFilename);
    void processEditParameters(void);

    bool allRobotsVisitedOrVisitingTarget(int targId);
    bool allRobotsOnTarget(int targId);

//protected:
	void setDefaultLab(void);
	void setDefaultGrid(void);
	void setDefaultParameters(void);

public:
	//DEBUG
#define GRIDSIZE 84

    QGraphicsScene *labScene;
    QGraphicsView *labView;
	double distGrid[GRIDSIZE][GRIDSIZE];
	unsigned int labCanvasWidth,labCanvasHeight;

	void startTimer(void);

public slots:
	void step();
	void reset();
	void start();
	void stop();

    void setScoreSensor(bool g);
    void setGPS(bool g);
    void setBeaconSensor(bool g);
    void setTime(bool);
    void setCollisions(bool);
    void setRegistrations(bool);
    void deleteRobot(uint id);

    void setShowActions(bool);
    void setShowMeasures(bool);
    void setShowPositions(bool);

    void printTargetRelativePositions();

signals:
    void toggleGPS(bool);
    void toggleBeaconSensor(bool);
    void toggleScoreSensor(bool);

    void toggleTime(bool);
    void toggleCollisions(bool);
    void toggleRegistrations(bool);

    void labChanged(const QString newLab);
    void gridChanged(int);
    void stateChanged(const QString newState);

    void simReset(bool);
    void simReady(bool);
    void simRunning(bool);

    void curTimeChanged(int);
    void simTimeChanged(int);

    void robotRegistered(int);
    void robotDeleted(int);


protected: // data members
	unsigned int curCycle;		// current simulation cycle
	unsigned int endCycle;		// last simulation cycle
	unsigned int cycle;			// length in miliseconds of a cycle
	
	cbLab *lab;					// the lab
	cbGrid *grid;				// the grid
	cbParameters *param;		// global simulation parameters

    cbLab *defaultLab;          // default lab
    cbGrid *defaultGrid;        // default grid
    cbParameters *defaultParam; // default simulation parameters

	cbReceptionist *receptionist; // the receptionist

	cbSimulatorGUI *gui;

    vector<cbView *> views;
    vector<cbPanel *> panels;
    vector<cbRobot *> robots;

	State curState, nextState;	// current and next states

    bool logging;
    ostream *logStream;
	QString logFilename;
	
	cbGraph *graph;
	double distMaxToTarget;

    QTimer timer;

    bool allowRegistrations;
    bool showPositions;

    int scoring;

protected: // member functions
	void CheckIn();
	void ViewCommands();
	void PanelCommands();
	void RobotActions();
	void Log(ostream &, bool withactions=true);
	void NextPositions();
	void CheckCollisions();
	void Commit();
	void UpdateViews();
	void UpdateScores();
	void UpdateSensors();
	void SendSensors();
	void UpdateState();
};

#endif
