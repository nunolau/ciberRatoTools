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
#include "cbparamdialog.h"

#include <stdio.h>

#include "cbparameters.h"

#include <QtGui>

/* 
 *  Constructs a cbParamDialog which is a child of 'parent', with the
 *  widget flags set to 'fl'
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
cbParamDialog::cbParamDialog( cbSimulator *sim, QWidget* parent, Qt::WFlags fl )
    : QDialog( parent, fl ),
      simulator(sim)
{

    setupUi(this);      // Sets up the user interface
    setModal(true);

    currentParam = simulator->getParameters();
    defaultParam = simulator->getDefaultParameters();
    setParamWidgets(currentParam);

    connect(buttonBox->button(QDialogButtonBox::RestoreDefaults),
            SIGNAL(clicked()), SLOT(restoreDefaults()));
}

/*
 *  Destroys the object and frees any allocated resources
 */
cbParamDialog::~cbParamDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

void cbParamDialog::setParamWidgets(cbParameters *param)
{
    char strNum[200];

    sprintf(strNum,"%d",param->simTime);
    lnEditSimTime->setText(strNum);
    sprintf(strNum,"%d",param->keyTime);
    lnEditKeyTime->setText(strNum);
    sprintf(strNum,"%d",param->cycleTime);
    lnEditSimStep->setText(strNum);

    //Noise
    sprintf(strNum,"%5.2f",param->obstacleNoise);
    lnEditObstacleNoise->setText(strNum);
    sprintf(strNum,"%5.2f",param->compassNoise);
    lnEditCompassNoise->setText(strNum);
    sprintf(strNum,"%5.2f",param->beaconNoise);
    lnEditBeaconNoise->setText(strNum);
    sprintf(strNum,"%5.2f",param->motorsNoise);
    lnEditMotorsNoise->setText(strNum);
    sprintf(strNum,"%5.2f",param->gpsLinNoise);
    lnEditGPSLinNoise->setText(strNum);
    sprintf(strNum,"%5.2f",param->gpsDirNoise);
    lnEditGPSDirNoise->setText(strNum);

    //Requests
    sprintf(strNum,"%3d",param->nReqPerCycle);
    lnEditReqPCycle->setText(strNum);
    cBoxReqIR->setChecked(param->obstacleRequestable);
    cBoxReqBeacon->setChecked(param->beaconRequestable);
    cBoxReqCompass->setChecked(param->compassRequestable);
    cBoxReqGround->setChecked(param->groundRequestable);
    cBoxReqCollision->setChecked(param->collisionRequestable);
    cBoxReqGPS->setChecked(param->gpsRequestable);

    //Latencies
    sprintf(strNum,"%3d",param->obstacleLatency);
    lnEditLatIR->setText(strNum);
    sprintf(strNum,"%3d",param->compassLatency);
    lnEditLatCompass->setText(strNum);
    sprintf(strNum,"%3d",param->beaconLatency);
    lnEditLatBeacon->setText(strNum);
    sprintf(strNum,"%3d",param->groundLatency);
    lnEditLatGround->setText(strNum);
    sprintf(strNum,"%3d",param->collisionLatency);
    lnEditLatCollision->setText(strNum);
    sprintf(strNum,"%3d",param->gpsLatency);
    lnEditLatGPS->setText(strNum);

    //Scores
    sprintf(strNum,"%d", param->returnTimePenalty);
    lineEdit_ReturnPenalty->setText(strNum);
    sprintf(strNum,"%d", param->arrivalTimePenalty);
    lineEdit_ArrivalPenalty->setText(strNum);
    sprintf(strNum,"%d", param->collisionWallPenalty);
    lineEdit_WallCollPenalty->setText(strNum);
    sprintf(strNum,"%d", param->collisionRobotPenalty);
    lineEdit_RobotCollPenalty->setText(strNum);
    sprintf(strNum,"%d", param->targetReward);
    lineEdit_TargetReward->setText(strNum);
    sprintf(strNum,"%d", param->homeReward);
    lineEdit_HomeReward->setText(strNum);
}

