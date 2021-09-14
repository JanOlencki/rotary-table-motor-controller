#include "communication.h"

uint8_t isFrameValid(uint8_t data[]) {
  if(data[0] == PREAMBLE) {
    if(data[REQUEST_FRAME_LENGTH-1] == calcCRC8(data, REQUEST_FRAME_LENGTH-1)) {
      return 1;
    }
  }
  return 0;
}

void parseRequest(uint8_t data[], RequestFrame *req) {
  req->address = data[1] >> 4;
  req->command = data[1] & 0xF;
  memcpy(&req->payload, &data[2], sizeof(req->payload));
}
void updateMotorTargetAndSpeed(volatile MotorSettings *motor, RequestFrame *req) {
  motor->target_angle = ((uint16_t)req->payload[0] << 8) | req->payload[1];
  motor->target_angle %= MOTOR_ANGLE_MAX;
  motor->target_angle &= MOTOR_ANGLE_STEP_PREC_MASK;
  motor->speed = req->payload[2];
}

void createResponse(uint8_t resp[], MotorSettings motor, Status *status, uint8_t *addr) {
  resp[0] = PREAMBLE;
  resp[1] = *addr << 4;
  resp[1] |= RESPONSE_HEADER;
  resp[2] = (uint8_t) *status;  
  if(motor.is_enabled) {
    SET_STATUS_ENABLED(resp[2]);
  } else {
    RESET_STATUS_ENABLED(resp[2]);
  }
  if(motor.is_rotating) {
    SET_STATUS_ROTATING(resp[2]);
  } else {
    RESET_STATUS_ROTATING(resp[2]);
  }
  memcpy(&resp[3], &motor.current_angle, sizeof(motor.current_angle));
  memcpy(&resp[5], &motor.target_angle, sizeof(motor.target_angle));
  resp[7] = motor.speed;
  resp[8] = calcCRC8(resp, RESPONSE_FRAME_LENGTH-1);
}

uint8_t calcCRC8(uint8_t data[], uint8_t len) {
  uint32_t crc = 0;
  int16_t i, j;
  for (j = len; j; j--, data++) {
    crc ^= (*data << 8);
    for (i = 8; i; i--) {
      if (crc & 0x8000u)
        crc ^= (0x1070u << 3);
      crc <<= 1;
    }
  }
  return (uint8_t) (crc >> 8);
}