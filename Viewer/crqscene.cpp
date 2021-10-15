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

#include "crqscene.h"

#include <vector>
#include <math.h>

#include <QtCore>
#include <QtGui>
#include <assert.h>

using std::vector;

CRQScene::CRQScene( CRLab *lb, QObject * parent  )
                : QGraphicsScene( parent )
{
#ifdef DEBUG
    cout << "CRQScene::CRQScene\n";
#endif
	sound = 'y';
    zoom = 34;			// 1 unidade no  lab ==> 34 pixeis no scene
	lab = lb;
	robotsVarStatus = 0;
	nRobots = 5;
	labStatus = 0;
	usedId = NULL;
	bgInitSprite = NULL;
	bgGameSprite = NULL;

    if(QSound::isAvailable())
    {
        collisionSound = new QSound("sounds/collision.wav");
        returningSound = new QSound("sounds/first.wav");
        finishedSound = new QSound("sounds/finished.wav");
    }
    setSceneRect(0, 0, lb->labSize().x() * zoom, lb->labSize().y() *zoom );
    setBackgroundBrush( QColor( 255, 255, 255 ) );
    skin("skins/default/default.skin");
    setBackgroundBrush( QColor( 255, 255, 255 ) );

    QGraphicsView view (this);
    view.setCacheMode(QGraphicsView::CacheBackground);

    bgInitDraw();
}


/*============================================================================*/
CRQScene::~CRQScene()
{
}

/*============================================================================*/
void CRQScene::bgInitDraw(void)
{
#ifdef DEBUG
    cout << "CRQScene::bgInitDraw\n";
#endif
    this->setSceneRect(0, 0, 28 * zoom, 14 * zoom);
    setBackgroundBrush( QColor( 255, 255, 255 ) );
    bgInitSprite = new QGraphicsPixmapItem( QPixmap(*bgInitImage), 0, this );
	bgInitSprite->setX( 0 );
	bgInitSprite->setY( 0 );
    bgInitSprite->setZValue( 20 );
    update();
}

/*============================================================================*/
void CRQScene::bgGameDraw(void)
{
#ifdef DEBUG
    cout << "CRQScene::bgGameDraw\n";
#endif
    setBackgroundBrush( QColor( 0, 0, 0 ) );
    bgGameSprite = new QGraphicsPixmapItem( QPixmap(*bgGameImage), 0, this );
	bgGameSprite->setX( 0 );
	bgGameSprite->setY( 0 );
    bgGameSprite->setZValue( 0 );
    bgGameSprite->show();
    update();
}

