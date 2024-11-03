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

#include "game_controller.h"

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
    if (connTaskHandle != NULL) vTaskDelete(connTaskHandle);
}

void GameController::init()
{
    xTaskCreatePinnedToCore(
        connectionsTask,
        CONN_TASK_NAME,
        CONN_TASK_STACK_SIZE,
        &conn,
        CONN_TASK_PRIORITY,
        &connTaskHandle,
        CONN_TASK_CORE
    );
    vTaskDelay(TIMEOUT_DELAY / portTICK_PERIOD_MS);
    Serial.print("Init: Executing on core ");
    Serial.println(xPortGetCoreID());

    initLed();
    setLedRGB(blue);
    while(!conn.getConnection())
    {
        vTaskDelay(TIMEOUT_DELAY / portTICK_PERIOD_MS);
        Serial.print(".");
    }
    
    sRender.init(SCREEN_ROTATION, true, TFT_BLACK);
}

void GameController::loop()
{
    switch(state)
    {
        case Intro:
            // Intro screen
            showIntro();
            break;
        case Playing:
            // Gameplay
            play();
            break;
        case EndGame:
            // Fill in name
            end();
            break;
        case ShowingHighScores:
            // Show highscores from database
            showHighScores();
            break;
        default:
            Serial.println("State Error Unrecognized state: " + state);
            break;    
    }
    vTaskDelay(TIMEOUT_DELAY / portTICK_PERIOD_MS);
}

void GameController::showIntro()
{
    Serial.println("------Showing Intro Sequence------");
    

    // Create session and show its id on screen
    settings = {};
    while(settings.sessionId == 0) {
        settings.sessionId = conn.createSession();
        sRender.renderIntro(settings.sessionId);
        vTaskDelay(BIG_TIMEOUT_DELAY / portTICK_PERIOD_MS);
    }

    // Start polling until a player id is found
    Serial.print("Start polling.");
    JsonDocument response;
    int playerId = 0;
    setLedRGB(yellow);

    while(settings.playerId  == 0)
    {
        response = conn.getSessionById(settings.sessionId);
        if(response["player_id"]) {
            settings.playerId = response["player_id"];
            settings.difficultyId = response["difficulty_id"];
            settings.useGyro = response["use_gyro"];
            Serial.println("Player connected to session!");
            Serial.printf("Difficulty: %d\nPlayerId: %d\nUse gyro: %d\n" , settings.difficultyId, settings.playerId, settings.useGyro);
        } else {
            Serial.print(".");
        }

        vTaskDelay(TIMEOUT_DELAY / portTICK_PERIOD_MS);
    }
    Serial.println();
    setLedRGB(green);

    settings.startTime = millis();

    state = Playing;
}

void GameController::play()
{
    Serial.println("------Start Gameplay------");

    settings.score = 0;
    conn.setListenForPackets(true);
    sRender.gameLoop(settings);
    conn.createScore(settings.sessionId, settings.score);
    conn.setListenForPackets(false);
    
    state = ShowingHighScores;
}

void GameController::showHighScores()
{
    Serial.println("------Showing Highscores------");
    
    sRender.renderHighscores(conn.getHighscores());
    state = EndGame;
}

void GameController::end()
{
    Serial.println("------Ending Game------");

    //TODO: Either quit or restart based on user input
    conn.setListenForPackets(true);
    bool keepPlaying = sRender.renderEndScreen(settings.useGyro);
    conn.setListenForPackets(false);

    keepPlaying ? state = Playing : state = Intro;
}

void GameController::initLed()
{
    // Initialize GPIO pins for RGB LED
    pinMode(LED_PIN_R, OUTPUT);
    pinMode(LED_PIN_G, OUTPUT);
    pinMode(LED_PIN_B, OUTPUT);

    // Initialize LED control channels
    ledcSetup(LED_R_CHANNEL, kFreq, kResolution);
    ledcSetup(LED_G_CHANNEL, kFreq, kResolution);
    ledcSetup(LED_B_CHANNEL, kFreq, kResolution);
    
    // Attach channels to pins
    ledcAttachPin(LED_PIN_R, LED_R_CHANNEL);
    ledcAttachPin(LED_PIN_G, LED_G_CHANNEL);
    ledcAttachPin(LED_PIN_B, LED_B_CHANNEL);
}

void GameController::setLedRGB(RGBColor color, float brightness)
{
    ledcWrite(LED_R_CHANNEL, 255 - color.r * brightness);
    ledcWrite(LED_G_CHANNEL, 255 - color.g * brightness);
    ledcWrite(LED_B_CHANNEL, 255 - color.b * brightness);
}