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



MotionController::MotionController()
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
    SendControllerData();
    if(digitalRead(BUTTON_PIN))
    {
        Serial.println("Trigger pressed!");
        SendTriggerInput();
        analogWrite(VIBRATION_MOTOR_PIN, 255);
    } else {
        analogWrite(VIBRATION_MOTOR_PIN, 0);
    }

    if(joystick.ReadJoystickClick())
    {
        SendJoystickClick();
        Serial.println("Joystick Clicked!");
    }
    
    // delay(1);
}

void MotionController::SendControllerData()
{
    // Get data from gyroscope
    GyroData gData = gyro.GetXYZ();
    JoystickData jData = joystick.GetAxis();

    // Create a JSON document
    JsonDocument jsonDoc;
    jsonDoc["method"] = CONTROLLER_AXIS_DATA_METHOD;
    jsonDoc["data"]["gX"] = gData.x;
    jsonDoc["data"]["gY"] = gData.y;
    jsonDoc["data"]["jX"] = jData.x;
    jsonDoc["data"]["jY"] = jData.y;



    udpConnection.SendJsonData(jsonDoc);
}

void MotionController::SendTriggerInput()
{
    // Create a JSON document
    JsonDocument jsonDoc;
    jsonDoc["method"] = TRIGGER_METHOD;

    udpConnection.SendJsonData(jsonDoc);
}

void MotionController::SendJoystickClick()
{
    // Create a JSON document
    JsonDocument jsonDoc;
    jsonDoc["method"] = JOYSTICK_CLICK_METHOD;
    
    udpConnection.SendJsonData(jsonDoc);
}