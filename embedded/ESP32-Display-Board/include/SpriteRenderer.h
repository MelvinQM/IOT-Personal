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

#include "GameDataModel.h"

class SpriteRenderer {
    public:
        SpriteRenderer();
        ~SpriteRenderer();
        void InitializeDisplay(int rotation, bool swapBytes, int fillColor);
        void GameLoop(Difficulty diff, bool useGyro);
        void ShowIntro();
        void ShowHighscores();

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
        

        GameDataModel& g = GameDataModel::getInstance();
        bool CheckCollision(int cursorX, int cursorY, int cursorHitBoxSize, int owlX, int owlY, int owlHitBoxSize);
        void UpdateCursorPosition(int& x, int& y, bool useGyro);
        void HandleCursorCollision(int& x, int& y);
        void AnimateOwl();
        void MoveOwl();
        void ResetOwl();
        void UpdateUI(int& x, int& y, int& score);

        // Gameloop configs
        int score = 0;
        int totalOwls = 10;
        int owlsKilled = 0;
        int owlsMissed = 0;
        int x = SCREEN_WIDTH / 2 -  cursorSpriteRatio / 2;
        int y = SCREEN_HEIGHT / 2 - cursorSpriteRatio / 2;
        int bullets = 3;

        // Cursor configs
        int cursorSpriteRatio = 40;     // 40x40
        int cursorColorDepth = 16;
        int cursorMovementDelay = 1;   // in millis

        // Background configs
        int backgroundColorDepth = 8;

        // UI configs
        int axisTextWidth = 120;
        int axisTextHeight = 40;
        int axisTextFontSize = 2;
        int axisPosX = 10;
        int axisPosY = 10;

        int scoreTextWidth = 120;
        int scoreTextHeight = 20;
        int scoreTextFontSize = 2;
        int scorePosX = 95;
        int scorePosY = 207;

        int bulletsTextWidth = 60;
        int bulletsTextHeight = 20;
        int bulletsTextFontSize = 2;
        int bulletsTextPosX = 28;
        int bulletsTextPosY = 208;

        int owlsTextWidth = 60;
        int owlsTextHeight = 20;
        int owlsTextFontSize = 2;
        int owlsTextPosX = 255;
        int owlsTextPosY = 208;

        // Owl configs
        int owlColorDepth = 16;
        int owlSpriteRatio = 64; // 64x64
        int animationIndex = 0;
        int owlX = -64;
        int owlY = 100;
        bool owlAlive = true;
        int animationDelay = 150;   // in milis
        int movementDelay = 10;     // in milis
        int movementStepSize = 5;   // in pixels

        unsigned long startMovementTime;
        unsigned long startAnimationTime;
        unsigned long startCursorTime;
        unsigned long elapsedTime;

        const unsigned short* const spriteArray[4] PROGMEM = {
            owlNeutralSprite,
            owlUpSprite,
            owlNeutralSprite,
            owlDownSprite,
        };

};

#endif