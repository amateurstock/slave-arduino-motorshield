#include "functions.hh"

AF_DCMotor m1(1);
AF_DCMotor m2(2);
AF_DCMotor m3(3);
AF_DCMotor m4(4);

void change_motors(String command, uint8_t motorbuf[4]) {
    command.trim();
}




// Serial commands outline:
// ESP32 -> Uno
// String command = "M1:001; M2:029; M3:255; M4:128;\n"