/*============================================================================*/
void CRQScene::drawLab( CRLab * l_b )
{
#ifdef DEBUG
    cout << "CRQScene::drawLab\n";
#endif
    for(int i = 0 ; i < 10 ; i++)
    {
        playSoundFinished[i] = 1;
        playSoundReturning[i] = 1;
    }

	if(labStatus != 0)
		this->clear();

	this->bgGameDraw();
    lab = l_b; // lab --> pointer to CRLab
    this->setSceneRect(0, 0, lab->labSize().x() * zoom, lab->labSize().y() * zoom);
    emit newSize( (int)(lab->labSize().x() * zoom),
                  (int)(lab->labSize().y() * zoom));
    //setBackgroundBrush(QColor(0, 0, 0));

	// ********* walls ************
	unsigned int pos = 0; 
	QColor color(0, 0, 0);	// Color for the walls
	// Walls
	vector< CRWall > *wl = lab->wallListRef();
	// Beacons
	vector< CRBeacon > *bl = lab->beaconListRef();
	vector< CRBeacon >::iterator beacon = bl->begin();
	// Targets
	vector< CRTarget > *tg = lab->targetListRef();
	vector< CRTarget >::iterator target = tg->begin();

	sizeInPixels = (int) (l_b->labSize().y() * zoom);
	for ( vector< CRWall >::iterator wall = wl->begin() ; wall != wl->end() ;
      ++wall )
    {
		if ( wall->wallHeight() > beacon->beaconHeight() )
            color = colorBig ;   // color depends of height
        else
			color = colorSmall ;   // color depends of height
		
        vector< CRVertice >	*points = wall->wallVectRef();//All the wall points
        QPolygon *pointArray = new QPolygon ( points->size() );
		pos = 0;	
		for ( vector< CRVertice >::iterator ponto = points->begin() ;
          ponto != points->end() ; ++ponto )
        {
            pointArray->setPoint(pos, (int)( ponto->x() * zoom ),
                                 (int)(sizeInPixels - ponto->y() * zoom) );
            pos++;
        }

        QGraphicsPolygonItem *p = new QGraphicsPolygonItem(0, this);
        p->setPolygon( *pointArray );
		p->setVisible( true );
        p->setBrush( QBrush( color ));
        p->setZValue(6);
		//if ( (wall->wallHeight()) > (beacon->beaconHeight()) )
		//	{
		//	p->setBrush( QBrush(color, QPixmap(*higherWallsFile)) );
        //	p->setZValue( 6 );
		//	}

		//else
		//	{
		//	p->setBrush( QBrush(color, QPixmap(*lowerWallsFile)) );
        //	p->setZValue( 6 );
        //	}
    }

    for ( target = tg->begin() ; target != tg->end(); ++target )
    {
        double radius = target->radius() * zoom;
        double diam = radius * 2;
        double target_x = target->Position().x() * zoom - radius;
        double target_y = sizeInPixels - target->Position().y() * zoom - radius;
        QGraphicsEllipseItem *labArrival = new QGraphicsEllipseItem(target_x, target_y,
                                                                    diam, diam, 0, this);
        labArrival->setBrush(Qt::cyan);
        labArrival->setZValue( 1 );
        labArrival->setVisible( true );

        QGraphicsEllipseItem *labArrival2 = new QGraphicsEllipseItem(target_x + 0.1 * zoom, target_y + 0.1 * zoom,
                                                                     diam - 0.2 * zoom, diam - 0.2 * zoom, 0, this);
        labArrival2->setBrush(Qt::black);
        labArrival2->setZValue( 2 );
        labArrival2->setVisible( true );
    }
    QList<QGraphicsPixmapItem *> *labLight = new QList<QGraphicsPixmapItem *>();
    for ( beacon = bl->begin() ; beacon != bl->end(); ++beacon )
    {
        QGraphicsPixmapItem *light = new QGraphicsPixmapItem (QPixmap(*beaconFile),0, this);
        light->setX( beacon->beacon().x() * zoom - light->pixmap().width()/2);
        light->setY( sizeInPixels -  beacon->beacon().y() * zoom - light->pixmap().height()/2);

        light->setZValue( 4 );
		light->setVisible( true );
        labLight->append(light);
    }

	labStatus = 1; 
    update();
}

/*=============================================================================*/

void CRQScene::drawGrid( CRLab * l_b )
{
#ifdef DEBUG
    cout << "CRQScene::drawGrid\n";
#endif
    //QColor color(0, 0, 0);
	lab = l_b;		// Lab --> pointer to CRLab
    if ( (labStatus != 0) && lab->grid() != NULL )
    {
		int nGrids = lab->grid()->howManyPositions(); //Number of grid positions
		startP.resize(nGrids);
        for ( int n = 0 ; n < nGrids ; n++ )
        {
            double grid_x = lab->grid()->getPosition(n)->position.x() * zoom - zoom/2;
            double grid_y = sizeInPixels - lab->grid()->getPosition(n)->position.y() * zoom - zoom/2;
            startP[n] = new QGraphicsEllipseItem(0, 0,
                                                 1 * zoom, 1 * zoom, 0, this);
            startP[n]->setX(grid_x);
            startP[n]->setY(grid_y);
			startP[n]->setVisible( true );
			startP[n]->setBrush( Qt::cyan );
            //startP[n]->setBrush( QBrush(color, QPixmap(*startFile[n])) );
            startP[n]->setZValue( 3 );
        }//Constroi todos os elementos da grelha de partida

    } //Valida se lab e grid existem

    update();
}

