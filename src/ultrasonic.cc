#include "ultrasonic.hh"

constexpr uint32_t ULTRASONIC_TIMEOUT_MS = 100;

extern Ultrasonic ultrasonic1;

Ultrasonic::Ultrasonic(
    uint8_t trig_pin,
    uint8_t echo_pin,
    uint32_t max_distance,
    void (*isr_fall)(void)
) {
    _trig_pin = trig_pin;
    _echo_pin = echo_pin;
    _max_distance = max_distance;
    _isr_fall = isr_fall;
}

void setup_ultrasonic_pins(Ultrasonic &ultrasonic) {
    pinMode(ultrasonic._trig_pin, OUTPUT);
    pinMode(ultrasonic._echo_pin, INPUT);
    digitalWrite(ultrasonic._trig_pin, LOW);

    attachInterrupt(
        digitalPinToInterrupt(ultrasonic._echo_pin),
        ultrasonic._isr_fall,
        FALLING);
}

void poll_ultrasonic(Ultrasonic &ultrasonic) {
    uint32_t now = millis();
    switch (ultrasonic._state) {
        case IDLE: {
            ultrasonic._start_time = now;

            digitalWrite(ultrasonic._trig_pin, LOW);
            delayMicroseconds(2);
            digitalWrite(ultrasonic._trig_pin, HIGH);
            delayMicroseconds(10);
            digitalWrite(ultrasonic._trig_pin, LOW);

            ultrasonic._echo_start = micros();
            ultrasonic._state = WAIT_FALL;
            break;
        }
        case WAIT_FALL: {
            if (now - ultrasonic._start_time > ULTRASONIC_TIMEOUT_MS) {
                ultrasonic._state = IDLE;
                ultrasonic._reading = 255;
            }
            break;
        }
    }
}

uint32_t pull_ultrasonic(Ultrasonic &ultrasonic) {
    if (ultrasonic._state != IDLE) {
        return ultrasonic._reading;
    }
    uint32_t duration = ultrasonic._echo_end - ultrasonic._echo_start;
    // Some weird ass equation that arose from extensive testing...
    ultrasonic._reading = (duration / 57.067) - 39;
    return ultrasonic._reading;
}




// ++++++++++++++++++++++++++++++++++++++++++++++++++
// ISR Routines
// ==================================================
void ultrasonic1_fall() {
    if (ultrasonic1._state == WAIT_FALL) {
        ultrasonic1._echo_end = micros();
        ultrasonic1._state = IDLE;
        ultrasonic1._last_time = millis();
    }
}
