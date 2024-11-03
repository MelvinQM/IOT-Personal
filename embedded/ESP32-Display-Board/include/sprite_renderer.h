/*
 * Author: Melvin Moes
 * Date: October 18, 2024
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
        struct TextSpriteSettings {
            int width;
            int height;
            int fontSize;
            int posX;
            int posY;
        };

    public:
        void init(int rotation, bool swapBytes, int fillColor);
        void gameLoop(GameSettings &settings);
        void renderIntro(int sessionId);
        void renderHighscores(JsonDocument highscores);
        bool renderEndScreen();

    private:
        TFT_eSPI tft = TFT_eSPI();
        TFT_eSprite cursor = TFT_eSprite(&tft);
        TFT_eSprite background = TFT_eSprite(&tft);
        TFT_eSprite owl = TFT_eSprite(&tft);
        
        // UI Sprites
        TFT_eSprite axisText = TFT_eSprite(&tft);
        TFT_eSprite scoreText = TFT_eSprite(&tft);
        TFT_eSprite bulletsText = TFT_eSprite(&tft);
        TFT_eSprite owlsText = TFT_eSprite(&tft);
        TFT_eSprite introText = TFT_eSprite(&tft);
    
        

        GameDataModel& g = GameDataModel::getInstance();

        // Game Logic
        bool checkCollision(int cursorX, int cursorY, int cursorHitBoxSize, int owlX, int owlY, int owlHitBoxSize);
        void updateCursorPosition(int& x, int& y, bool useGyro);
        void handleTriggerFire(int& x, int& y);
        void animateOwl();
        void moveOwl();
        void resetOwl();
        void updateUI(int& x, int& y, int& score);
        void updateTextElement(TFT_eSprite &text, const TextSpriteSettings &settings, String content);

        // Game Settings
        const int kTotalBulletsEasy = 3;
        const int kTotalBulletsNormal = 2;
        const int kTotalBulletsHard = 1;
        const int owlKillScoreEasy = 80;
        const int owlKillScoreNormal = 90;
        const int owlKillScoreHard = 100;

        // Game Loop Configs
        int score = 0;
        int totalOwls = 10;
        int owlsKilled = 0;
        int owlsMissed = 0;
        int x = SCREEN_WIDTH / 2 - kCursorSpriteRatio / 2;
        int y = SCREEN_HEIGHT / 2 - kCursorSpriteRatio / 2;
        int totalBullets = kTotalBulletsEasy;
        int bullets = totalBullets;

        unsigned long startMovementTime;
        unsigned long startAnimationTime;
        unsigned long startCursorTime;
        unsigned long elapsedTime;

        // Cursor Configs
        const int kCursorSpriteRatio = 40;  // 40x40
        const int kCursorColorDepth = 16;
        const int kCursorMovementDelay = 1; // in millis
        const int kCursorHitBoxMargin = 10; // in pixels

        // Background Configs
        int kBackgroundColorDepth = 8;

        // Owl Configs
        const int kOwlColorDepth = 16;
        const int kOwlSpriteRatio = 64; // 64x64
        int animationIndex = 0;
        int owlX = -64;
        int owlY = 100;
        bool owlAlive = true;
        const int kAnimationDelay = 150;   
        const int kMovementStepSizeEasy = 5;        
        const int kMovementStepSizeNormal = 8;
        const int kMovementStepSizeHard = 12;
        int movementStepSize = kMovementStepSizeEasy;   
        int kMovementDelay = 10;
        int owlKillScore = owlKillScoreEasy;

        unsigned long shootDelayStartTime; 
        const unsigned long kShootCooldownDuration = 1000; 
        const unsigned long dFlashInterval = 200; 
        bool shootOnCooldown = false;

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