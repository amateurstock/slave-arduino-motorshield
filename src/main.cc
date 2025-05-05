#include <Arduino.h>
#include "functions.hh"
#include "ultrasonic.hh"

//#define HARDWARE_TEST

#ifndef HARDWARE_TEST
String buffer;
serial_state_t handshake;
Ultrasonic ultrasonic1(2, 3, 100, ultrasonic1_fall);
uint32_t &timestamp = ultrasonic1._start_time;
char send_buf[64] = {0};

void setup() {
    Serial.begin(9600);
    timestamp = millis();
}

void loop() {
    if (Serial.available()) {
        buffer = Serial.readStringUntil('x');
        handshake = change_motors(buffer);

        if (handshake != SERIAL_OK) {
            Serial.print("errorx");
        }
    }
    if ((millis() - timestamp) >= 50) {
        timestamp = millis();
        pull_ultrasonic(ultrasonic1);
        poll_ultrasonic(ultrasonic1);

        sprintf(send_buf, "d:%ld;x", ultrasonic1._reading);
        Serial.println(send_buf);
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