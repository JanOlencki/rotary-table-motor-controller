#include "uart.h"
#include "gpio.h"

uint8_t uartRxBuffer[UART_RX_BUFFER_LENGTH];
uint8_t uartRxBufferCount;
uint8_t uartRxNewDataFlag;
uint8_t uartTxBuffer[UART_TX_BUFFER_LENGTH];
uint8_t uartTxBufferCount;
uint8_t uartTxCompletedFlag;

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

#pragma vector = USART_R_RXNE_vector
__interrupt void uartRXEHandler(void) {
  uartRxBuffer[uartRxBufferCount] = USART_DR;
  LED_ODR = 0;
  uartRxNewDataFlag = 1;
  uartRxBufferCount = (uartRxBufferCount + 1) % UART_RX_BUFFER_LENGTH;
}