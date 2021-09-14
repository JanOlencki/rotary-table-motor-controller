#include "common.h"
#include "gpio.h"
#include "motor.h"
#include "uart.h"
#include "communication.h"

uint8_t readCfgAddress();
Status status = 0;
uint8_t cfg_address = 0;
RequestFrame lastReq;

int main(void)
{
  gpioInit();
  cfg_address = readCfgAddress();
  motInit();
  motTimerInit();
  uartInit();
  uartRxOn();
  __enable_interrupt();
  SET_STATUS_MOTOR_OK(status);
  
  LED_ODR = 1;
  while(1) {
    if(uartRxNewDataFlag && uartRxBufferCount == REQUEST_FRAME_LENGTH) {
      if(isFrameValid(uartRxBuffer)) {
        SET_STATUS_CRC_VALID(status);
        parseRequest(uartRxBuffer, &lastReq);
        if(lastReq.address == cfg_address) {
          uartTxOn();
          __disable_interrupt();
          if(lastReq.command == REQUEST_COMMAND_HALT) {            
            motor.target_angle = motor.current_angle;
            motor.speed = 0;            
            motor.is_enabled = 1;
          } else if(lastReq.command == REQUEST_COMMAND_DISABLE) {
            motor.target_angle = 0;
            motor.current_angle = 0;
            motor.speed = 0;
            motor.is_enabled = 0;
          } else if(lastReq.command == REQUEST_COMMAND_SET_HOME) {
            uint32_t angle = motor.target_angle;
            angle += MOTOR_ANGLE_MAX - motor.current_angle;
            angle %= MOTOR_ANGLE_MAX;
            motor.target_angle = (uint16_t) angle;
            motor.current_angle = 0;            
          } else if(lastReq.command == REQUEST_COMMAND_ROTATE) {
            updateMotorTargetAndSpeed(&motor, &lastReq);
            motor.is_enabled = 1;
          }
          __enable_interrupt();
          motUpdate(&motor);
          uint8_t resp[RESPONSE_FRAME_LENGTH] = {0};
          createResponse(resp, motor, &status, &cfg_address);
          uartSend(resp, RESPONSE_FRAME_LENGTH);
        } else {
          //LED_ODR = 1;
        }
      } else {
        RESET_STATUS_CRC_VALID(status);
        //LED_ODR = 1;
      }
      uartRxNewDataFlag = 0;
      uartRxBufferCount = 0;
    }
    if(uartTxCompletedFlag) {      
      uartRxOn();
      //LED_ODR = 1;
      uartTxCompletedFlag = 0;
    }
    LED_ODR = ~MOT_STEP_IDR;
  }
}

uint8_t readCfgAddress() {
  uint8_t addr = 0x3;
  addr &= CFG_ID0_IDR;
  addr &= CFG_ID1_IDR<<1;
  return addr;
}
