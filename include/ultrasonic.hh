#ifndef ULTRASONIC_HH
#define ULTRASONIC_HH

#include <Arduino.h>

typedef enum {
    IDLE,
    WAIT_FALL
} sonar_state_t;

class Ultrasonic {
public:
    uint8_t _trig_pin;
    uint8_t _echo_pin;
    uint32_t _max_distance;
    volatile uint8_t _reading = 255;

    uint32_t _echo_start = 0;
    volatile uint32_t _echo_end = 0;
    uint32_t _start_time = 0;
    volatile uint32_t _last_time = 0;
    volatile sonar_state_t _state = IDLE;

    void (*_isr_fall)(void);

    Ultrasonic(
        uint8_t trig_pin,
        uint8_t echo_pin,
        uint32_t max_distance,
        void (*isr_fall)(void)
    );
};

void setup_ultrasonic_pins(Ultrasonic &ultrasonic);
void poll_ultrasonic(Ultrasonic &ultrasonic);
uint32_t pull_ultrasonic(Ultrasonic &ultrasonic);

void ultrasonic1_fall();
void ultrasonic2_fall();
void ultrasonic3_fall();

#endif
