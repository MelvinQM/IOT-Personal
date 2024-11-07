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
#include "connections.h"
#include "sprite_renderer.h"

class GameController 
{
    private:
        /**
         * @struct RGBColor
         * A structure for representing colors using RGB values.
         * It holds the red, green, and blue components of a color.
         */
        struct RGBColor {
            int r; ///< Red component of the color.
            int g; ///< Green component of the color.
            int b; ///< Blue component of the color.
        };

        /**
         * @enum GameState
         * Defines the possible states of the game.
         */
        enum GameState
        {
            Intro,
            Playing,
            ShowingHighScores,
            EndGame,
        };
    public:
        GameController();
        ~GameController();
        void init();
        void loop();
    private:
        Connections conn;
        SpriteRenderer sRender;
        GameSettings settings;

        GameState state = Intro;
        const int kFreq = 2000;
        const int kResolution = 8; 

        /**
         * Displays the into screen.
         */
        void showIntro();

        /**
         * Starts and runs the game.
         * Initiates gameplay, handling the game's main mechanics.
         */
        void play();

        /**
         * Handles the logic for ending the game and displaying the end screen.
         */
        void end();

        /**
         * Shows a page with the high scores of the players.
         */
        void showHighScores();

        /**
         * Sets up the LED display to indicate various game states or notifications.
         */
        void initLed();

        /**
         * Adjusts the RGB color of the LED with a specified brightness.
         * 
         * @param color The RGB color to set.
         * @param brightness The brightness of the LED, default value is LED_DEFAULT_BRIGHTNESS.
         */
        void setLedRGB(RGBColor color, float brightness = LED_DEFAULT_BRIGHTNESS);

        RGBColor red {255, 0, 0};
        RGBColor green {0, 255, 0};
        RGBColor blue {0, 0, 255};
        RGBColor white {255, 255, 255};
        RGBColor yellow {255, 255, 0};
        RGBColor orange {255, 165, 0};
        RGBColor off {0, 0, 0};

        TaskHandle_t connTaskHandle = NULL;
        #define CONN_TASK_STACK_SIZE    5000
        #define CONN_TASK_PRIORITY      1
        #define CONN_TASK_CORE          0
        #define CONN_TASK_NAME          "ConnectionsTask"
        /**
         * This task initializes the connection and continuously loops to handle connection logic.
         *
         * @param {void*} pvParameters - Pointer to Connections instance passed to the task.
         */
        static void connectionsTask(void *pvParameters)
        {
            Connections* conn = static_cast<Connections*>(pvParameters);
            conn->init();
            for (;;)
            {
                conn->loop();
            }
        }
};

#endif