#include <HardwareSerial.h>
#include "L298N.hh"
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
void motor_command_translator(L298N &motor, int16_t val);