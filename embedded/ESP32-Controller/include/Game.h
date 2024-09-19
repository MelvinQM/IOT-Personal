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
            BluetoothClient* btClient = static_cast<BluetoothClient*>(pvParameters);
            btClient->Init();
            for (;;)
            {
                btClient->Loop();
                vTaskDelay(1000 / portTICK_PERIOD_MS);
            }
        }

        static void WiFiTask(void *pvParameters)
        {
            Api* api = static_cast<Api*>(pvParameters);
            pinMode(BUTTON_PIN, INPUT); // Test button
            api->Init();
            for (;;)
            {
                api->Connect();
                if (digitalRead(BUTTON_PIN))
                {
                    Serial.println("Button pressed");
                    api->CreatePlayer("Lucas");
                    api->FetchPlayers();
                }
                vTaskDelay(1000 / portTICK_PERIOD_MS);
            }
        }
};


#endif