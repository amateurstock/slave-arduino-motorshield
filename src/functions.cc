#include "functions.hh"

AF_DCMotor m1(1);
AF_DCMotor m2(2);
AF_DCMotor m3(3);
AF_DCMotor m4(4);

void change_motors(String command) {
    char l_buf[32] = {0};
    char r_buf[32] = {0};
    const char *target = command.c_str();

    get_key_value(l_buf, target, 'L', ';', 2);
    get_key_value(l_buf, target, 'R', ';', 2);

    int16_t l_tmp = atoi(l_buf);
    int16_t r_tmp = atoi(r_buf);

    grouped_motor_update(m1, m2, l_tmp);
    grouped_motor_update(m3, m4, r_tmp);
}

void get_key_value(
    char *buf,
    const char *target,
    char query,
    char terminator,
    uint32_t offset
) {
    const char *p = strchr(target, query) + offset;
    if (!p) {
        buf[0] = '\0';
        return;
    }

    const char *end = strchr(p, terminator);
    if (!end) {
        buf[0] = '\0';
        return;
    }

    uint32_t index = 0;
    while (p != end) {
        buf[index] = *p;
        index += 1; p += 1;
    }
    buf[index] = '\0';
}

void grouped_motor_update(
    AF_DCMotor &motor1,
    AF_DCMotor &motor2,
    int16_t val
) {
    uint8_t cmd = FORWARD;
    if (val < 0) {
        cmd = BACKWARD;
        val = val * -1;
    } else if (val == 0) {
        cmd = BRAKE;
    }
    motor1.setSpeed(val);
    motor1.run(cmd);
    motor2.setSpeed(val);
    motor2.run(cmd);
}