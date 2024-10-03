#ifndef MOTION_CONTROLLER_H
#define MOTION_CONTROLLER_H

#include "utilities.h"
#include "Gyroscope.h"
#include "UdpConnection.h"

class MotionController {
    public:
        MotionController();
        ~MotionController();
        void Init();
        void Run();
    private:
        UdpConnection udpConnection;
        Gyroscope gyro;
        TaskHandle_t GyroTaskHandle = NULL;
        static void GyroTask(void *pvParameters)
        {
            Gyroscope* gyro = static_cast<Gyroscope*>(pvParameters);
            for (;;)
            {
                gyro->Loop();
                vTaskDelay(200 / portTICK_PERIOD_MS);
            }
        }
};


#endif