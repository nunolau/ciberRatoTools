#include "robfunc.h"

/* Calculate the power of left and right motors */
void DetermineAction(int beaconToFollow, float *lPow, float *rPow)
{
    static int counter=0;

    bool   beaconReady;
    static struct beaconMeasure beacon;
    static float  left, right, center;
    static int    Ground;
    static bool   Collision;
    
    /*Access to values from Sensors - Only ReadSensors() gets new values */
    if(IsObstacleReady(LEFT))
        left=     GetObstacleSensor(LEFT);
    if(IsObstacleReady(RIGHT))
        right=    GetObstacleSensor(RIGHT);
    if(IsObstacleReady(CENTER))
        center=   GetObstacleSensor(CENTER);

    beaconReady = IsBeaconReady(beaconToFollow);
    if(beaconReady) {
       beacon =  GetBeaconSensor(beaconToFollow);
    }
    else beaconReady=0;

    if(IsGroundReady())
        Ground=    GetGroundSensor();
    if(IsBumperReady())
        Collision= GetBumperSensor();

    if(center>4.5 || right>4.5 || left>4.5 || Collision) { /* Close Obstacle - Rotate */
        if(counter % 400 < 200) {
           *lPow=0.06;
           *rPow=-0.06; }
        else {
           *lPow=-0.06;
           *rPow=0.06; }
    }
    else if(right>1.5) { /* Obstacle Near - Avoid */
        *lPow=0.0;
        *rPow=0.05;
    }
    else if(left>1.5) {
        *lPow=0.05;
        *rPow=0.0;
    }
    else { 
        if(beaconReady && beacon.beaconVisible && beacon.beaconDir>20.0) { /* turn to Beacon */
           *lPow=0.0;
           *rPow=0.1;
        }
        else if(beaconReady && beacon.beaconVisible && beacon.beaconDir<-20.0) {
           *lPow=0.1;
           *rPow=0.0;
        }
        else { /* Full Speed Ahead */
           *lPow=0.1;
           *rPow=0.1;
        }
    }

    counter++;
}
