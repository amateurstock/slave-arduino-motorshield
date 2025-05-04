#include <Arduino.h>
#include "functions.hh"

//#define HARDWARE_TEST

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

L298N test_motor1(2, 3, 9);
L298N test_motor2(4, 5, 10);

void setup() {
    Serial.println("Init");
    Serial.begin(9600);
}

void loop() {
    test_motor1.updateMotor(L298N::FORWARD, 240);
    test_motor2.updateMotor(L298N::BACKWARD, 240);
    delay(5000);

    test_motor1.updateMotor(L298N::BACKWARD, 240);
    test_motor2.updateMotor(L298N::FORWARD, 240);
    delay(5000);
}

#endif