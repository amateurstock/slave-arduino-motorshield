#include <HardwareSerial.h>
#include <AFMotor.h>
#include <string.h>

typedef enum {
    SERIAL_OK,
    SERIAL_ERROR
}serial_state_t;

serial_state_t change_motors(String command);
serial_state_t get_key_value(
    char *buf,
    const char *target,
    char query,
    char terminator,
    uint32_t offset
);

void grouped_motor_update(
    AF_DCMotor &motor1,
    AF_DCMotor &motor2,
    int16_t val
);