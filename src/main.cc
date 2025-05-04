#include <Arduino.h>
#include "functions.hh"

#define HARDWARE_TEST

#ifndef HARDWARE_TEST
String buffer;
serial_state_t handshake;

void setup() {
    Serial.begin(9600);
}

void loop() {
    if (Serial.available()) {
        buffer = Serial.readStringUntil('x');
        handshake = change_motors(buffer);

        if (handshake != SERIAL_OK) {
            Serial.print("errorx");
        }
    }
}

#else

extern AF_DCMotor m1;
extern AF_DCMotor m2;
extern AF_DCMotor m3;
extern AF_DCMotor m4;

void setup() {
    Serial.begin(9600);
}

void loop() {

    grouped_motor_update(m1, m2, 192);
    grouped_motor_update(m3, m4, 192);
    delay(2000);

    grouped_motor_update(m1, m2, -192);
    grouped_motor_update(m3, m4, 192);
    delay(2000);

    grouped_motor_update(m1, m2, 192);
    grouped_motor_update(m3, m4, -192);
    delay(2000);

    grouped_motor_update(m1, m2, -192);
    grouped_motor_update(m3, m4, -192);
    delay(2000);

}

#endif