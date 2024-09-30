#include "MotionController.h"

MotionController::MotionController() : btClient(&gyro)
{
    // Create the tasks for Bluetooth and WiFi handling
    xTaskCreatePinnedToCore(
        BluetoothTask,        // Function that implements the task
        "BluetoothTask",      // Name of the task
        10000,                // Stack size (in words) for the task
        &btClient,                 // Parameter passed to the task (Game object)
        1,                    // Priority of the task
        &BluetoothTaskHandle, // Task handle for Bluetooth
        0                     // Run on core 0 (for dual-core devices like ESP32)
    );
}

MotionController::~MotionController()
{
    // Delete the tasks on game exit to free up resources
    if (BluetoothTaskHandle != NULL) vTaskDelete(BluetoothTaskHandle);
}

void MotionController::Init()
{
    Serial.println("\n------------[Initializing Game]------------");
    gyro.Init();
}

void MotionController::Run() 
{
    gyro.Loop();
}

