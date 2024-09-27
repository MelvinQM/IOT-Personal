#ifndef GAME_H
#define GAME_H

#include "utilities.h"
#include <TFT_eSPI.h>
#include "sprites/cursor.h"
#include "sprites/background.h"
#include "BluetoothServer.h"

class Game 
{
    public:
        void Init();
        void Loop();
    private:
        TFT_eSPI tft = TFT_eSPI();
        TFT_eSprite cursor = TFT_eSprite(&tft);
        TFT_eSprite background = TFT_eSprite(&tft);
        TFT_eSprite gyroText = TFT_eSprite(&tft);
        BluetoothServer bluetooth;
        float screenWidth = 320;
        float screenHeight = 240;
};

#endif