#ifndef UTILITIES_H
#define UTILITIES_H

#include <Arduino.h>

struct GyroData {
    int x;
    int y;
    // int z; Z is redundant for moving a cursor on a 2d surface
};

struct JoystickData {
    float x;
    float y;
};

#define USE_GYRO false
#define BUTTON_PIN 22

#endif