#ifndef UTILITIES_H
#define UTILITIES_H

#include <Arduino.h>

#define BUTTON_PIN 21
#define GYRO_INTERRUPT_PIN 15
#define VIBRATION_MOTOR_PIN 47
#define JOYSTICK_VRX_PIN 1
#define JOYSTICK_VRY_PIN 2
#define JOYSTICK_SW_PIN 48

struct GyroData {
    int x;
    int y;
    // int z; Z is redundant for moving a cursor on a 2d surface
};

struct JoystickData {
    float x;
    float y;
};


#endif