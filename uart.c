#include "uart.h"
#include "gpio.h"

int uartRxBuffer[6];
int uartRxBufferCount;
int uartRxNewDataFlag;
int uartTxBuffer[9];
int uartTxBufferCount;
int uartTxCompletedFlag;

void uartInit() {
  CLK_PCKENR |= PCKEN5;
  // Baud_rate = 38400, USART_DIV = 417 = 0x1A1
  USART_BRR1 = 0x1A;
  USART_BRR2 = 0x1;
  USART_CR2_bit.REN = 1;
  USART_CR2_bit.TEN = 1;
  USART_CR2_bit.RIEN = 1;
  uartRxOn();
}

void uartRxOn() {
  USART_RX_EN_ODR = 0;
  USART_TX_EN_ODR = 0;
}
void uartTxOn() {
  USART_RX_EN_ODR = 1;
  USART_TX_EN_ODR = 1;
}