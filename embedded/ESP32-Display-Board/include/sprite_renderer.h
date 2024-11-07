/*
 * Author: Melvin Moes
 * Date: November 6, 2024
 * Description: This header defines a class that handles the rendering of sprites using the TFT_eSPI library. 
 * This class defines functions for the initialization of the display, handling rendering of the cursor, background, and owl/enemy sprites,
 * and their positions and logic such as collision. 
 * Based on given parameters the gameloop can be altered based on control schemes and difficulty
 * Additionally certain sprite configurations are defined here.
 * License: This project is licensed under the MIT License.
 */

#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "utilities.h"
#include <TFT_eSPI.h>

#include "sprites/cursor.h"
#include "sprites/background.h"
#include "sprites/owl.h"

#include "game_data_model.h"

class SpriteRenderer {
    private:
        /**
         * @typedef {Object} TextSpriteSettings
         * @property {int} width - The width of the sprite.
         * @property {int} height - The height of the sprite.
         * @property {int} fontSize - The font size for text elements.
         * @property {int} posX - The X position for the sprite.
         * @property {int} posY - The Y position for the sprite.
         */
        struct TextSpriteSettings {
            int width;
            int height;
            int fontSize;
            int posX;
            int posY;
        };

    public:
        /**
         * Initializes the display with specified rotation, byte swapping, and fill color.
         * @param {int} rotation - The rotation of the display (0, 90, 180, or 270).
         * @param {bool} swapBytes - If true, swap the byte order for display compatibility.
         * @param {int} fillColor - The background fill color for the display.
         */
        void init(int rotation, bool swapBytes, int fillColor);

        /**
         * Main game loop that manages the game flow and rendering.
         * @param {GameSettings} settings - The game settings affecting gameplay.
         */
        void gameLoop(GameSettings &settings);

        /**
         * Renders the introduction screen, including session ID.
         * @param {int} sessionId - The session ID to be displayed on the intro screen.
         */
        void renderIntro(int sessionId);

        /**
         * Renders the highscores page.
         * @param {JsonDocument} highscores - A JSON document containing the highscores to render.
         */
        void renderHighscores(JsonDocument highscores);

        /**
         * Renders the end screen and determines whether to use gyroscope-based control.
         * @param {bool} useGyro - Whether to use the gyroscope for control.
         * @returns {bool} - Returns true if the end screen was rendered successfully, false otherwise.
         */
        bool renderEndScreen(bool useGyro);

    private:
        TFT_eSPI tft = TFT_eSPI();
        TFT_eSprite cursor = TFT_eSprite(&tft);
        TFT_eSprite background = TFT_eSprite(&tft);
        TFT_eSprite owl = TFT_eSprite(&tft);
        
        // UI Sprites
        TFT_eSprite countdownText = TFT_eSprite(&tft);
        //TFT_eSprite axisText = TFT_eSprite(&tft);
        TFT_eSprite scoreText = TFT_eSprite(&tft);
        TFT_eSprite bulletsText = TFT_eSprite(&tft);
        TFT_eSprite owlsText = TFT_eSprite(&tft);
        TFT_eSprite introText = TFT_eSprite(&tft);
    

        GameDataModel& g = GameDataModel::getInstance();
        /**
         * Checks for a collision between the cursor and the owl.
         * @param {int} cursorX - The X position of the cursor.
         * @param {int} cursorY - The Y position of the cursor.
         * @param {int} cursorHitBoxSize - The size of the cursor's hit box.
         * @param {int} owlX - The X position of the owl.
         * @param {int} owlY - The Y position of the owl.
         * @param {int} owlHitBoxSize - The size of the owl's hit box.
         * @returns {bool} - Returns true if there is a collision, false otherwise.
         */
        bool checkCollision(int cursorX, int cursorY, int cursorHitBoxSize, int owlX, int owlY, int owlHitBoxSize);

        /**
         * Updates the cursor's position based on gyro data or joystick input.
         * @param {int} x - The X position of the cursor.
         * @param {int} y - The Y position of the cursor.
         * @param {bool} useGyro - Whether to use gyro input for the cursor movement.
         */
        void updateCursorPosition(int& x, int& y, bool useGyro);

        /**
         * Handles the logic for firing the trigger.
         * @param {int} x - The X position of the cursor.
         * @param {int} y - The Y position of the cursor.
         */
        void handleTriggerFire(int& x, int& y);

        /**
         * Animates the owl's movement.
         */
        void animateOwl();

        /**
         * Moves the owl across the screen
         */
        void moveOwl();

        /**
         * Resets the owl's position and state.
         */
        void resetOwl();

        /**
         * Updates the UI elements such as score and owls remaining.
         * @param {int} x - The X position of the cursor.
         * @param {int} y - The Y position of the cursor.
         * @param {int} score - The current score to display.
         */
        void updateUI(int& x, int& y, int& score);

