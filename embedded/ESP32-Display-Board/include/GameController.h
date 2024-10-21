/*
 * Author: Melvin Moes
 * Date: October 18, 2024
 * Description: This header file defines the GameController class, which manages 
 * the game statemachine. It includes methods for initializing 
 * the game, handling the main game loop, and managing different game states. 
 * This class created a SpriteRenderer class for handling the display and sprites.
 * It also integrates the Connections class for managing network connectivity 
 * and communications.
 * License: This project is licensed under the MIT License.
 */

#ifndef GAME_H
#define GAME_H

#include "utilities.h"
#include "Connections.h"
#include "SpriteRenderer.h"

class GameController 
{
    public:
        GameController();
        ~GameController();
        void Init();
        void Loop();
    private:
        Connections conn;
        SpriteRenderer sRender;
        GameSettings settings;
        TaskHandle_t ConnTaskHandle = NULL;
        #define CONN_TASK_STACK_SIZE    5000
        #define CONN_TASK_PRIORITY      1
        #define CONN_TASK_CORE          0
        #define CONN_TASK_NAME          "ConnectionsTask"
        static void ConnectionsTask(void *pvParameters)
        {
            Connections* conn = static_cast<Connections*>(pvParameters);
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
        };

        GameState state = Intro;

        void ShowIntro();
        void Play();
        void End();
        void ShowHighScores();


        struct RGBColor {
            int r;
            int g;
            int b;
        };
        
        int freq = 2000;
        int resolution = 8; 
        void InitLed();
        void SetLedRGB(RGBColor color, float brightness = LED_DEFAULT_BRIGHTNESS);
        RGBColor red {255, 0, 0};
        RGBColor green {0, 255, 0};
        RGBColor blue {0, 0, 255};
        RGBColor white {255, 255, 255};
        RGBColor yellow {255, 255, 0};
        RGBColor orange {255, 165, 0};
        RGBColor off {0, 0, 0};
};

#endif