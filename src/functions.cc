#include "functions.hh"

constexpr uint8_t LEFT_LOG1 = 2;
constexpr uint8_t LEFT_LOG2 = 3;
constexpr uint8_t LEFT_PWM = 9;

constexpr uint8_t RIGHT_LOG1 = 4;
constexpr uint8_t RIGHT_LOG2 = 5;
constexpr uint8_t RIGHT_PWM = 10;

L298N left_motor(LEFT_LOG1, LEFT_LOG2, LEFT_PWM);
L298N right_motor(RIGHT_LOG1, RIGHT_LOG2, RIGHT_PWM);

serial_state_t change_motors(String command) {
    char l_buf[32] = {0};
    char r_buf[32] = {0};
    const char *target = command.c_str();

    if ((get_key_value(l_buf, target, 'L', ';', 2)) != SERIAL_OK) {
        return SERIAL_ERROR;
    }

    if ((get_key_value(r_buf, target, 'R', ';', 2)) != SERIAL_OK) {
        return SERIAL_ERROR;
    }

    int16_t l_tmp = atoi(l_buf);
    int16_t r_tmp = atoi(r_buf);

    motor_command_translator(left_motor, l_tmp);
    motor_command_translator(right_motor, r_tmp);

    return SERIAL_OK;
}

serial_state_t get_key_value(
    char *buf,
    const char *target,
    char query,
    char terminator,
    uint32_t offset
) {
    const char *p = strchr(target, query) + offset;
    if (!p) {
        buf[0] = '\0';
        return SERIAL_ERROR;
    }

    const char *end = strchr(p, terminator);
    if (!end) {
        buf[0] = '\0';
        return SERIAL_ERROR;
    }

    uint32_t index = 0;
    while (p != end) {
        buf[index] = *p;
        index += 1; p += 1;
    }
    buf[index] = '\0';
    return SERIAL_OK;
}

void motor_command_translator(
    L298N &motor,
    int16_t val
) {
    L298N::MotorsType cmd = L298N::FORWARD;
    if (val < 0) {
        cmd = L298N::BACKWARD;
        val = val * -1;
    } else if (val == 0) {
        cmd = L298N::STOP;
    }
    motor.updateMotor(cmd, val);
}