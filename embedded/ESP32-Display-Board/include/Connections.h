/*
 * Author: Melvin Moes
 * Date: November 6, 2024
 * Description: This header file defines the Connections class, which manages 
 * network connections for the project. It includes functionalities for initializing 
 * Wi-Fi connections, creating player entities through an API connection, and handling ESP-NOW communications. 
 * The class utilizes the WiFiManager library for easy Wi-Fi management and ArduinoJson 
 * for parsing JSON data.
 * License: This project is licensed under the MIT License.
 */

#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include "utilities.h"
#include "WiFiManager.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include "game_data_model.h"
#include <esp_now.h>

class Connections {
    public:
        Connections();

        void init();
        void loop();
        bool connect();
        bool getConnection();

        void createPlayer(String name);
        void fetchPlayers();
        int createSession();

        JsonDocument getHighscores();
        JsonDocument getSessionById(int id);
        void endSession(int id);
        void createScore(int sessionId, int score);
        void onDataRecvCallback(const uint8_t *macAddr, const uint8_t *data, int dataLen);
    private:
        static IPAddress AP_LOCAL_IP;
        static IPAddress AP_GATEWAY_IP;
        static IPAddress AP_NETWORK_MASK;
        static uint8_t broadcastAddress[6];

        const char* kWifiManagerPortalName = "HootPursuitAP";
        const char* kWifiManagerPortalPassword = "password";
        const String kHostName = "192.168.0.8";
        static Connections* instance;
        // const String kHostName = "145.92.189.173";

        WiFiManager wm;
        GameDataModel& g = GameDataModel::getInstance();
        bool isConnected = false;

        static void OnDataRecv(const uint8_t *macAddr, const uint8_t *data, int dataLen);
        JsonDocument makeAPICall(String method, String endpoint, JsonDocument* jsonDoc = nullptr);
        void getMacAddress();
};

#endif