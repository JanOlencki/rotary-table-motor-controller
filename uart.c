#include "uart.h"
#include "gpio.h"
#include "communication.h"

#define CLEAR_USART_TC_FLAG() asm("BRES 0x5230, #6")
//#define CLEAR_USART_TC_FLAG() (1) 
uint8_t uartRxBuffer[UART_RX_BUFFER_LENGTH];
volatile uint8_t uartRxBufferCount;
volatile uint8_t uartRxNewDataFlag;
uint8_t uartTxBuffer[UART_TX_BUFFER_LENGTH];
volatile uint8_t uartTxBufferCount;
volatile uint8_t uartTxCompletedFlag;

void uartInit() {
  CLK_PCKENR |= PCKEN5;
  // Baud_rate = 38400, USART_DIV = 417 = 0x1A1
  USART_BRR1 = 0x1A;
  USART_BRR2 = 0x1;
  USART_CR2_bit.REN = 1;
  USART_CR2_bit.TEN = 1;
  USART_CR2_bit.RIEN = 1;
  USART_CR2_bit.TCIEN = 0;
  uartRxBufferCount = 0;
  uartRxNewDataFlag = 0;
  uartTxBufferCount = 0;
  uartTxCompletedFlag = 0;
}
void uartTimerInit() {
  CLK_PCKENR |= PCKEN1;
  TIM3_PSCR = 0x2; // PRESCALER=4, F_CLK=4MHz
  TIM3_ARRH = 0x20;
  TIM3_ARRL = 0x00;
  TIM3_CR1_bit.URS = 1;
  TIM3_IER_bit.UIE = 1;
  TIM3_CR1_bit.CEN = 1;
}
void uartSend(uint8_t data[], uint8_t data_length) {
  USART_CR2_bit.TCIEN = 0;
  memcpy(&uartTxBuffer, data, data_length);
  uartTxCompletedFlag = 0;
  uartTxBufferCount = data_length;
  USART_DR = uartTxBuffer[UART_TX_BUFFER_LENGTH - uartTxBufferCount];  
  CLEAR_USART_TC_FLAG();
  USART_CR2_bit.TCIEN = 1;
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
  uint8_t bufferIndex = uartRxBufferCount % UART_RX_BUFFER_LENGTH;
  uartRxBuffer[bufferIndex] = USART_DR;
  uartRxNewDataFlag = 1;
  uartRxBufferCount = (uartRxBufferCount + 1) % (UART_RX_BUFFER_LENGTH + 1);
  if(uartRxBufferCount == 1) {
    LED_ODR = 0;
  }
  TIM3_EGR_bit.UG = 1;
}

#pragma vector = USART_T_TC_vector
__interrupt void uartTCHandler(void) {
  CLEAR_USART_TC_FLAG();
  if(uartTxBufferCount == 0) {    
    uartTxCompletedFlag = 1;
  } else {
    uartTxBufferCount--;
    USART_DR = uartTxBuffer[UART_TX_BUFFER_LENGTH - uartTxBufferCount];
  }
}

#pragma vector = TIM3_OVR_UIF_vector
__interrupt void uartTimer3OvrHandler(void) {
  TIM3_SR1_bit.UIF = 0;
  if(!uartRxNewDataFlag && uartRxBufferCount > 0) {
    uartRxBufferCount = 0;
    LED_ODR = 1;
  }
}