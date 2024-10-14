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
        String hostName = "145.92.189.173";
        WiFiUDP udp;
        char packetBuffer[255];
        unsigned int localPort = 44444;
};

#endif