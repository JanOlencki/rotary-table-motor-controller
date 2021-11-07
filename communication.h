#ifndef __COMMUNICATION_H__
#define __COMMUNICATION_H__

#include "common.h"
#include "motor.h"

#define PREAMBLE (0x5D)
#define REQUEST_ADDRESS_BROADCAST (0xF)
#define REQUEST_COMMAND_GET_STATUS (0x0)
#define REQUEST_COMMAND_SET_HOME (0x1)
#define REQUEST_COMMAND_HALT (0x2)
#define REQUEST_COMMAND_DISABLE (0x3)
#define REQUEST_COMMAND_ROTATE (0x4)
#define REQUEST_FRAME_LENGTH (6)
#define RESPONSE_FRAME_LENGTH (9)
#define RESPONSE_HEADER (0xF)
typedef struct {
  uint8_t address, command;
  uint8_t payload[3];
} RequestFrame;

typedef uint8_t Status;
#define STATUS_MOTOR_OK_MASK (1<<0)
#define STATUS_ROTATING_MASK (1<<1)
#define STATUS_ENABLED_MASK (1<<2)
#define STATUS_CRC_VALID_MASK (1<<3)
#define SET_STATUS_MOTOR_OK(status) ((status) |= STATUS_MOTOR_OK_MASK)
#define SET_STATUS_ROTATING(status) ((status) |= STATUS_ROTATING_MASK)
#define SET_STATUS_ENABLED(status) ((status) |= STATUS_ENABLED_MASK)
#define SET_STATUS_CRC_VALID(status) ((status) |= STATUS_CRC_VALID_MASK)
#define RESET_STATUS_MOTOR_OK(status) ((status) &= ~STATUS_MOTOR_OK_MASK)
#define RESET_STATUS_ROTATING(status) ((status) &= ~STATUS_ROTATING_MASK)
#define RESET_STATUS_ENABLED(status) ((status) &= ~STATUS_ENABLED_MASK)
#define RESET_STATUS_CRC_VALID(status) ((status) &= ~STATUS_CRC_VALID_MASK)
#define GET_STATUS_MOTOR_OK(status) ((status) & STATUS_MOTOR_OK_MASK)
#define GET_STATUS_ROTATING(status) ((status) & STATUS_ROTATING_MASK)
#define GET_STATUS_ENABLED(status) ((status) & STATUS_ENABLED_MASK)
#define GET_STATUS_CRC_VALID(status) ((status) & STATUS_CRC_VALID_MASK)


uint8_t isFrameValid(uint8_t data[]);
void parseRequest(uint8_t data[], RequestFrame *req);
void updateMotorTargetAndSpeed(volatile MotorSettings *motor, RequestFrame *req);
void createResponse(uint8_t resp[], MotorSettings motor, Status *status, uint8_t *addr);
uint8_t calcCRC8(uint8_t data[], uint8_t len);
                                       
#endif