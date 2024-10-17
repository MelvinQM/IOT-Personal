/*
 * Author: Melvin Moes
 * Date: October 17, 2024
 * Description: 
 */

#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "utilities.h"
#include <TFT_eSPI.h>

#include "sprites/cursor.h"
#include "sprites/background.h"
#include "sprites/owl.h"

class SpriteRenderer {
    public:
        SpriteRenderer();
        ~SpriteRenderer();
        void InitializeDisplay(int rotation, bool swapBytes, int fillColor);
        void GameLoop(Difficulty diff, bool useGyro);

        void SetAxisData(GyroData *gData, JoystickData *jData);
    private:
        TFT_eSPI tft = TFT_eSPI();
        TFT_eSprite cursor = TFT_eSprite(&tft);
        TFT_eSprite background = TFT_eSprite(&tft);
        TFT_eSprite gyroText = TFT_eSprite(&tft);
        TFT_eSprite owl = TFT_eSprite(&tft);

        bool CheckCollision(int cursorX, int cursorY, int cursorHitBoxSize, int owlX, int owlY, int owlHitBoxSize);

        // Cursor configs
        int cursorSpriteRatio = 40;     // 40x40
        int cursorColorDepth = 16;
        int cursorMovementDelay = 10;   // in millis

        // Background configs
        int backgroundColorDepth = 8;

        // Axis Text configs
        int axisTextWidth = 240;
        int axisTextHeight = 40;

        // Owl configs
        int owlColorDepth = 16;
        int owlSpriteRatio = 64; // 64x64
        int animationIndex = 0;
        int owlX = -64;
        int owlY = 100;

        GyroData *gData;
        JoystickData *jData;

        int animationDelay = 250;   // in milis
        int movementDelay = 10;     // in milis
        int movementStepSize = 5;   // in pixels

        const unsigned short* const spriteArray[4] PROGMEM = {
            owlNeutralSprite,
            owlUpSprite,
            owlNeutralSprite,
            owlDownSprite,
        };

};

#endif