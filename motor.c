#include "motor.h"
#include "gpio.h"

void motInit() {
  MOT_STEP_ODR = 0;
  MOT_ENn_ODR = 1;
  MOT_SLEEP_ODR = 1;
  MOT_DIR_ODR = 1;
  MOT_MS2_ODR = 0;
  MOT_MS1_ODR = 1;
  MOT_SR_ODR = 0;
  MOT_RESETn_ODR = 1;
}

void motMoveSteps(int steps) {
  MOT_STEP_ODR = 0;
  for(; steps > 0; steps--) {
    delay(MOT_WAIT);
    MOT_STEP_ODR = 1;
    delay(MOT_WAIT);
    MOT_STEP_ODR = 0;
  }
  delay(MOT_WAIT);
}