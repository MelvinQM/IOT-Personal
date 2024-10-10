#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "utilities.h"

class Joystick {
    public:
        Joystick();
        ~Joystick();
        void Init();
        void Loop();
    private:
        JoystickData data = {0.0f, 0.0f};
        void ReadJoystickClick();
        void ReadJoystickAxis();
        void NormalizeAxis(int x, int y);
        JoystickData GetAxis();

        #define RANGE_IN_MIN 0
        #define RANGE_IN_MAX 4095
        #define RANGE_OUT_MIN -1.0
        #define RANGE_OUT_MAX 1.0
};


#endif