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
        /**
         * Initializes the joystick by setting up power direction for the x, y and sw pins.
         * This method prepares the joystick for reading input values.
         */
        void init();

        /**
         * Reads the state of the joystick click button.
         * @return {bool} - Returns true if the joystick button is pressed, otherwise false.
         */
        bool readJoystickClick();

        /**
         * Reads the current x and y axis values from the joystick and updates internal data.
         * This method is intended to be called to refresh the joystick position values.
         */
        void readJoystickAxis();

        /**
         * Retrieves the normalized x and y axis values of the joystick.
         * @return {JoystickData} - A struct containing the x and y values normalized to the specified output range.
         */
        JoystickData getAxis();

    private:
        JoystickData data = {0.0f, 0.0f};

        /**
         * Normalizes the raw x and y axis values from the joystick to a specified output range.
         * This method maps the raw input range to a normalized range.
         *
         * @param {int} x - The raw x-axis value from the joystick.
         * @param {int} y - The raw y-axis value from the joystick.
         */
        void normalizeAxis(int x, int y);

        #define RANGE_IN_MIN JOYSTICK_RANGE_IN_MIN
        #define RANGE_IN_MAX JOYSTICK_RANGE_IN_MAX
        #define RANGE_OUT_MIN JOYSTICK_RANGE_OUT_MIN
        #define RANGE_OUT_MAX JOYSTICK_RANGE_OUT_MAX
};


#endif