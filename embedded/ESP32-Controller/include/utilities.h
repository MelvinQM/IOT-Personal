
/*
 * Author: Melvin Moes
 * Date: October 18, 2024
 * Description: This header defines various utility constants, pin assignments, and data structures used in the 
 * motion controller project. It includes definitions for button and joystick pins and data structures for joystick and gyro data.
 * License: This project is licensed under the MIT License.
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#include <Arduino.h>
#include <ArduinoJson.h>

// Pin definitions
#define BUTTON_PIN          41
#define GYRO_INTERRUPT_PIN  15
#define VIBRATION_MOTOR_PIN 47
#define JOYSTICK_VRX_PIN    1
#define JOYSTICK_VRY_PIN    2
#define JOYSTICK_SW_PIN     41

// General settings
#define BAUD_RATE           115200
#define TIMEOUT_DELAY       1000
#define TRIGGER_COOLDOWN    100
#define SMALL_COOLDOWN      1

// Vibration motor settings
#define VIBRATION_MOTOR_MAX     255
#define VIBRATION_MOTOR_MIN     0
#define VIBRATION_COOLDOWN      200

// Joystick settings
#define NORMALIZE_FACTOR_JOYSTICK   100     // 10 = 1 decimal
#define JOYSTICK_RANGE_IN_MIN       0
#define JOYSTICK_RANGE_IN_MAX       4095
#define JOYSTICK_RANGE_OUT_MIN      -1.0
#define JOYSTICK_RANGE_OUT_MAX      1.0
#define JOYSTICK_DEAD_ZONE          0.1
#define JOYSTICK_CLICK_COOLDOWN     100     // in milis

// Gyroscope settings
#define GYRO_DELAY 50

// Defining the JSON method names
#define TRIGGER_METHOD "trigger"
#define JOYSTICK_CLICK_METHOD "joystickClick"
#define CONTROLLER_AXIS_DATA_METHOD "axisData"


// Data structures
struct GyroData {
    int x;
    int y;
};

struct JoystickData {
    float x;
    float y;
};


#endif