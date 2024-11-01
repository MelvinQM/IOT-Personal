/*
 * Author: Melvin Moes
 * Date: October 18, 2024
 * Description: This class implements the MotionController header. It initializes the 
 * joystick and gyroscope, manages the UDP connection for sending data to the console and handles 
 * input from a button. The Init function sets up the necessary components, while 
 * the Run function processes joystick movements, button presses, and activates a vibration motor 
 * based on input. A separate task is created for handling gyroscope data.
 * License: This project is licensed under the MIT License.
 */

#include "motion_controller.h"

MotionController::MotionController()
{
    Serial.begin(BAUD_RATE);
}

MotionController::~MotionController() {}

void MotionController::init()
{
    Serial.println("\n------------[Initializing Game]------------");
    udpConnection.init();
    joystick.init();
    gyro.init();
    pinMode(BUTTON_PIN, INPUT);
    //digitalWrite(BUTTON_PIN, HIGH);
    pinMode(VIBRATION_MOTOR_PIN, OUTPUT);


    xTaskCreatePinnedToCore(
        gyroTask,
        GYRO_TASK_NAME,
        GYRO_TASK_STACK_SIZE,
        &gyro,
        GYRO_TASK_PRIORITY,
        &gyroTaskHandle,
        GYRO_TASK_CORE
    );

    xTaskCreatePinnedToCore(
        sendControllerDataTask,
        SEND_CONTROLLER_TASK_NAME,
        SEND_CONTROLLER_TASK_STACK_SIZE,
        this,
        SEND_CONTROLLER_TASK_PRIORITY,
        &sendControllerDataTaskHandle,
        SEND_CONTROLLER_TASK_CORE
    );
}

void MotionController::loop() 
{
    handleButtonPress();
    handleJoystickClick();
    vTaskDelay(SMALL_COOLDOWN / portTICK_PERIOD_MS);
}


void MotionController::sendControllerData()
{
    // Read joystick data
    joystick.readJoystickAxis();

    // Get data from gyroscope
    GyroData gData = gyro.getXYZ();
    JoystickData jData = joystick.getAxis();

    // Create a JSON document
    JsonDocument jsonDoc;
    jsonDoc["method"] = CONTROLLER_AXIS_DATA_METHOD;
    jsonDoc["data"]["gX"] = gData.x;
    jsonDoc["data"]["gY"] = gData.y;
    jsonDoc["data"]["jX"] = jData.x;
    jsonDoc["data"]["jY"] = jData.y;

    Serial.printf("GX: %d, GY: %d\n", gData.x, gData.y);
    udpConnection.sendJsonData(jsonDoc);
}

void MotionController::sendTriggerInput()
{
    // Create a JSON document
    JsonDocument jsonDoc;
    jsonDoc["method"] = TRIGGER_METHOD;

    udpConnection.sendJsonData(jsonDoc, true);
}

void MotionController::sendJoystickClick()
{
    // Create a JSON document
    JsonDocument jsonDoc;
    jsonDoc["method"] = JOYSTICK_CLICK_METHOD;
    
    udpConnection.sendJsonData(jsonDoc, true);
}

void MotionController::handleButtonPress()
{
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - lastButtonPressTime;

    bool currentButtonState = !digitalRead(BUTTON_PIN);

    // Prevent holding down button
    if (currentButtonState && !previousButtonState)
    {
        if (elapsedTime > kButtonCooldown)
        {
            Serial.println("Button pressed");
            sendTriggerInput();
            lastButtonPressTime = currentTime;
            isVibrating = true;
            analogWrite(VIBRATION_MOTOR_PIN, VIBRATION_MOTOR_MAX);
        }
    }

    // Handle vibration duration
    if (isVibrating && (currentTime - lastButtonPressTime > kVibrationDuration))
    {
        // Stop vibrating
        analogWrite(VIBRATION_MOTOR_PIN, VIBRATION_MOTOR_MIN);
        isVibrating = false;  // Reset vibration state
    }

    previousButtonState = currentButtonState; 
}

void MotionController::handleJoystickClick()
{
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - lastButtonPressTime;
    bool currentButtonState = joystick.readJoystickClick();

    // Prevent holding down button
    if (currentButtonState && !previousJoystickClickState)
    {
        if (elapsedTime > kButtonCooldown)
        {
            Serial.println("Joystick Clicked!");
            sendJoystickClick();
            lastJoystickClickTime = currentTime;
        }
        
    }

    previousJoystickClickState = currentButtonState; 
}