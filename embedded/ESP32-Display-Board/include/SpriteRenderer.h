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
    private:
        struct TextSpriteSettings {
            int width;
            int height;
            int fontSize;
            int posX;
            int posY;
        };

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

        TFT_eSprite introText = TFT_eSprite(&tft);
        

        GameDataModel& g = GameDataModel::getInstance();
        bool CheckCollision(int cursorX, int cursorY, int cursorHitBoxSize, int owlX, int owlY, int owlHitBoxSize);
        void UpdateCursorPosition(int& x, int& y, bool useGyro);
        void HandleCursorCollision(int& x, int& y);
        void AnimateOwl();
        void MoveOwl();
        void ResetOwl();
        void UpdateUI(int& x, int& y, int& score);
        void UpdateTextElement(TFT_eSprite &text, TextSpriteSettings &settings, String content);

        // Gameloop configs
        int score = 0;
        int totalOwls = 10;
        int owlsKilled = 0;
        int owlsMissed = 0;
        int x = SCREEN_WIDTH / 2 -  cursorSpriteRatio / 2;
        int y = SCREEN_HEIGHT / 2 - cursorSpriteRatio / 2;
        int bullets = 3;
        unsigned long startMovementTime;
        unsigned long startAnimationTime;
        unsigned long startCursorTime;
        unsigned long elapsedTime;

        // Cursor configs
        int cursorSpriteRatio = 40;     // 40x40
        int cursorColorDepth = 16;
        int cursorMovementDelay = 1;   // in millis

        // Background configs
        int backgroundColorDepth = 8;

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

        const unsigned short* const spriteArray[4] PROGMEM = {
            owlNeutralSprite,
            owlUpSprite,
            owlNeutralSprite,
            owlDownSprite,
        };


        // Gameplay text
        TextSpriteSettings axisTextSettings = {
            .width = 120,
            .height = 40,
            .fontSize = 2,
            .posX = 10,
            .posY = 10
        };

        TextSpriteSettings scoreTextSettings = {
            .width = 120,
            .height = 20,
            .fontSize = 2,
            .posX = 95,
            .posY = 207
        };

        TextSpriteSettings bulletsTextSettings = {
            .width = 60,
            .height = 20,
            .fontSize = 2,
            .posX = 28,
            .posY = 208
        };

        TextSpriteSettings owlsTextSettings = {
            .width = 60,
            .height = 20,
            .fontSize = 2,
            .posX = 255,
            .posY = 208
        };

        // Intro text
        TextSpriteSettings introTextSettings = {
            .width = 200,
            .height = 20,
            .fontSize = 2,
            .posX = 80,
            .posY = 120
        };

};

#endif