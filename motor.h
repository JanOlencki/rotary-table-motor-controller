#ifndef __MOTOR_H__
#define __MOTOR_H__
#include "common.h"

#define MOT_WAIT (100)
#define MOTOR_ANGLE_FRACTION_LENGTH (7)
#define MOTOR_ANGLE_STEP (1 << 4)
#define MOTOR_ANGLE_STEP_PREC_MASK (0xFFF0)
#define MOTOR_ANGLE_MAX (360u << MOTOR_ANGLE_FRACTION_LENGTH)
#define MOTOR_SPEED_TO_TIMER (10417u)
typedef struct {
  uint8_t is_enabled;
  uint8_t is_rotating;
  uint16_t current_angle;
  uint16_t target_angle;
  int8_t speed;
} MotorSettings;

extern volatile MotorSettings motor;

void motInit();
void motTimerInit();
void motUpdate(volatile MotorSettings *motor);

#endif