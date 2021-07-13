#include "iostm8l101k3.h"

#define MOT_STEP_ODR    PB_ODR_bit.ODR0
#define MOT_ENn_ODR     PB_ODR_bit.ODR4
#define MOT_SLEEP_ODR   PB_ODR_bit.ODR5
#define MOT_DIR_ODR     PB_ODR_bit.ODR7
#define MOT_MS2_ODR     PD_ODR_bit.ODR4 
#define MOT_MS1_ODR     PD_ODR_bit.ODR5 
#define MOT_SR_ODR      PD_ODR_bit.ODR6 
#define MOT_RESETn_ODR  PD_ODR_bit.ODR7
#define LED_ODR         PD_ODR_bit.ODR0

#define MOT_STEP_DDR    PB_DDR_bit.DDR0
#define MOT_ENn_DDR     PB_DDR_bit.DDR4
#define MOT_SLEEP_DDR   PB_DDR_bit.DDR5
#define MOT_DIR_DDR     PB_DDR_bit.DDR7
#define MOT_MS2_DDR     PD_DDR_bit.DDR4 
#define MOT_MS1_DDR     PD_DDR_bit.DDR5 
#define MOT_SR_DDR      PD_DDR_bit.DDR6 
#define MOT_RESETn_DDR  PD_DDR_bit.DDR7
#define LED_DDR         PD_DDR_bit.DDR0

#define MOT_STEP_CR1    PB_CR1_bit.C10
#define MOT_ENn_CR1     PB_CR1_bit.C14
#define MOT_SLEEP_CR1   PB_CR1_bit.C15
#define MOT_DIR_CR1     PB_CR1_bit.C17
#define MOT_MS2_CR1     PD_CR1_bit.C14 
#define MOT_MS1_CR1     PD_CR1_bit.C15 
#define MOT_SR_CR1      PD_CR1_bit.C16 
#define MOT_RESETn_CR1  PD_CR1_bit.C17
#define LED_CR1         PD_CR1_bit.C10

#define MOT_HOMEn_IDR   PB_IDR_bit.IDR6
#define LED_IDR         PD_IDR_bit.IDR0

void delay(unsigned long count) {
    while (count-- > 0);
}

#define MOT_WAIT (100)
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

int main(void)
{
  MOT_STEP_DDR = 1;
  MOT_ENn_DDR = 1;
  MOT_SLEEP_DDR = 1;
  MOT_DIR_DDR = 1;
  MOT_MS2_DDR = 1;
  MOT_MS1_DDR = 1;
  MOT_SR_DDR = 1;
  MOT_RESETn_DDR = 1;

  MOT_STEP_CR1 = 1;
  MOT_ENn_CR1 = 1;
  MOT_SLEEP_CR1 = 1;
  MOT_DIR_CR1 = 1;
  MOT_MS2_CR1 = 1;
  MOT_MS1_CR1 = 1;
  MOT_SR_CR1 = 1;
  MOT_RESETn_CR1 = 1;

  MOT_STEP_ODR = 0;
  MOT_ENn_ODR = 0;
  MOT_SLEEP_ODR = 1;
  MOT_DIR_ODR = 1;
  MOT_MS2_ODR = 0;
  MOT_MS1_ODR = 1;
  MOT_SR_ODR = 0;
  MOT_RESETn_ODR = 1;
  
  LED_DDR = 0;
  LED_CR1 = 1;
  
  MOT_STEP_ODR = 0;
  int sw_prev = LED_IDR;
  while(1) {
    delay(100);
    if(sw_prev && !LED_IDR) {
      motMoveSteps(4*5);
    }
    sw_prev = LED_IDR;    
  }
}