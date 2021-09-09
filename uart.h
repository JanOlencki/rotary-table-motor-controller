#ifndef __UART_H__
#define __UART_H__

#include "iostm8l101k3.h"

extern int uartRxBuffer[6];
extern int uartRxBufferCount;
extern int uartRxNewDataFlag;
extern int uartTxBuffer[9];
extern int uartTxBufferCount;
extern int uartTxCompletedFlag;

void uartInit();
void uartRxOn();
void uartTxOn();

#endif