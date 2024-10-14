/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: This header file defines the GameController class, which manages 
 * the game statemachine. It includes methods for initializing 
 * the game, handling the main game loop, and managing different game states 
 * (Intro, Playing, EndGame, ShowingHighScores, and Restart). The class utilizes 
 * the TFT_eSPI library for handling graphics and displays a cursor and background 
 * sprites. It also integrates the Connections class for managing network connectivity 
 * and communications. A separate task is created to manage Wi-Fi connections 
 * concurrently. 
 * License: This project is licensed under the MIT License.
 */

#ifndef GAME_H
#define GAME_H

#include "utilities.h"
#include <TFT_eSPI.h>
#include "sprites/cursor.h"
#include "sprites/background.h"
#include "Connections.h"

class GameController 
{
    public:
        GameController();
        ~GameController();
        void Init();
        void Loop();
    private:
        Connections conn;

        TFT_eSPI tft = TFT_eSPI();
        TFT_eSprite cursor = TFT_eSprite(&tft);
        TFT_eSprite background = TFT_eSprite(&tft);
        TFT_eSprite gyroText = TFT_eSprite(&tft);
        float screenWidth = 320;
        float screenHeight = 240;
        int cursorSpriteRatio = 40;
        
        TaskHandle_t WiFiTaskHandle = NULL;
        static void WiFiTask(void *pvParameters)
        {
            Connections* conn = static_cast<Connections*>(pvParameters);
            pinMode(BUTTON_PIN, INPUT); // Test button
            conn->Init();
            for (;;)
            {
                conn->Loop();
            }
        }

        enum GameState
        {
            Intro,
            Playing,
            EndGame,
            ShowingHighScores,
            Restart,
        };

        GameState state = Intro;

        void ShowIntro();
        void Play();
        void End();
        void ShowHighScores();
        void Restarting();
};

#endif