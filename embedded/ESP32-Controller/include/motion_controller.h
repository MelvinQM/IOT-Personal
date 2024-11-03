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
#include "gyroscope.h"
#include "udp_connection.h"
#include "joystick.h"

class MotionController {
    public:
        MotionController();
        ~MotionController();
        void init();
        void loop();
    private:
        UdpConnection udpConnection;
        Gyroscope gyro;
        Joystick joystick;

        void sendTriggerInput();
        void sendJoystickClick();
        void sendControllerData();
        void handleButtonPress();
        void handleJoystickClick();

        // Trigger configs
        unsigned long lastButtonPressTime = 0;
        bool isVibrating = false;
        bool previousButtonState = LOW;
        const unsigned long kButtonCooldown = 100;
        const unsigned long kVibrationDuration = 400;

        // Joystick click configs
        bool previousJoystickClickState = LOW;
        unsigned long lastJoystickClickTime = 0;
        const unsigned long kJoystickClickCooldown = 100;
        
        bool buttonPressPending = false;

        TaskHandle_t gyroTaskHandle = NULL;
        #define GYRO_TASK_STACK_SIZE    5000
        #define GYRO_TASK_PRIORITY      1
        #define GYRO_TASK_CORE          0
        #define GYRO_TASK_NAME          "GyroTask"
        static void gyroTask(void *pvParameters)
        {
            Gyroscope* gyro = static_cast<Gyroscope*>(pvParameters);
            for (;;)
            {
                gyro->loop();
                vTaskDelay(GYRO_DELAY / portTICK_PERIOD_MS);
            }
        }

        TaskHandle_t sendControllerDataTaskHandle = NULL;
        #define SEND_CONTROLLER_TASK_STACK_SIZE    5000
        #define SEND_CONTROLLER_TASK_PRIORITY      1
        #define SEND_CONTROLLER_TASK_CORE          1
        #define SEND_CONTROLLER_TASK_NAME          "ControllerDataTask"
        // New task function for sendControllerData
        static void sendControllerDataTask(void *pvParameters) {
            MotionController *controller = reinterpret_cast<MotionController *>(pvParameters);
            while (true) {
                controller->sendControllerData();
                vTaskDelay(CONTROLLER_DATA_SEND_INTERVAL / portTICK_PERIOD_MS);  // Set appropriate delay
            }
        }
};


#endif