/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: This header defines the MotionController class, which integrates the gyroscope, joystick, and UDP 
 * connection for managing a motion controller's inputs and communications. It initializes the components then  
 * runs a main control loop and handles defines a task for reading gyroscope data asynchronously.
 * License: This project is licensed under the MIT License.
 */

#ifndef MOTION_CONTROLLER_H
#define MOTION_CONTROLLER_H

#include "utilities.h"
#include "Gyroscope.h"
#include "UdpConnection.h"
#include "Joystick.h"

class MotionController {
    public:
        MotionController();
        ~MotionController();
        void Init();
        void Run();
    private:
        UdpConnection udpConnection;
        Gyroscope gyro;
        Joystick joystick;

        void SendTriggerInput();
        void SendJoystickClick();
        void SendControllerData();

        TaskHandle_t GyroTaskHandle = NULL;
        static void GyroTask(void *pvParameters)
        {
            Gyroscope* gyro = static_cast<Gyroscope*>(pvParameters);
            for (;;)
            {
                gyro->Loop();
                vTaskDelay(50 / portTICK_PERIOD_MS);
            }
        }
};


#endif