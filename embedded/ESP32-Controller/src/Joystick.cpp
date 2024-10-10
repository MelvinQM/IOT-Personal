#include "Joystick.h"

Joystick::Joystick(){}
Joystick::~Joystick(){}

void Joystick::Init()
{
    pinMode(JOYSTICK_VRX_PIN, INPUT);
    pinMode(JOYSTICK_VRY_PIN, INPUT);
    pinMode(JOYSTICK_SW_PIN, INPUT);
}

void Joystick::Loop()
{
    // ReadJoystickAxis();
    ReadJoystickClick();
}

void Joystick::ReadJoystickClick()
{
    if(digitalRead(JOYSTICK_SW_PIN))
    {
        Serial.println("SW Pressed");
    }
}

void Joystick::ReadJoystickAxis()
{
    //Serial.println("X: " + String(analogRead(JOYSTICK_VRX_PIN)) + " Y: " + String(analogRead(JOYSTICK_VRY_PIN)));
    NormalizeAxis(analogRead(JOYSTICK_VRX_PIN), analogRead(JOYSTICK_VRY_PIN));
    Serial.println("X: " + String(data.x) + " Y: " + String(data.y));

}

void Joystick::NormalizeAxis(int x, int y)
{
    float nX = (x - RANGE_IN_MIN) * (RANGE_OUT_MAX - RANGE_OUT_MIN) / (RANGE_IN_MAX - RANGE_IN_MIN) + (RANGE_OUT_MIN);
    float nY = (y - RANGE_IN_MIN) * (RANGE_OUT_MAX - RANGE_OUT_MIN) / (RANGE_IN_MAX - RANGE_IN_MIN) + (RANGE_OUT_MIN);
    data = {nX, nY};
}