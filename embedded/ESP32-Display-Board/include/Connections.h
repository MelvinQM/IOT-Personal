/*
 * Author: Melvin Moes
 * Date: October 14, 2024
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

class Connections {
    public:
        Connections();
        ~Connections();
        void Init();
        bool IsConnected();
        void CreatePlayer(String name);
        void UdpListen();
        void FetchPlayers();
        bool Connect();
        void Loop();
        GyroData gyroData = {0, 0};
        JoystickData joystickData {0, 0};
    private:
        void GetMacAddress();
        WiFiManager wm;
        WiFiUDP udp;
        
        String hostName = "145.92.189.173";
        const char *ssid = "HootPursuitConsoleAP";
        const char *password = "hootpursuitaccess";
        char packetBuffer[255];
        unsigned int localPort = 44444;
};

#endif