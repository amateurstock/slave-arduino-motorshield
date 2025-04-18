#include <Arduino.h>
#include "functions.hh"

String buffer;
uint8_t motorbuf[4] = {0, 0, 0, 0};

void setup() {
    Serial.begin(9600);
}

void loop() {
    if (Serial.available()) {
        buffer = Serial.readStringUntil('\n');
        change_motors(buffer, motorbuf);
    }
}