        /**
         * Updates a text sprite element with new content.
         * @param {TFT_eSprite} text - The text sprite to update.
         * @param {TextSpriteSettings} settings - The settings for the text sprite (e.g., position, font size).
         * @param {String} content - The new content to display in the text sprite.
         */
        void updateTextElement(TFT_eSprite &text, const TextSpriteSettings &settings, String content);

        /**
         * Creates the cursor sprite.
         */
        void createCursorSprite();

        /**
         * Renders the countdown screen before the game starts.
         */
        void renderCountdown();

        // Difficulty settings
        const int kMovementStepSizeEasy = 5;        
        const int kMovementStepSizeNormal = 8;
        const int kMovementStepSizeHard = 12;
        const int kOwlKillScoreEasy = 80;
        const int kOwlKillScoreNormal = 90;
        const int kOwlKillScoreHard = 100;
        const int kTotalBulletsEasy = 3;
        const int kTotalBulletsNormal = 2;
        const int kTotalBulletsHard = 1;

        // Highscore page settings
        const int kHighscoreTitleX = 85;
        const int kTitleY = 10;
        const int kTitleFontSize = 4;
        const int kNameX = 125;
        const int kInitialY = 50;
        const int kFontSize = 2;
        const int kYIncrement = 17;

        // Gameloop configs
        int score = 0;
        int totalOwls = 10;
        int owlsKilled = 0;
        int owlsMissed = 0;
        int x = SCREEN_WIDTH / 2 -  kCursorSpriteRatio / 2;
        int y = SCREEN_HEIGHT / 2 - kCursorSpriteRatio / 2;
        int totalBullets = kTotalBulletsEasy;
        int bullets = totalBullets;
        unsigned long startMovementTime;
        unsigned long startAnimationTime;
        unsigned long startCursorTime;
        unsigned long elapsedTime;

        // Cursor configs
        const int kCursorSpriteRatio = 40;      // 40x40
        const int kCursorColorDepth = 16;
        const int kCursorMovementDelay = 20;     // in millis
        const int kCursorHitBoxMargin = 10;     // in pixels

        // End Game screen configs
        const int kButtonBorderOffset = 20;
        const int kButtonWidth = (SCREEN_WIDTH / 2) - (kButtonBorderOffset * 2);
        const int kButtonHeight = SCREEN_HEIGHT - (kButtonBorderOffset * 2);
        const int kButtonTextOriginY = 110;
        const int kPlayButtonTextOriginX = 205;
        const int kEndButtonTextOriginX = 45;
        const int kButtonTextFontSize = 2;

        const int kPlayButtonOriginX = SCREEN_WIDTH / 2 + kButtonBorderOffset;
        const int kPlayButtonOriginY = kButtonBorderOffset;
        const int kEndButtonOriginX = kButtonBorderOffset;
        const int kEndButtonOriginY = kButtonBorderOffset;

        // Background configs
        int kBackgroundColorDepth = 8;

        // Owl configs
        const int kOwlColorDepth = 16;
        const int kOwlSpriteRatio = 64;    // 64x64
        int animationIndex = 0;
        int owlX = -64;
        int owlY = 100;
        bool owlAlive = true;
        const int kAnimationDelay = 150;   
        int movementStepSize = kMovementStepSizeEasy;   
        int kMovementDelay = 10;
        int owlKillScore = kOwlKillScoreEasy;
        


        unsigned long shootDelayStartTime; 
        const unsigned long kShootCooldownDuration = 1000; 
        const unsigned long dFlashInterval = 200; 
        bool shootOnCooldown = false;

        const int kTotalAnimationFrames = 4;
        const unsigned short* const kSpriteArray[4] PROGMEM = {
            kOwlNeutralSprite,
            kOwlUpSprite,
            kOwlNeutralSprite,
            kOwlDownSprite,
        };


        // Gameplay text
        const TextSpriteSettings kAxisTextSettings = {
            .width = 120,
            .height = 40,
            .fontSize = 2,
            .posX = 10,
            .posY = 10
        };

        const TextSpriteSettings kScoreTextSettings = {
            .width = 120,
            .height = 20,
            .fontSize = 2,
            .posX = 95,
            .posY = 207
        };

        const TextSpriteSettings kBulletsTextSettings = {
            .width = 60,
            .height = 20,
            .fontSize = 2,
            .posX = 28,
            .posY = 208
        };

        const TextSpriteSettings kOwlsTextSettings = {
            .width = 60,
            .height = 20,
            .fontSize = 2,
            .posX = 255,
            .posY = 208
        };

        // Intro text
        const TextSpriteSettings kIntroTextSettings = {
            .width = 200,
            .height = 20,
            .fontSize = 2,
            .posX = 80,
            .posY = 120
        };



};

#endif