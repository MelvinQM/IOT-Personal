#include "GameController.h"

/**
 * DONT FORGET TO CHANGE THE USER_SETUP.H IN THE TFT_eSPI lib inside .pio/libdeps
 */
GameController::GameController() {}
GameController::~GameController()
{
    // Delete the tasks on game exit to free up resources
    // if (BluetoothTaskHandle != NULL) vTaskDelete(BluetoothTaskHandle);
    if (WiFiTaskHandle != NULL) vTaskDelete(WiFiTaskHandle);
}

void GameController::Init()
{
    conn.Init();
    xTaskCreatePinnedToCore(
        WiFiTask,             // Function that implements the task
        "WiFiTask",           // Name of the task
        5000,                // Stack size (in words) for the task
        &conn,                 // Parameter passed to the task
        1,                    // Priority of the task
        &WiFiTaskHandle,      // Task handle for WiFi
        0                     // Run on core 1
    );
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    Serial.print("Init: Executing on core ");
    Serial.println(xPortGetCoreID());

    // Start the tft display and set it to black
    tft.init();
    tft.setRotation(1); //This is the display in landscape
    tft.setSwapBytes(true);

    // Clear the screen before writing to it
    tft.fillScreen(TFT_BLACK);
    
    cursor.setColorDepth(16);
    cursor.createSprite(cursorSpriteRatio, cursorSpriteRatio);

    gyroText.createSprite(240,40);

    background.setColorDepth(8);
    background.createSprite(screenWidth, screenHeight);
    background.setSwapBytes(true); // Correct color
}

void GameController::Loop()
{
    switch(state)
    {
        case Intro:
            // Intro screen
            ShowIntro();
            break;
        case Playing:
            // Gameplay
            Play();
            break;
        case EndGame:
            // Fill in name
            End();
            break;
        case ShowingHighScores:
            // Show highscores from database
            ShowHighScores();
            break;
        case Restart:
            // Restart? Button
            Restarting();
            break;
        default:
            Serial.println("State Error Unrecognized state: " + state);
            break;    
    }
    delay(1000);
}

void GameController::ShowIntro()
{
    Serial.println("------Showing Intro Sequence------");
    state = Playing;
}

// float x = 50;
// float y = 50;
void GameController::Play()
{
    Serial.println("------Start Gameplay------");
    bool isRunning = true;
    while(isRunning)
    {
        background.pushImage(0, 0, screenWidth, screenHeight, backgroundSprite);
        gyroText.setTextColor(TFT_WHITE,TFT_BLACK);
        gyroText.fillSprite(TFT_BLACK);
        gyroText.drawString("X: " + String(conn.gyroData.x) + ", Y: " + String(conn.gyroData.y),0,0,4);
        gyroText.pushToSprite(&background,10,10,TFT_BLACK);

        cursor.pushImage(0, 0, cursorSpriteRatio, cursorSpriteRatio, cursorSprite);
        cursor.pushToSprite(&background, conn.gyroData.x, conn.gyroData.y, TFT_BLACK); 
        
        background.pushSprite(0,0);

        // vTaskDelay(100 / portTICK_PERIOD_MS);

        // cursor.pushImage(0, 0, cursorSpriteRatio, cursorSpriteRatio, cursorSpriteRed);
        // cursor.pushToSprite(&background, conn.gyroData.x, conn.gyroData.y, TFT_BLACK); 
        // background.pushSprite(0,0);

        vTaskDelay(100 / portTICK_PERIOD_MS);

        // If end game is triggered set running to false
        // TODO: Think of a reason to end the game
    }

    // If game ended setState to End
    state = EndGame;
}

void GameController::End()
{
    Serial.println("------Ending Game------");
    // Fill in name
}
void GameController::ShowHighScores()
{
    Serial.println("------Showing Highscores------");
}
void GameController::Restarting()
{
    Serial.println("------Restart Sequence------");
}