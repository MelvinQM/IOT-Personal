/*
 * Author: Melvin Moes
 * Date: October 18, 2024
 * Description: An implementation of the GameController class, which manages 
 * the game statemachine. It includes methods for initializing the game, handling the main game loop, 
 * and managing the game state. This class created a SpriteRenderer class for handling the display and sprites. 
 * It also integrates the Connections class for managing network connectivity 
 * and communications. A separate task is created to manage Wi-Fi connections 
 * concurrently. 
 * License: This project is licensed under the MIT License.
 */

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
    if (ConnTaskHandle != NULL) vTaskDelete(ConnTaskHandle);
}

void GameController::Init()
{
    xTaskCreatePinnedToCore(
        ConnectionsTask,
        CONN_TASK_NAME,
        CONN_TASK_STACK_SIZE,
        &conn,
        CONN_TASK_PRIORITY,
        &ConnTaskHandle,
        CONN_TASK_CORE
    );
    vTaskDelay(TIMEOUT_DELAY / portTICK_PERIOD_MS);
    Serial.print("Init: Executing on core ");
    Serial.println(xPortGetCoreID());

    InitLed();
    SetLedRGB(blue);
    while(!conn.GetConnection())
    {
        vTaskDelay(TIMEOUT_DELAY / portTICK_PERIOD_MS);
        Serial.print(".");
    }
    
    sRender.InitializeDisplay(SCREEN_ROTATION, true, TFT_BLACK);
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
        default:
            Serial.println("State Error Unrecognized state: " + state);
            break;    
    }
    vTaskDelay(TIMEOUT_DELAY / portTICK_PERIOD_MS);
}

void GameController::ShowIntro()
{
    Serial.println("------Showing Intro Sequence------");
    
    // Reset settings
    settings = {};

    // Create session and show its id on screen
    settings.sessionId = conn.CreateSession();
    sRender.ShowIntro(settings.sessionId);

    // Start polling until a player id is found
    Serial.print("Start polling.");
    JsonDocument response;
    int playerId = 0;
    SetLedRGB(yellow);

    // unsigned long startTime;
    // unsigned long timeoutDuration = 10000;
    while(settings.playerId  == 0)
    {
        // // Check if 10 seconds have passed
        // if (millis() - startTime >= timeoutDuration) {
        //     Serial.println("Timeout! No player connected.");
        //     break; // Exit the loop after 10 seconds
        // }

        response = conn.GetSessionById(settings.sessionId);
        if(response["player_id"]) {
            settings.playerId = response["player_id"];
            settings.difficultyId = response["difficulty_id"];
            settings.useGyro = response["use_gyro"];
            Serial.println("Player connected to session!");
            Serial.printf("Difficulty: %d\nPlayerId: %d\nUse gyro: %d\n" , settings.difficultyId, settings.playerId, settings.useGyro);
        } else {
            Serial.print(".");
        }

        vTaskDelay(BIG_TIMEOUT_DELAY / portTICK_PERIOD_MS);
    }
    Serial.println();
    SetLedRGB(green);

    settings.startTime = millis();

    state = Playing;
}

void GameController::Play()
{
    Serial.println("------Start Gameplay------");
    
    //TODO: Add settings received from session
    sRender.GameLoop(settings);

    // Upload score
    conn.CreateScore(settings.sessionId, settings.score);

    // If game ended setState to Highscores
    state = ShowingHighScores;
}

void GameController::ShowHighScores()
{
    Serial.println("------Showing Highscores------");
    
    //TODO: Fetch highscores
    
    sRender.ShowHighscores();

    // After some time go to end screen
    state = EndGame;
}

void GameController::End()
{
    Serial.println("------Ending Game------");
    //TODO: Either quit or restart based on user input
    state = Playing;
}

void GameController::InitLed()
{
    // Initialize GPIO pins for RGB LED
    pinMode(LED_PIN_R, OUTPUT);
    pinMode(LED_PIN_G, OUTPUT);
    pinMode(LED_PIN_B, OUTPUT);

    // Initialize LED control channels
    ledcSetup(LED_R_CHANNEL, freq, resolution);
    ledcSetup(LED_G_CHANNEL, freq, resolution);
    ledcSetup(LED_B_CHANNEL, freq, resolution);
    
    // Attach channels to pins
    ledcAttachPin(LED_PIN_R, LED_R_CHANNEL);
    ledcAttachPin(LED_PIN_G, LED_G_CHANNEL);
    ledcAttachPin(LED_PIN_B, LED_B_CHANNEL);
}

void GameController::SetLedRGB(RGBColor color, float brightness)
{
    ledcWrite(LED_R_CHANNEL, 255 - color.r * brightness);
    ledcWrite(LED_G_CHANNEL, 255 - color.g * brightness);
    ledcWrite(LED_B_CHANNEL, 255 - color.b * brightness);
}