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