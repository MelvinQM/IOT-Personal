#include "MotionController.h"

MotionController::MotionController()
{

}

MotionController::~MotionController()
{

}

void MotionController::Init()
{
    Serial.println("\n------------[Initializing Game]------------");
    //gyro.Init();

    udpConnection.Init();
}

void MotionController::Run() 
{
    //gyro.Loop();
    udpConnection.ReceivePackets();
    //Wait for 1 second
    delay(1000);
}

