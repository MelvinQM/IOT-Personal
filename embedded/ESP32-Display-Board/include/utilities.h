/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: This header defines various utility constants, pin assignments, and data structures used in the project. 
 * It also includes definitions for a button pin and data structures for joystick and gyro data.
 * License: This project is licensed under the MIT License.
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#include <Arduino.h>
#include <ArduinoJson.h>

// General settings
#define BAUD_RATE           115200
#define TIMEOUT_DELAY       1000
#define BIG_TIMEOUT_DELAY   5000
#define HIGHSCORE_KEEPALIVE 10000


// Display settings and configurations
#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   240
#define SCREEN_ORIGIN_X 0
#define SCREEN_ORIGIN_Y 0
#define SCREEN_ROTATION 1   // Landscape

// Game settings
#define CURSOR_SPEED    10
#define USE_GYRO        false
#define EXTRA_SCORE_MAX 50
#define EXTRA_SCORE_DIVISION_FACTOR (SCREEN_WIDTH / EXTRA_SCORE_MAX)

// Pin definitions
#define BUTTON_PIN  22
#define LED_PIN_R       4
#define LED_PIN_G       16
#define LED_PIN_B       17
#define LED_R_CHANNEL 0
#define LED_G_CHANNEL 1
#define LED_B_CHANNEL 2
#define LED_DEFAULT_BRIGHTNESS 0.1

// Wifi settings
#define WIFI_TIMEOUT    10000
#define UDP_DELAY       10
#define HIGHSCORE_AMOUNT 10

// Defining the JSON method names
#define TRIGGER_METHOD              "trigger"
#define JOYSTICK_CLICK_METHOD       "joystickClick"
#define CONTROLLER_AXIS_DATA_METHOD "axisData"

enum Difficulty {
    EASY = 1,
    NORMAL = 2,
    HARD = 3
};

struct GameSettings {
    unsigned int sessionId;
    unsigned int playerId;
    Difficulty difficultyId;
    unsigned int score;
    unsigned long startTime;
    unsigned long endTime;
    boolean useGyro;
    boolean completed;
};

#endif