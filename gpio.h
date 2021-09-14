#ifndef __GPIO_H__
#define __GPIO_H__
#include "common.h"

#include "iostm8l101k3.h"

#define CLK_F 16000000
#define PCKEN7          (1<<7)
#define PCKEN6          (1<<6)
#define PCKEN5          (1<<5)
#define PCKEN4          (1<<4)
#define PCKEN3          (1<<3)
#define PCKEN2          (1<<2)
#define PCKEN1          (1<<1)
#define PCKEN0          (1<<0)
#define TIMx_CCMRx_OCxM_FROZEN          (0x0)
#define TIMx_CCMRx_OCxM_SET_ACTIVE      (0x1)
#define TIMx_CCMRx_OCxM_SET_INACTIVE    (0x2)
#define TIMx_CCMRx_OCxM_TOGGLE          (0x3)
#define TIMx_CCMRx_OCxM_FORCE_INACTIVE  (0x4)
#define TIMx_CCMRx_OCxM_FORCE_ACTIVE    (0x5)
#define TIMx_CCMRx_OCxM_FORCE_PWM1      (0x6)
#define TIMx_CCMRx_OCxM_FORCE_PWM2      (0x7)

#define MOT_STEP_ODR    PB_ODR_bit.ODR0
#define MOT_ENn_ODR     PB_ODR_bit.ODR4
#define MOT_SLEEP_ODR   PB_ODR_bit.ODR5
#define MOT_DIR_ODR     PB_ODR_bit.ODR7
#define MOT_MS2_ODR     PD_ODR_bit.ODR4 
#define MOT_MS1_ODR     PD_ODR_bit.ODR5 
#define MOT_SR_ODR      PD_ODR_bit.ODR6 
#define MOT_RESETn_ODR  PD_ODR_bit.ODR7
#define LED_ODR         PD_ODR_bit.ODR0
#define USART_RX_ODR    PC_ODR_bit.ODR2    
#define USART_RX_EN_ODR PC_ODR_bit.ODR5
#define USART_TX_ODR    PC_ODR_bit.ODR3
#define USART_TX_EN_ODR PC_ODR_bit.ODR4
#define CFG_ID0_ODR     PC_ODR_bit.ODR0
#define CFG_ID1_ODR     PC_ODR_bit.ODR1

#define MOT_STEP_DDR    PB_DDR_bit.DDR0
#define MOT_ENn_DDR     PB_DDR_bit.DDR4
#define MOT_SLEEP_DDR   PB_DDR_bit.DDR5
#define MOT_DIR_DDR     PB_DDR_bit.DDR7
#define MOT_MS2_DDR     PD_DDR_bit.DDR4 
#define MOT_MS1_DDR     PD_DDR_bit.DDR5 
#define MOT_SR_DDR      PD_DDR_bit.DDR6 
#define MOT_RESETn_DDR  PD_DDR_bit.DDR7
#define LED_DDR         PD_DDR_bit.DDR0
#define USART_RX_DDR    PC_DDR_bit.DDR2
#define USART_RX_EN_DDR PC_DDR_bit.DDR5
#define USART_TX_DDR    PC_DDR_bit.DDR3
#define USART_TX_EN_DDR PC_DDR_bit.DDR4
#define CFG_ID0_DDR     PC_DDR_bit.DDR0
#define CFG_ID1_DDR     PC_DDR_bit.DDR1

#define MOT_STEP_CR1    PB_CR1_bit.C10
#define MOT_ENn_CR1     PB_CR1_bit.C14
#define MOT_SLEEP_CR1   PB_CR1_bit.C15
#define MOT_DIR_CR1     PB_CR1_bit.C17
#define MOT_MS2_CR1     PD_CR1_bit.C14 
#define MOT_MS1_CR1     PD_CR1_bit.C15 
#define MOT_SR_CR1      PD_CR1_bit.C16 
#define MOT_RESETn_CR1  PD_CR1_bit.C17
#define LED_CR1         PD_CR1_bit.C10
#define USART_RX_CR1    PC_CR1_bit.C12
#define USART_RX_EN_CR1 PC_CR1_bit.C15
#define USART_TX_CR1    PC_CR1_bit.C13
#define USART_TX_EN_CR1 PC_CR1_bit.C14
#define CFG_ID0_CR1     PC_CR1_bit.C10
#define CFG_ID1_CR1     PC_CR1_bit.C11

#define MOT_STEP_IDR    PB_IDR_bit.IDR0
#define MOT_HOMEn_IDR   PB_IDR_bit.IDR6
#define LED_IDR         PD_IDR_bit.IDR0
#define USART_RX_IDR    PC_IDR_bit.IDR2
#define CFG_ID0_IDR     PC_IDR_bit.IDR0
#define CFG_ID1_IDR     PC_IDR_bit.IDR1

void gpioInit();
void delay(unsigned long count);

#endif