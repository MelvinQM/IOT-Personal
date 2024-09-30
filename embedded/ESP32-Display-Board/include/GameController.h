#ifndef GAME_H
#define GAME_H

#include "utilities.h"
#include <TFT_eSPI.h>
#include "sprites/cursor.h"
#include "sprites/background.h"
#include "BluetoothServer.h"
#include "Api.h"

class GameController 
{
    public:
        GameController();
        ~GameController();
        void Init();
        void Loop();
    private:
        BluetoothServer btServer;
        Api api;

        TFT_eSPI tft = TFT_eSPI();
        TFT_eSprite cursor = TFT_eSprite(&tft);
        TFT_eSprite background = TFT_eSprite(&tft);
        TFT_eSprite gyroText = TFT_eSprite(&tft);
        float screenWidth = 320;
        float screenHeight = 240;
        
        TaskHandle_t BluetoothTaskHandle = NULL;
        static void BluetoothTask(void *pvParameters)
        {
            BluetoothServer* btServer = static_cast<BluetoothServer*>(pvParameters);
            // btServer->Init();
            for (;;)
            {
                btServer->Loop();
                // Check the amount of stack remaining (high watermark)
                // UBaseType_t stackHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
                // Serial.print("Stack high water mark (Bluetooth): ");
                // Serial.println(stackHighWaterMark);
                vTaskDelay(1000 / portTICK_PERIOD_MS);
            }
        }
        TaskHandle_t WiFiTaskHandle = NULL;
        static void WiFiTask(void *pvParameters)
        {
            Api* api = static_cast<Api*>(pvParameters);
            pinMode(BUTTON_PIN, INPUT); // Test button
            // api->Init();
            for (;;)
            {
                api->Connect();
                if (digitalRead(BUTTON_PIN))
                {
                    Serial.println("Button pressed");
                    api->CreatePlayer("Lucas");
                    api->FetchPlayers();
                }

                // Check the amount of stack remaining (high watermark)
                // UBaseType_t stackHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
                // Serial.print("Stack high water mark (API): ");
                // Serial.println(stackHighWaterMark);
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