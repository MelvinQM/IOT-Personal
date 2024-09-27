#ifndef GAME_H
#define GAME_H

#include "utilities.h"
#include <TFT_eSPI.h>
#include "sprites/cursor.h"
#include "sprites/background.h"
#include "BluetoothServer.h"

class GameController 
{
    public:
        GameController();
        ~GameController();
        void Init();
        void Loop();
    private:
        TFT_eSPI tft = TFT_eSPI();
        TFT_eSprite cursor = TFT_eSprite(&tft);
        TFT_eSprite background = TFT_eSprite(&tft);
        TFT_eSprite gyroText = TFT_eSprite(&tft);
        BluetoothServer btServer;
        float screenWidth = 320;
        float screenHeight = 240;


        TaskHandle_t BluetoothTaskHandle = NULL;
        static void BluetoothTask(void *pvParameters)
        {
            BluetoothServer* btServer = static_cast<BluetoothServer*>(pvParameters);
            btServer->Init();
            for (;;)
            {
                btServer->Loop();
                vTaskDelay(1000 / portTICK_PERIOD_MS);
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