#include "game.h"

/**
 * DONT FORGET TO CHANGE THE USER_SETUP.H IN THE TFT_eSPI lib inside .pio/libdeps
 */
Game::Game(){}
Game::~Game()
{
    // Delete the tasks on game exit to free up resources
    if (BluetoothTaskHandle != NULL) vTaskDelete(BluetoothTaskHandle);
}

void Game::Init()
{
    // xTaskCreatePinnedToCore(
    //     BluetoothTask,        // Function that implements the task
    //     "BluetoothTask",      // Name of the task
    //     2048,                 // Stack size (in words) for the task
    //     &btServer,            // Parameter passed to the task (Game object)
    //     1,                    // Priority of the task
    //     &BluetoothTaskHandle, // Task handle for Bluetooth
    //     0                     // Run on core 0 (for dual-core devices like ESP32)
    // );


    Serial.print("Init: Executing on core ");
    Serial.println(xPortGetCoreID());
    // Start the tft display and set it to black
    tft.init();
    tft.setRotation(1); //This is the display in landscape
    tft.setSwapBytes(true);

    // Clear the screen before writing to it
    tft.fillScreen(TFT_BLACK);
    
    cursor.setColorDepth(8);
    cursor.createSprite(16,16);

    gyroText.createSprite(240,40);

    background.setColorDepth(8);
    background.createSprite(screenWidth, screenHeight);
    background.setSwapBytes(true); // Correct color
}


float x = 50;
float y = 50;
void Game::Loop()
{
    background.pushImage(0, 0, screenWidth, screenHeight, backgroundSprite);

    gyroText.setTextColor(TFT_WHITE,TFT_BLACK);
    gyroText.fillSprite(TFT_BLACK);
    gyroText.drawString("X: " + String(x) + ", Y: " + String(y),0,0,4);
    gyroText.pushToSprite(&background,10,10,TFT_BLACK);

    cursor.pushImage(0, 0, 16, 16, cursorSprite);
    cursor.pushToSprite(&background, x, y, TFT_BLACK); 
    
    background.pushSprite(0,0);

    x++;
    y++;
    if (x > screenWidth) {
       x = 0;
    }
    if (y > screenHeight) {
        y = 0;
    }

    delay(1000);
}