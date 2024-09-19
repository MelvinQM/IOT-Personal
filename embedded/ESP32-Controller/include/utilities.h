#ifndef UTILITIES_H
#define UTILITIES_H

#include <Arduino.h>

#define BUTTON_PIN 21

struct GyroData {
    float x;
    float y;
    // float z; Z is redundant for moving a cursor on a 2d surface
};

#endif