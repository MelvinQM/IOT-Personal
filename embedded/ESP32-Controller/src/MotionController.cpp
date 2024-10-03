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


    xTaskCreatePinnedToCore(
        GyroTask,             // Function that implements the task
        "WiFiTask",           // Name of the task
        5000,                 // Stack size (in words) for the task
        &gyro,                // Parameter passed to the task
        1,                    // Priority of the task
        &GyroTaskHandle,      // Task handle for WiFi
        0                     // Run on core 0
    );
}

void MotionController::Run() 
{
    udpConnection.SendGyroData();
    if(digitalRead(BUTTON_PIN))
    {
        Serial.println("Trigger pressed!");
        udpConnection.SendTriggerInput();
    }
    delay(50);
}

