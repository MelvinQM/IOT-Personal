#ifndef UTILITIES_H
#define UTILITIES_H

#include <Arduino.h>

#define BUTTON_PIN 21
#define GYRO_INTERRUPT_PIN 15

struct GyroData {
    int x;
    int y;
    // int z; Z is redundant for moving a cursor on a 2d surface
};

#endif