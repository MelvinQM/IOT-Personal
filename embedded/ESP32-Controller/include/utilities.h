
/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: This header defines various utility constants, pin assignments, and data structures used in the 
 * motion controller project. It includes definitions for button and joystick pins and data structures for joystick and gyro data.
 * License: This project is licensed under the MIT License.
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#include <Arduino.h>
#include <ArduinoJson.h>

#define BUTTON_PIN 21
#define GYRO_INTERRUPT_PIN 15
#define VIBRATION_MOTOR_PIN 47
#define JOYSTICK_VRX_PIN 1
#define JOYSTICK_VRY_PIN 2
#define JOYSTICK_SW_PIN 48

#define BAUD_RATE 115200

struct GyroData {
    int x;
    int y;
    // int z; Z is redundant for moving a cursor on a 2d surface
};

struct JoystickData {
    float x;
    float y;
};


// Defining the JSON method names
#define TRIGGER_METHOD "trigger"
#define JOYSTICK_CLICK_METHOD "joystickClick"
#define CONTROLLER_AXIS_DATA_METHOD "axisData"

#endif