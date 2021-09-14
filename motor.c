#include "motor.h"
#include "gpio.h"

volatile MotorSettings motor = {0};

void motInit() {  
  MOT_ENn_ODR = 1;
  MOT_STEP_ODR = 0;
  MOT_SLEEP_ODR = 1;
  MOT_DIR_ODR = 1;
  MOT_MS2_ODR = 1;
  MOT_MS1_ODR = 0;
  MOT_SR_ODR = 0;
  MOT_RESETn_ODR = 1;
}

void motTimerHalt() {
  TIM2_CCMR1_COMPARE_OC1M = TIMx_CCMRx_OCxM_FORCE_INACTIVE;
  TIM2_CR1_bit.CEN = 0;
  TIM2_CNTRH = 0;
  TIM2_CNTRL = 0;
}

void motTimerInit() {
  CLK_PCKENR |= PCKEN0;
  TIM2_PSCR = 0x7; // PRESCALER=128, F_CLK=125kHz
  TIM2_ARRH = 0x20;
  TIM2_ARRL = 0x00;
  TIM2_CCR1H = 0x0;
  TIM2_CCR1L = 0x1;
  TIM2_IER_bit.CC1IE = 1;  
  TIM2_CCMR1_COMPARE_OC1M = TIMx_CCMRx_OCxM_FORCE_INACTIVE;
  TIM2_CCER1_bit.CC1P = 0;
  TIM2_CCMR1_COMPARE_bit.OC1PE = 0;
  TIM2_CCER1_bit.CC1E = 1;
  TIM2_CR1_bit.CEN = 1;
  TIM2_BKR_bit.MOE = 1;
  motTimerHalt();
}

void motUpdate(volatile MotorSettings *motor) {
  MOT_ENn_ODR = !motor->is_enabled;
  MOT_DIR_ODR = motor->speed > 0;
  if(motor->speed > 0) {
    TIM2_ARRH = (uint8_t) motor->speed;
  } else {
    TIM2_ARRH = (uint8_t) (-motor->speed);
  }
  TIM2_ARRL = 0;
  if(motor->is_enabled && motor->speed != 0 && motor->current_angle != motor->target_angle) {
    motor->is_rotating = 1;
    if(!TIM2_CR1_bit.CEN) {
      TIM2_CR1_bit.CEN = 1;
      TIM2_CCMR1_COMPARE_OC1M = TIMx_CCMRx_OCxM_TOGGLE;
      TIM2_EGR_bit.CC1G;
    }
  } else {
    motTimerHalt();
    motor->is_rotating = 0;
  }
}

#pragma vector = TIM2_CAPCOM_CC1IF_vector
__interrupt void motTimerCC(void) {
  TIM2_SR1_bit.CC1IF = 0;  
  if(MOT_STEP_IDR) {
    uint32_t angle = motor.current_angle + MOTOR_ANGLE_MAX;
    if(motor.speed > 0) {
      angle += MOTOR_ANGLE_STEP;
    } else {
      angle -= MOTOR_ANGLE_STEP;
    }
    angle %= MOTOR_ANGLE_MAX;
    motor.current_angle = (uint16_t) angle;
    if(motor.current_angle == motor.target_angle) {
      motTimerHalt();
      motor.is_rotating = 0;
    }
  }
}