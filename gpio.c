#include "gpio.h"

void gpioInit() {
  CLK_CKDIVR = 0;
  
  LED_DDR = 1;
  LED_ODR = 1;
  LED_CR1 = 1;
  
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
  
  USART_RX_DDR = 0;
  USART_RX_EN_DDR = 1;
  USART_TX_DDR = 1;
  USART_TX_EN_DDR = 1;
  USART_RX_CR1 = 1;
  USART_RX_EN_CR1 = 1;
  USART_TX_CR1 = 1;
  USART_TX_EN_CR1 = 1;
  
  CFG_ID0_DDR = 0;
  CFG_ID0_CR1 = 1;
  CFG_ID1_DDR = 0;
  CFG_ID1_CR1 = 1;
}
void delay(unsigned long count) {
    while (count-- > 0);
}