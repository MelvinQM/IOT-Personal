/*
 * Author: Melvin Moes
 * Date: October 18, 2024
 * Description: This header defines the Joystick class, which handles reading the joystick's x and y axis and click input. 
 * It provides methods to initialize the joystick, read its click state, and normalize the axis values for better control over motion or input.
 * License: This project is licensed under the MIT License.
 */

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "utilities.h"

class Joystick {
    public:
        void init();
        bool readJoystickClick();
        void readJoystickAxis();
        JoystickData getAxis();
    private:
        JoystickData data = {0.0f, 0.0f};
        void normalizeAxis(int x, int y);

        #define RANGE_IN_MIN JOYSTICK_RANGE_IN_MIN
        #define RANGE_IN_MAX JOYSTICK_RANGE_IN_MAX
        #define RANGE_OUT_MIN JOYSTICK_RANGE_OUT_MIN
        #define RANGE_OUT_MAX JOYSTICK_RANGE_OUT_MAX
};


#endif