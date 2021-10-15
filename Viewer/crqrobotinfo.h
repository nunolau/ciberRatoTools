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

#ifndef _CIBER_RATO_CRQROBOTINFO_
#define _CIBER_RATO_CRQROBOTINFO_

/*! \class CRQRobotInfo
 *  \brief Implementation of information about one robot.
 *  This class will create one line of information that contains
 *  the state, name, icon, score and the number of colisions of 
 *  the robot.
 */

#include <QWidget>
#include "Lab/crrobot.h"

namespace Ui {
class CRQRobotInfo;
}

class CRQRobotInfo : public QWidget
{
    Q_OBJECT
public:
	/*! This is the constructor.
	 */
    explicit CRQRobotInfo( CRRobot *, QString, QWidget *parent = 0);

	/*! This is the destructor.
	 */
    ~CRQRobotInfo();

	/*! This function will update the information of the robot.
	 */
	void update( CRRobot * );

	/*! This function is used to change skin
	 */
	void skin(QString skinName);
signals:
	/*! Signal emited to change the score.
	 */
	void score( int );
	/*! Signal emited to change the actual time.
	 */
	void returnTime( int );
	/*! Signal emited to change the collisions number.
	 */
	void collisions( int );
	/*! Signal emited to change the state of the robot.
	 */
	void state( const QPixmap & );
	/*! Signal emited to change the robot time.
	 */
	void time( int );
private:
	CRRobot *robot;
	CRRobot::States previousState;
    QStringList robFiles;
    QPixmap runPix;
    QPixmap waitPix;
    QPixmap stopPix;
    QPixmap returnPix;
    QPixmap removePix;
    QPixmap finishPix;

	QString skinName;

    Ui::CRQRobotInfo *ui;
};

#endif
