#include "Game.h"

Game::Game()
{

}

Game::~Game()
{
    // Delete the tasks on game exit to free up resources
    if (BluetoothTaskHandle != NULL) vTaskDelete(BluetoothTaskHandle);
    if (WiFiTaskHandle != NULL) vTaskDelete(WiFiTaskHandle);
}

void Game::Init()
{
    Serial.println("\n------------[Initializing Game]------------");
    btClient.Init();
    pinMode(BUTTON_PIN, INPUT);
    api.Init();

    // gyro.Init();

    // Create the tasks for Bluetooth and WiFi handling
    xTaskCreatePinnedToCore(
        BluetoothTask,        // Function that implements the task
        "BluetoothTask",      // Name of the task
        10000,                // Stack size (in words) for the task
        this,                 // Parameter passed to the task (Game object)
        1,                    // Priority of the task
        &BluetoothTaskHandle, // Task handle for Bluetooth
        0                     // Run on core 0 (for dual-core devices like ESP32)
    );
    
    xTaskCreatePinnedToCore(
        WiFiTask,             // Function that implements the task
        "WiFiTask",           // Name of the task
        10000,                // Stack size (in words) for the task
        this,                 // Parameter passed to the task (Game object)
        1,                    // Priority of the task
        &WiFiTaskHandle,      // Task handle for WiFi
        1                     // Run on core 1 (if applicable)
    );
}

void Game::Run()
{

}

