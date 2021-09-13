#ifndef __MOTOR_H__
#define __MOTOR_H__
#include "common.h"

#define MOT_WAIT (100)
#define MOTOR_ANGLE_PRECISION (7)
#define MOTOR_ANGLE_MAX (360 << MOTOR_ANGLE_PRECISION)
typedef struct {
  uint8_t is_enabled;
  uint16_t current_angle;
  uint16_t target_angle;
  int8_t speed;
} MotorSettings;

void motInit();
void motMoveSteps(int steps);

#endif