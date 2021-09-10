#ifndef __UART_H__
#define __UART_H__
#include "common.h"

#define UART_RX_BUFFER_LENGTH (6)
#define UART_TX_BUFFER_LENGTH (9)

extern uint8_t uartRxBuffer[UART_RX_BUFFER_LENGTH];
extern uint8_t uartRxBufferCount;
extern uint8_t uartRxNewDataFlag;
extern uint8_t uartTxBuffer[UART_TX_BUFFER_LENGTH];
extern uint8_t uartTxBufferCount;
extern uint8_t uartTxCompletedFlag;

void uartInit();
void uartRxOn();
void uartTxOn();

#endif