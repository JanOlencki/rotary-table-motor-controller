#include "common.h"
#include "gpio.h"
#include "motor.h"
#include "uart.h"


int main(void)
{
  gpioInit();
  motInit();
  uartInit();
  __enable_interrupt();
  
  LED_ODR = 1;
  while(1) {
    delay(500000);
    if(uartRxNewDataFlag && uartRxBufferCount == 0) {
      delay(100);
    }
    //motMoveSteps(4*5);
  }
}