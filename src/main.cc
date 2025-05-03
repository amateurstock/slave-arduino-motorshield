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

void setup() {
    Serial.begin(9600);
}

void loop() {
    if (Serial.available()) {
        char c = Serial.read();
        Serial.println(c);
    }
}

#endif