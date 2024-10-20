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
    while(!conn.Connect())
    {
        vTaskDelay(TIMEOUT_DELAY / portTICK_PERIOD_MS);
        Serial.print(".");
    }
    SetLedRGB(green);
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
    JsonDocument res = conn.MakeAPICall("POST", "session");
    
    String message = res["message"];
    int sessionId = res["id"];
    Serial.println(message);
    
    sRender.ShowIntro(sessionId);
    state = Playing;
}

void GameController::Play()
{
    Serial.println("------Start Gameplay------");
    
    //TODO: Add settings received from session
    sRender.GameLoop(EASY, false);

    // If game ended setState to End
    state = EndGame;
}

void GameController::ShowHighScores()
{
    Serial.println("------Showing Highscores------");
    sRender.ShowHighscores();
}

void GameController::End()
{
    Serial.println("------Ending Game------");
}
void GameController::Restarting()
{
    Serial.println("------Restart Sequence------");
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