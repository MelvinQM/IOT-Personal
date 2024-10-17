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

// General settings
#define BAUD_RATE       115200
#define TIMEOUT_DELAY   1000

// Game settings
#define CURSOR_SPEED    10
#define USE_GYRO        false

// Display settings and configurations
#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   240
#define SCREEN_ORIGIN_X 0
#define SCREEN_ORIGIN_Y 0
#define REFRESH_RATE    10
#define SCREEN_ROTATION 1   // Landscape

// Pin definitions
#define BUTTON_PIN      22

// Wifi settings
#define WIFI_TIMEOUT    10000
#define UDP_DELAY       10

// Defining the JSON method names
#define TRIGGER_METHOD              "trigger"
#define JOYSTICK_CLICK_METHOD       "joystickClick"
#define CONTROLLER_AXIS_DATA_METHOD "axisData"

// Defining data structures
struct GyroData {
    int x;
    int y;
    // int z; Z is redundant for moving a cursor on a 2d surface
};

struct JoystickData {
    float x;
    float y;
};

enum Difficulty {
    EASY,
    NORMAL,
    HARD
};

#endif