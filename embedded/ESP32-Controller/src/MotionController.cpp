#include "MotionController.h"

MotionController::MotionController() : udpConnection(&gyro, &joystick)
{

}

MotionController::~MotionController()
{

}

void MotionController::Init()
{
    Serial.println("\n------------[Initializing Game]------------");
    // udpConnection.Init();
    joystick.Init();
    gyro.Init();
    pinMode(BUTTON_PIN, INPUT);
    pinMode(VIBRATION_MOTOR_PIN, OUTPUT);


    xTaskCreatePinnedToCore(
        GyroTask,             // Function that implements the task
        "GyroTask",           // Name of the task
        5000,                 // Stack size (in words) for the task
        &gyro,                // Parameter passed to the task
        1,                    // Priority of the task
        &GyroTaskHandle,      // Task handle for WiFi
        0                     // Run on core 0
    );
}

void MotionController::Run() 
{
    // udpConnection.SendGyroData();
    if(digitalRead(BUTTON_PIN))
    {
        Serial.println("Trigger pressed!");
        // udpConnection.SendTriggerInput();
        analogWrite(VIBRATION_MOTOR_PIN, 255);
    } else {
        analogWrite(VIBRATION_MOTOR_PIN, 0);
    }

    if(joystick.ReadJoystickClick())
    {
        // udpConnection.SendJoystickClick();
        Serial.println("Joystick Clicked!");
    }
    
    joystick.Loop();
    delay(50);
}

