#include <Arduino.h>
#include "functions.hh"

String buffer;

void setup() {
    Serial.begin(9600);
}

void loop() {
    if (Serial.available()) {
        buffer = Serial.readStringUntil('\n');
        change_motors(buffer);
    }
}