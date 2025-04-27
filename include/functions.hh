#include <HardwareSerial.h>
#include <AFMotor.h>
#include <string.h>

void change_motors(String command);
void get_key_value(
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