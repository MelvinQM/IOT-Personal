/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: This class implements the MotionController header. It initializes the 
 * joystick and gyroscope, manages the UDP connection for sending data to the console and handles 
 * input from a button. The Init function sets up the necessary components, while 
 * the Run function processes joystick movements, button presses, and activates a vibration motor 
 * based on input. A separate task is created for handling gyroscope data.
 * License: This project is licensed under the MIT License.
 */

#include "MotionController.h"



MotionController::MotionController() : udpConnection(&gyro, &joystick)
{
    Serial.begin(BAUD_RATE);
}

MotionController::~MotionController()
{

}

void MotionController::Init()
{
    Serial.println("\n------------[Initializing Game]------------");
    udpConnection.Init();
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
    joystick.ReadJoystickAxis();
    udpConnection.SendControllerData();
    if(digitalRead(BUTTON_PIN))
    {
        Serial.println("Trigger pressed!");
        udpConnection.SendTriggerInput();
        analogWrite(VIBRATION_MOTOR_PIN, 255);
    } else {
        analogWrite(VIBRATION_MOTOR_PIN, 0);
    }

    if(joystick.ReadJoystickClick())
    {
        udpConnection.SendJoystickClick();
        Serial.println("Joystick Clicked!");
    }
    
    // delay(1);
}

