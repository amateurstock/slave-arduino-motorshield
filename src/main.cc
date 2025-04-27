#include <Arduino.h>
#include "functions.hh"

String buffer;
serial_state_t handshake;

void setup() {
    Serial.begin(9600);
}

void loop() {
    if (Serial.available()) {
        buffer = Serial.readStringUntil('\n');
        handshake = change_motors(buffer);

        if (handshake != SERIAL_OK) {
            Serial.println("error");
        } else {
            Serial.println("ok");
        }
    }
}