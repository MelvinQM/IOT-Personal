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

MotionController::~MotionController() {}

void MotionController::Init()
{
    Serial.println("\n------------[Initializing Game]------------");
    udpConnection.Init();
    joystick.Init();
    gyro.Init();
    pinMode(BUTTON_PIN, INPUT);
    pinMode(VIBRATION_MOTOR_PIN, OUTPUT);


    xTaskCreatePinnedToCore(
        GyroTask,
        GYRO_TASK_NAME,
        GYRO_TASK_STACK_SIZE,
        &gyro,
        GYRO_TASK_PRIORITY,
        &GyroTaskHandle,
        GYRO_TASK_CORE
    );
}

void MotionController::Run() 
{
    joystick.ReadJoystickAxis();
    //SendControllerData();

    HandleButtonPress();
    HandleJoystickClick();


    // vTaskDelay(1 / portTICK_PERIOD_MS);
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

unsigned long lastButtonPressTime = 0;
unsigned long buttonCooldown = 100;
unsigned long vibrationDuration = 250;
bool isVibrating = false;
bool previousButtonState = LOW;

void MotionController::HandleButtonPress()
{
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - lastButtonPressTime;

    bool currentButtonState = digitalRead(BUTTON_PIN);

    // Prevent holding down button
    if (currentButtonState && !previousButtonState)
    {
        Serial.println("Button pressed");
        if (elapsedTime > buttonCooldown)
        {
            SendTriggerInput();
            lastButtonPressTime = currentTime;
            isVibrating = true;
            analogWrite(VIBRATION_MOTOR_PIN, VIBRATION_MOTOR_MAX);
        }
    }

    // Handle vibration duration
    if (isVibrating && (currentTime - lastButtonPressTime > vibrationDuration))
    {
        // Stop vibrating
        analogWrite(VIBRATION_MOTOR_PIN, VIBRATION_MOTOR_MIN);
        isVibrating = false;  // Reset vibration state
    }

    previousButtonState = currentButtonState; 
}

void MotionController::HandleJoystickClick()
{
    if (joystick.ReadJoystickClick())
    {
        SendJoystickClick();
        Serial.println("Joystick Clicked!");
    }

}