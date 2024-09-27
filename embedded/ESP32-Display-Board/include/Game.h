#ifndef GAME_H
#define GAME_H

#include "utilities.h"
#include <TFT_eSPI.h>
#include "sprites/cursor.h"
#include "sprites/background.h"

class Game 
{
    public:
        void Init();
        void Loop();
    private:
        float screenWidth = 320;
        float screenHeigth = 240;
};

#endif