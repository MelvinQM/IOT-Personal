#ifndef UTILITIES_H
#define UTILITIES_H

#include <Arduino.h>

struct GyroData {
    int x;
    int y;
    // int z; Z is redundant for moving a cursor on a 2d surface
};

#define BUTTON_PIN 22

#endif