/*=============================================================================*/

int CRQScene::drawRobot( CRLab * l_b )
{
//	cout << "CRQScene::drawRobot\n";
	lab = l_b;
	CRRobot *rob;
    if (labStatus == 0)  // Valida se lab ja existe
    {
        return 0;
    }

    if (robotsVarStatus == 0)
    {
		if( lab->grid() != NULL )		// if grid exist
			nRobots = lab->grid()->howManyPositions(); 

		usedId = new int[nRobots];   // estado dos robots
		for ( int n = 0; n < nRobots; n++ )
			usedId[n] = 0;

		robots.resize( nRobots );
        robotsVarStatus = 1;
    }

	// percorre todos os robots existentes no lab
    for( int nRobs=1; nRobs<=nRobots; nRobs++ )
    {
		rob=lab->robot( nRobs );
        if( rob !=NULL && (rob->id() > 0) && (rob->id() < (nRobots + 1) ) )
        {
            float dir = rob->direction();
            if( dir < 0 )
                dir += 360;
            if( usedId[ rob->id() - 1] == 0 ) // if robot not created
            {
                QGraphicsPixmapItem *robot = new QGraphicsPixmapItem(0, this);

                if(rob->state() == CRRobot::RETURNING)
                    robot->setPixmap(*robPixmapReturn[rob->id() - 1]);
                else
                    robot->setPixmap(*robPixmap[rob->id() - 1]);

                assert(!robot->pixmap().isNull());

                double robWidth = static_cast<double>(robot->pixmap().width());
                double robHeight = static_cast<double>(robot->pixmap().height());

                robot->setTransformOriginPoint(robWidth / 2.0, robHeight / 2.0);

                robot->setX( rob->x() * zoom - robWidth / 2.0);
                robot->setY( sizeInPixels - rob->y() * zoom - robHeight / 2.0);

                robot->setVisible( true );
                robot->setZValue( 5 );
                robot->setRotation(-dir);

				robots[rob->id() - 1] = robot; //Add new robot to vector
                usedId[rob->id() - 1] = 1;	   //Update the var used
            }
            else		// if robot exist
            {
                QGraphicsPixmapItem *robot = robots[rob->id() - 1];
                // actualiza robot existente
                if (rob->state() == CRRobot::REMOVED)
                    robot->setVisible(false);

                if (rob->state() == CRRobot::RETURNING ||
                        rob->state() == CRRobot::STOPPED ||
                        rob->state() == CRRobot::FINISHED)
                    startP[rob->id() - 1]->setRect(0, 0,
                                                   1 * zoom, 1 * zoom);
                else
                    startP[rob->id() - 1]->setRect(0.25 * zoom, 0.25 * zoom,
                                                   0.5 * zoom, 0.5 * zoom);


                // no caso de colisoes:
                /* Novo campo da msg */
                if(strncmp(rob->collision(), "True", 4) == 0 &&
                        rob->state() != CRRobot::REMOVED)
                {
                    robot->setPixmap(*robPixmapCollision[rob->id() - 1]);
                    if(QSound::isAvailable() && sound == 'y')
                        collisionSound->play();
                }
                else
                {
                    if(rob->state() == CRRobot::RETURNING)
                        robot->setPixmap(*robPixmapReturn[rob->id() - 1]);
                    else
                        robot->setPixmap(*robPixmap[rob->id() - 1]);

                    robot->setRotation(-dir);
                }

                robot->setPos (rob->x() * zoom - robot->pixmap().width() / 2.0,
                               sizeInPixels - rob->y() * zoom - robot->pixmap().height() / 2.0);

                if(rob->state() == CRRobot::RETURNING &&
                        playSoundReturning[rob->id() - 1])
                {
                    if(QSound::isAvailable() && sound == 'y')
                        returningSound->play();

                    playSoundReturning[rob->id() - 1] = 0;
                }

                if(rob->state() == CRRobot::FINISHED &&
                        playSoundFinished[rob->id() - 1])
                {
                    if(QSound::isAvailable() && sound == 'y')
                        finishedSound->play();

                    playSoundFinished[rob->id() - 1] = 0;
                }
            }// Robot existe
        }// Valida rob ID
    }// Percorre todos os robots existentes no lab

    update();
    return 0;
}