void cbParamDialog::accept(void)
{
	int    vali;
	double valf; 
	char   ch;

    if(sscanf(lnEditSimTime->text().toAscii(),"%d%c",&vali,&ch)==1)
        currentParam->simTime = vali;
    if(sscanf(lnEditKeyTime->text().toAscii(),"%d%c",&vali,&ch)==1)
        currentParam->keyTime = vali;
    if(sscanf(lnEditSimStep->text().toAscii(),"%d%c",&vali,&ch)==1)
        currentParam->cycleTime = vali;

	//Noise
    if(sscanf(lnEditObstacleNoise->text().toAscii(),"%lf%c",&valf,&ch)==1)
        currentParam->obstacleNoise = valf;
    if(sscanf(lnEditCompassNoise->text().toAscii(),"%lf%c",&valf,&ch)==1)
        currentParam->compassNoise = valf;
    if(sscanf(lnEditBeaconNoise->text().toAscii(),"%lf%c",&valf,&ch)==1)
        currentParam->beaconNoise = valf;
    if(sscanf(lnEditMotorsNoise->text().toAscii(),"%lf%c",&valf,&ch)==1)
        currentParam->motorsNoise = valf;
    if(sscanf(lnEditGPSLinNoise->text().toAscii(),"%lf%c",&valf,&ch)==1)
        currentParam->gpsLinNoise = valf;
    if(sscanf(lnEditGPSDirNoise->text().toAscii(),"%lf%c",&valf,&ch)==1)
        currentParam->gpsDirNoise = valf;

	//Requests
    if(sscanf(lnEditReqPCycle->text().toAscii(),"%d%c",&vali,&ch)==1)
        currentParam->nReqPerCycle = vali;
    currentParam->obstacleRequestable = cBoxReqIR->isChecked();
    currentParam->compassRequestable = cBoxReqCompass->isChecked();
    currentParam->beaconRequestable = cBoxReqBeacon->isChecked();
    currentParam->groundRequestable = cBoxReqGround->isChecked();
    currentParam->collisionRequestable = cBoxReqCollision->isChecked();
    currentParam->gpsRequestable = cBoxReqGPS->isChecked();

    //Latencies
    if(sscanf(lnEditLatIR->text().toAscii(),"%d%c",&vali,&ch)==1)
        currentParam->obstacleLatency = vali;
    if(sscanf(lnEditLatCompass->text().toAscii(),"%d%c",&vali,&ch)==1)
        currentParam->compassLatency = vali;
    if(sscanf(lnEditLatBeacon->text().toAscii(),"%d%c",&vali,&ch)==1)
        currentParam->beaconLatency = vali;
    if(sscanf(lnEditLatGround->text().toAscii(),"%d%c",&vali,&ch)==1)
        currentParam->groundLatency = vali;
    if(sscanf(lnEditLatCollision->text().toAscii(),"%d%c",&vali,&ch)==1)
        currentParam->collisionLatency = vali;
    if(sscanf(lnEditLatGPS->text().toAscii(),"%d%c",&vali,&ch)==1)
        currentParam->gpsLatency = vali;

    //Scores
    if(sscanf(lineEdit_ReturnPenalty->text().toAscii(), "%d%c", &vali, &ch) == 1)
        currentParam->returnTimePenalty = vali;
    if(sscanf(lineEdit_ArrivalPenalty->text().toAscii(), "%d%c", &vali, &ch) == 1)
        currentParam->arrivalTimePenalty = vali;
    if(sscanf(lineEdit_WallCollPenalty->text().toAscii(), "%d%c", &vali, &ch) == 1)
        currentParam->collisionWallPenalty = vali;
    if(sscanf(lineEdit_RobotCollPenalty->text().toAscii(), "%d%c", &vali, &ch) == 1)
        currentParam->collisionRobotPenalty = vali;
    if(sscanf(lineEdit_TargetReward->text().toAscii(), "%d%c", &vali, &ch) == 1)
        currentParam->targetReward = vali;
    if(sscanf(lineEdit_HomeReward->text().toAscii(), "%d%c", &vali, &ch) == 1)
        currentParam->homeReward = vali;

    simulator->GUI()->appendMessage("New Parameters have been set!");

    close();
}

void cbParamDialog::restoreDefaults()
{
    setParamWidgets(defaultParam);
}
