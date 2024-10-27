/*
 * Author: Melvin Moes
 * Date: October 18, 2024
 * Description: This header file defines the Connections class, which manages 
 * network connections for the project. It includes functionalities for initializing 
 * Wi-Fi connections, creating player entities through an API connection, and handling UDP communications. 
 * The class utilizes the WiFiManager library for easy Wi-Fi management and ArduinoJson 
 * for parsing JSON data. It also contains methods for fetching player data and 
 * listening for UDP packets.
 * License: This project is licensed under the MIT License.
 */

#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include "utilities.h"
#include "WiFiManager.h"
#include <WiFi.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "game_data_model.h"

class Connections {
    public:
        void init();
        void loop();
        void udpListen();
        bool connect();
        bool getConnection();

        void createPlayer(String name);
        void fetchPlayers();
        int createSession();
        JsonDocument getSessionById(int id);
        void updateSession(GameSettings &settings);
        void createScore(int sessionId, int score);
        void setListenForPackets(bool listen);
    private:
        JsonDocument makeAPICall(String method, String endpoint, JsonDocument* jsonDoc = nullptr);
        void getMacAddress();

        WiFiManager wm;
        WiFiUDP udp;
        GameDataModel& g = GameDataModel::getInstance();

        const char* kWifiManagerPortalName = "HootPursuitAP";
        const char* kWifiManagerPortalPassword = "password";
        const char* kSoftApHostname = "HootPursuitHost";
        // const String kHostName = "192.168.0.239";
        const String kHostName = "145.92.189.173";
        const char *kSSID = "HootPursuitConsoleAP";
        const char *kPassword = "hootpursuitaccess";
        char packetBuffer[255];
        unsigned int kLocalPort = 44444;
        bool isConnected = false;
        bool listenForPackets = false;
};

#endif