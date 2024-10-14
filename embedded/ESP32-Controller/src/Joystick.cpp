#include "Joystick.h"

Joystick::Joystick(){}
Joystick::~Joystick(){}

void Joystick::Init()
{
    pinMode(JOYSTICK_VRX_PIN, INPUT);
    pinMode(JOYSTICK_VRY_PIN, INPUT);
    pinMode(JOYSTICK_SW_PIN, INPUT_PULLUP);
}

void Joystick::Loop()
{
    ReadJoystickAxis();
    ReadJoystickClick();
}

bool Joystick::ReadJoystickClick()
{
    return !digitalRead(JOYSTICK_SW_PIN);
}

void Joystick::ReadJoystickAxis()
{
    NormalizeAxis(analogRead(JOYSTICK_VRX_PIN), analogRead(JOYSTICK_VRY_PIN));
    // Serial.println("X: " + String(data.x) + " Y: " + String(data.y));

}

void Joystick::NormalizeAxis(int x, int y)
{
    float nX = (x - RANGE_IN_MIN) * (RANGE_OUT_MAX - RANGE_OUT_MIN) / (RANGE_IN_MAX - RANGE_IN_MIN) + (RANGE_OUT_MIN);
    float nY = (y - RANGE_IN_MIN) * (RANGE_OUT_MAX - RANGE_OUT_MIN) / (RANGE_IN_MAX - RANGE_IN_MIN) + (RANGE_OUT_MIN);
    
    // Cut off the decimals
    nX = static_cast<int>(nX * 10) / 10.0;
    nY = static_cast<int>(nY * 10) / 10.0;

    // * -1 because to prevent inverse vertical controls
    data = {nX, nY * -1};


}

JoystickData Joystick::GetAxis()
{
    return data;
}