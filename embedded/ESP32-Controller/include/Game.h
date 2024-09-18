#ifndef GAME_H
#define GAME_H

#include "utilities.h"
#include "Gyroscope.h"
#include "Api.h"
#include "BluetoothClient.h"

class Game {
    public:
        Game();
        ~Game();
        void Init();
        void Run();
    private:
        Gyroscope gyro;
        Api api;
        BluetoothClient btClient;

        TaskHandle_t BluetoothTaskHandle = NULL;
        TaskHandle_t WiFiTaskHandle = NULL;

        static void BluetoothTask(void *pvParameters)
        {
            Game* game = static_cast<Game*>(pvParameters);
            for (;;)
            {
                game->btClient.Loop();
                vTaskDelay(10 / portTICK_PERIOD_MS);
            }
        }

        static void WiFiTask(void *pvParameters)
        {
            Game* game = static_cast<Game*>(pvParameters);
            for (;;)
            {
                if (digitalRead(BUTTON_PIN))
                {
                    Serial.println("Button pressed");
                    game->api.CreatePlayer("Lucas");
                    game->api.FetchPlayers();
                }
                vTaskDelay(1000 / portTICK_PERIOD_MS);
            }
        }
};


#endif