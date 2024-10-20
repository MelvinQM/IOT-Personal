/*
 * Author: Melvin Moes
 * Date: October 18, 2024
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
        void HandleButtonPress();
        void HandleJoystickClick();

        // Trigger configs
        unsigned long lastButtonPressTime = 0;
        bool isVibrating = false;
        bool previousButtonState = LOW;
        unsigned long buttonCooldown = 100;
        unsigned long vibrationDuration = 200;

        // Joystick click configs
        bool previousJoystickClickState = LOW;
        unsigned long lastJoystickClickTime = 0;
        unsigned long joystickClickCooldown = 100;
        
        TaskHandle_t GyroTaskHandle = NULL;
        #define GYRO_TASK_STACK_SIZE    5000
        #define GYRO_TASK_PRIORITY      1
        #define GYRO_TASK_CORE          0
        #define GYRO_TASK_NAME          "GyroTask"
        static void GyroTask(void *pvParameters)
        {
            Gyroscope* gyro = static_cast<Gyroscope*>(pvParameters);
            for (;;)
            {
                gyro->Loop();
                vTaskDelay(GYRO_DELAY / portTICK_PERIOD_MS);
            }
        }
};


#endif