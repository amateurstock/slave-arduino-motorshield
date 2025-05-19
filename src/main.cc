#include <Arduino.h>
#include "functions.hh"

//#define HARDWARE_TEST
//#define ULTRASONIC_ON

#define TRIG 2
#define ECHO 3

#ifndef HARDWARE_TEST
String buffer;
serial_state_t handshake;

#ifdef ULTRASONIC_ON
char send_buf[64] = {0};
uint32_t timestamp = 0;
uint32_t duration = 0;
uint8_t distance = 0;
#endif

void setup() {
    Serial.begin(9600);

#ifdef ULTRASONIC_ON
    timestamp = millis();
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
#endif
}

void loop() {
    if (Serial.available()) {
        buffer = Serial.readStringUntil('x');
        handshake = change_motors(buffer);

        if (handshake != SERIAL_OK) {
            Serial.println("errorx");
        }
    }

#ifdef ULTRASONIC_ON
    if ((millis() - timestamp) >= 1000) {
        timestamp = millis();
        digitalWrite(TRIG, LOW); delayMicroseconds(2);
        digitalWrite(TRIG, HIGH); delayMicroseconds(10);
        digitalWrite(TRIG, LOW);

        duration = pulseIn(ECHO, HIGH, 10000);
        distance = duration * 0.034 / 2;

        sprintf(send_buf, "d:%d;x", distance);
        Serial.println(send_buf);
    }
#endif

}

#else
L298N test_motor1(4, 5, 9);
L298N test_motor2(6, 7, 10);

void setup() {
    Serial.println("Setting up.");
    Serial.begin(9600);
}

void loop() {
    test_motor1.updateMotor(L298N::FORWARD, 100);
    test_motor2.updateMotor(L298N::FORWARD, 100);
    delay(2000);

    test_motor1.updateMotor(L298N::BACKWARD, 100);
    test_motor2.updateMotor(L298N::BACKWARD, 100);
    delay(2000);
}

#endif

#ifdef some_shit_lmao
L:100;R:100;x
#endif