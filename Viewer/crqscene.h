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

#ifndef _CIBER_RATO_CRQSCENE_
#define _CIBER_RATO_CRQSCENE_

/*! \class CRQScene
 *  \brief Class that implement one 2D graphic area where everything will be
 *  draw.
 *
 *  This class will be the support for all visible items like walls, robots, etc.
 */

#include <QGraphicsScene>
#include <QSound>
#include "./Lab/crlab.h"
#include "./Lab/crrobot.h"

class CRQScene : public QGraphicsScene
{
    Q_OBJECT
public:
	/*! This is the constructor.
	 */
    CRQScene( CRLab *, QObject * parent = 0 );
	/*! This is the destructor.
	 */
	~CRQScene();
	/*! Draws the received lab, with walls, one beacon end one target area.
     *  Each of them will be one scene item.
	 */ 
	void drawLab( CRLab * );

	/*! Function called when the skin changed.
	 *	\var skinFileName The skin name.
	 */
	void skin(QString skinFileName);

	/*! Draws the received grid. At this moment it is only a lot of squares.
	 */
	void drawGrid( CRLab * );
	/*! Draws all robots considering the images that we have in the 
	 *  images/robotN directory, where N is the id of the robot. If the robot
	 *  does not exist, it will be created, otherwise the existent item will
	 *  be moved and/or rotated.
	 */
	int drawRobot( CRLab * );
    /*! Clear the scene, all elements will be lost.
	 */
	void clear( void );
    /*! Draw the initial image in scene when aplication begins. This
	 * function also is called when a reset or connect is done.
	 */
	void bgInitDraw(void);
    /*! Draw the game image in scene when lab is ready . This
	 * function also is called when a connect is done.
	 */
	void bgGameDraw(void);
	/*! \var nRobots
	 *  Global variable that contain the number of robots. By default there
	 *  will be 3, but the grid may change this value.
	 */
	int nRobots; 					 
	/*! \var colorSmall
	 * 	Global variable that contains the color of the walls whose height 
	 * 	is lower than the beacon height.
	 */
	QColor colorSmall;
	/*! \var colorBig
	 * 	Global variable that contains the color of the walls whose height
	 * 	is higher than the beacon height.
	 */
	QColor colorBig;
	/*! \var backImage
	 * Global variable used to activate the use of sounds
	 */ 
	char sound;
	/*! \var lab
	 * Global pointer that contain the lab received.
	 */
   	CRLab *lab;

signals:
    /*! This signal is emited when new lab is draw in scene.
	 * \param x x dimension in pixeis
	 * \param y y dimension in pixeis
	 */
	void newSize(int x, int y);

private:
	// Vector of robots
    vector<QGraphicsPixmapItem *> robots;

    // Robot images
    vector<QPixmap *> robPixmap;
    vector<QPixmap *> robPixmapReturn;
    vector<QPixmap *> robPixmapCollision;
    vector<QPixmap *> startPixmap;

    // Vector of starting points
    vector<QGraphicsEllipseItem *> startP;

	// Means that robots already exists
	int *usedId;

	// Status of the robots construction		
	int robotsVarStatus;
	
    // Zoom for the Scene
	double zoom;
	
	// Tell if lab is available
	int labStatus;

    // Size of the Scene in pixels
    int sizeInPixels;

	// Game Background
    QGraphicsPixmapItem *bgGameSprite;
    QString *bgGameImage;

	// Initial Background 
    QGraphicsPixmapItem *bgInitSprite;
    QString *bgInitImage;

    QString *lowerWallsFile;
    QString *higherWallsFile;	
	QString *beaconFile;

	// Game sounds
	QSound *collisionSound;
    QSound *returningSound;
    QSound *finishedSound;
    int playSoundReturning[10];
    int playSoundFinished[10];
};


#endif
