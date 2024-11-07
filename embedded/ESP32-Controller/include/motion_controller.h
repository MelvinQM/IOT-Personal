/*
 * Author: Melvin Moes
 * Date: November 6, 2024
 * Description: This header defines the MotionController class, which integrates the gyroscope, joystick, and ESP-NOW 
 * connection for managing a motion controller's inputs and communications. It initializes the components then  
 * runs a main control loop and handles defines a task for reading gyroscope data asynchronously.
 * License: This project is licensed under the MIT License.
 */

#ifndef MOTION_CONTROLLER_H
#define MOTION_CONTROLLER_H

#include "utilities.h"
#include "gyroscope.h"
#include "joystick.h"
#include "connections.h"

class MotionController {
    public:
        /**
         * Constructor for the MotionController class.
         * Initializes the Serial monitor.
         */
        MotionController();

        /**
         * Initializes the motion controller's components, including the gyroscope, joystick, and ESP-NOW connection.
         * Sets up tasks for gyroscope reading and controller axis data sending.
         */
        void init();

        /**
         * Main control loop for the MotionController.
         * Continuously read for Button and Joystick click presses.
         */
        void loop();
    private:
        Connections conn;
        Gyroscope gyro;
        Joystick joystick;

        /**
         * Sends trigger input data via ESP-NOW.
         * This method is called when the trigger is pressed, sending the input status.
         */
        void sendTriggerInput();

        /**
         * Sends joystick click data via ESP-NOW.
         * Called when the joystick click is detected, this method sends the click state.
         */
        void sendJoystickClick();

        /**
         * Sends combined controller data, including gyroscope and joystick values, via ESP-NOW.
         */
        void sendControllerData();

        /**
         * Handles button press events and manages cooldown and vibration states.
         * This method ensures that button presses are processed with appropriate delays.
         */
        void handleButtonPress();

        /**
         * Handles joystick click events and manages cooldown.
         * Ensures that repeated clicks are managed with a cooldown period.
         */
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
        /**
         * Task function for reading gyroscope data asynchronously.
         * Continuously calls the gyroscope's loop method with a delay, allowing for asynchronous updates.
         *
         * @param {void*} pvParameters - Pointer to gyroscope instance passed to the task.
         */
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
        /**
         * Task function for sending controller data asynchronously.
         * Continuously sends controller data at a specified interval.
         *
         * @param {void*} pvParameters - Pointer to MotionController instance passed to the task.
         */
        static void sendControllerDataTask(void *pvParameters) {
            MotionController *controller = reinterpret_cast<MotionController *>(pvParameters);
            while (true) {
                controller->sendControllerData();
                vTaskDelay(CONTROLLER_DATA_SEND_INTERVAL / portTICK_PERIOD_MS);  // Set appropriate delay
            }
        }
};


#endif