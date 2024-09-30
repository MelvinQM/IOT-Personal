#ifndef MOTION_CONTROLLER_H
#define MOTION_CONTROLLER_H

#include "utilities.h"
#include "Gyroscope.h"
#include "BluetoothClient.h"

class MotionController {
    public:
        MotionController();
        ~MotionController();
        void Init();
        void Run();
    private:
        Gyroscope gyro;
        BluetoothClient btClient;

        TaskHandle_t BluetoothTaskHandle = NULL;
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
};


#endif