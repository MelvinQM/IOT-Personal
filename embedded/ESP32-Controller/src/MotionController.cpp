#include "MotionController.h"

MotionController::MotionController() : udpConnection(&gyro)
{

}

MotionController::~MotionController()
{

}

void MotionController::Init()
{
    Serial.println("\n------------[Initializing Game]------------");
    gyro.Init();

    udpConnection.Init();
    pinMode(BUTTON_PIN, INPUT);
}

void MotionController::Run() 
{
    gyro.Loop();
    //Wait for 1 second
    udpConnection.SendGyroData();
    if(digitalRead(BUTTON_PIN))
    {
        Serial.println("Trigger pressed!");
        udpConnection.SendTriggerInput();
    }
    delay(1000);
}

