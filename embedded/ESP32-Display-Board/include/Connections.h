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
#include "GameDataModel.h"

class Connections {
    public:
        void Init();
        void Loop();
        void UdpListen();
        bool Connect();
        bool GetConnection();

        void CreatePlayer(String name);
        void FetchPlayers();
        int CreateSession();
        JsonDocument GetSessionById(int id);
        void UpdateSession(GameSettings &settings);
        void CreateScore(int sessionId, int score);
    private:
        JsonDocument MakeAPICall(String method, String endpoint, JsonDocument* jsonDoc = nullptr);
        void GetMacAddress();
        WiFiManager wm;
        WiFiUDP udp;
        GameDataModel& g = GameDataModel::getInstance();
        bool isConnected = false;
        // String hostName = "192.168.0.239";
        String hostName = "145.92.189.173";
        const char *ssid = "HootPursuitConsoleAP";
        const char *password = "hootpursuitaccess";
        char packetBuffer[255];
        unsigned int localPort = 44444;
};

#endif