#include "iostm8l101k3.h"
#include "gpio.h"
#include "motor.h"
#include "uart.h"

int main(void)
{
  gpioInit();
  motInit();
  uartInit();
  enableInterrupts();
  
  LED_ODR = 0;
  while(1) {
    //motMoveSteps(4*5);
    LED_ODR = ~LED_ODR;
  }
}