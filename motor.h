#ifndef __MOTOR_H__
#define __MOTOR_H__
#include "common.h"

#define MOT_WAIT (100)

void motInit();
void motMoveSteps(int steps);

#endif