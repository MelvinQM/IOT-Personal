/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: This header defines various utility constants, pin assignments, and data structures used in the project. 
 * It also includes definitions for a button pin and data structures for joystick and gyro data.
 * License: This project is licensed under the MIT License.
 */

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
#define BAUD_RATE 115200

#endif