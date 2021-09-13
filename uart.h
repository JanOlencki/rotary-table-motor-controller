#ifndef __UART_H__
#define __UART_H__
#include "common.h"

#define UART_RX_BUFFER_LENGTH (6)
#define UART_TX_BUFFER_LENGTH (9)

extern uint8_t uartRxBuffer[UART_RX_BUFFER_LENGTH];
volatile extern uint8_t uartRxBufferCount;
volatile extern uint8_t uartRxNewDataFlag;
extern uint8_t uartTxBuffer[UART_TX_BUFFER_LENGTH];
volatile extern uint8_t uartTxBufferCount;
volatile extern uint8_t uartTxCompletedFlag;

void uartInit();
void uartSend(uint8_t data[], uint8_t data_length);
void uartRxOn();
void uartTxOn();

#endif