/*============================================================================*/
void CRQScene::clear( void )
{
#ifdef DEBUG
    cout << "CRQScene::clear\n";
#endif

    // Delete scene elements
    QList<QGraphicsItem *> list = items();
    QList<QGraphicsItem *>::iterator it = list.begin();
    for (; it != list.end(); ++it)
    {
        if (*it)
        {
			delete *it;
            *it = NULL;
        }
    }

    if(bgGameImage != NULL)
    {
		delete bgGameImage;
        bgGameImage = NULL;
    }

    if(bgInitImage != NULL)
    {
		delete bgInitImage;
        bgInitImage = NULL;
    }

    if(usedId != NULL)
    {
		delete [] usedId;
        usedId = NULL;
    }

    if(lowerWallsFile != NULL)
    {
		delete lowerWallsFile;
        lowerWallsFile = NULL;
    }

    if(higherWallsFile != NULL)
    {
		delete higherWallsFile;
        higherWallsFile = NULL;
    }

    robPixmap.clear();
    robPixmapReturn.clear();
    robPixmapCollision.clear();
    startPixmap.clear();
	robots.clear();
	startP.clear();

	// Initialize status
	robotsVarStatus = 0;
    labStatus = 0;
}

/*============================================================================*/
void CRQScene::skin(QString skinFileName)
{
    QString skinName;
    char tmp[32];
	QFile fp(skinFileName);

    if(!fp.exists())
        cerr << "Unable to load file " << skinFileName.toStdString() << endl;
    else
    {
#ifdef DEBUG
        cout << "CRQScene::skin\n";
#endif
		fp.open(QIODevice::ReadOnly);
        fp.readLine(tmp, 32);
        skinName = QString(tmp).trimmed();
		fp.close();

        robPixmap.resize(5);
        robPixmapReturn.resize(5);
        robPixmapCollision.resize(5);
        startPixmap.resize(5);

        // robot files
        for(unsigned int r=0; r < 5; r++)
        {
            QString baseName;
            baseName = QString("skins/")+skinName+"/rob"+QString::number(r+1)+"/";
            QString robFile = baseName;
            robFile.append("rob.png");
            QString robFileReturn = baseName;
            robFileReturn.append("robr.png");
            QString robFileCollision = baseName;
            robFileCollision.append("robc.png");
            QString startFile = baseName;
            startFile.append("start.png");
            robPixmap[r] = new QPixmap(robFile);
            robPixmapReturn[r] = new QPixmap(robFileReturn);
            robPixmapCollision[r] = new QPixmap(robFileCollision);
            startPixmap[r] = new QPixmap(startFile);
        }

		//Lower walls
		lowerWallsFile = new QString("skins/");
		lowerWallsFile->append(skinName);
		lowerWallsFile->append("/lowerwall.png");

		//Higher walls
		higherWallsFile = new QString("skins/");
		higherWallsFile->append(skinName);
		higherWallsFile->append("/higherwall.png");

		//beacon
		beaconFile = new QString("skins/");
		beaconFile->append(skinName);
		beaconFile->append("/beacon.png");
		
		//Init background
		bgInitImage = new QString("skins/");
		bgInitImage->append(skinName);
        bgInitImage->append("/bg1/bg0000.png");

		//Game background
		bgGameImage = new QString("skins/");
		bgGameImage->append(skinName);
        bgGameImage->append("/bg2/bg0000.png");
    }
}
