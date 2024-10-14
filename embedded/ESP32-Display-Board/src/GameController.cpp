#include "GameController.h"

/**
 * DONT FORGET TO CHANGE THE USER_SETUP.H IN THE TFT_eSPI lib inside .pio/libdeps
 */
GameController::GameController() 
{
    Serial.begin(BAUD_RATE);
}
GameController::~GameController()
{
    // Delete the tasks on game exit to free up resources
    // if (BluetoothTaskHandle != NULL) vTaskDelete(BluetoothTaskHandle);
    if (WiFiTaskHandle != NULL) vTaskDelete(WiFiTaskHandle);
}

void GameController::Init()
{
    xTaskCreatePinnedToCore(
        WiFiTask,
        WIFI_TASK_NAME,
        WIFI_TASK_STACK_SIZE,
        &conn,
        WIFI_TASK_PRIORITY,
        &WiFiTaskHandle,
        WIFI_TASK_CORE
    );
    vTaskDelay(TIMEOUT_DELAY / portTICK_PERIOD_MS);

    Serial.print("Init: Executing on core ");
    Serial.println(xPortGetCoreID());

    // Start the tft display
    tft.init();
    tft.setRotation(SCREEN_ROTATION);
    tft.setSwapBytes(true);

    // Clear the screen before writing to it
    tft.fillScreen(TFT_BLACK);
    
    cursor.setColorDepth(cursorColorDepth);
    cursor.createSprite(cursorSpriteRatio, cursorSpriteRatio);

    gyroText.createSprite(axisTextWidth, axisTextHeight);

    background.setColorDepth(backgroundColorDepth);
    background.createSprite(SCREEN_WIDTH, SCREEN_HEIGHT);
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
    vTaskDelay(TIMEOUT_DELAY / portTICK_PERIOD_MS);
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
    int x = SCREEN_WIDTH / 2;
    int y = SCREEN_HEIGHT / 2;
    while(isRunning)
    {
        background.pushImage(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, SCREEN_WIDTH, SCREEN_HEIGHT, backgroundSprite);
        gyroText.setTextColor(TFT_WHITE,TFT_BLACK);
        gyroText.fillSprite(TFT_BLACK);
        gyroText.drawString("X: " + String(x) + ", Y: " + String(y), SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, 4);
        gyroText.pushToSprite(&background, 10, 10, TFT_BLACK);

        cursor.pushImage(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, cursorSpriteRatio, cursorSpriteRatio, cursorSprite);
        if(USE_GYRO) {
            x = conn.gyroData.x;
            y = conn.gyroData.y;
        } else {
            x += conn.joystickData.x * CURSOR_SPEED;
            y += conn.joystickData.y * CURSOR_SPEED;

            if(x > SCREEN_WIDTH) x = SCREEN_WIDTH;
            if(y > SCREEN_HEIGHT) y = SCREEN_HEIGHT;
            if(x < SCREEN_ORIGIN_X) y = SCREEN_ORIGIN_X;
            if(y < SCREEN_ORIGIN_Y) y = SCREEN_ORIGIN_Y;
        }
        cursor.pushToSprite(&background, x, y, TFT_BLACK); 
        
        background.pushSprite(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y);

        // cursor.pushImage(0, 0, cursorSpriteRatio, cursorSpriteRatio, cursorSpriteRed);
        // cursor.pushToSprite(&background, conn.gyroData.x, conn.gyroData.y, TFT_BLACK); 
        // background.pushSprite(0,0);

        vTaskDelay(REFRESH_RATE / portTICK_PERIOD_MS);

        // If end game is triggered set running to false
        // TODO: Think of a reason to end the game
    }

    // If game ended setState to End
    state = EndGame;
}

void GameController::End()
{
    Serial.println("------Ending Game------");
}
void GameController::ShowHighScores()
{
    Serial.println("------Showing Highscores------");
}
void GameController::Restarting()
{
    Serial.println("------Restart Sequence------");
}