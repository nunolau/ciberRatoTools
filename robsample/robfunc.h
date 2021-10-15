#ifndef __ROBFUNC_H__
#define __ROBFUNC_H__

#include "RobSock.h"

#define RUN         1
#define STOP        2
#define WAIT        3
#define RETURN      4
#define FINISHED    5

void DetermineAction(int beaconToFollow, float *lPow, float *rPow);

#endif
