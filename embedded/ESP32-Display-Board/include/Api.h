#ifndef API_H
#define API_H

#include "utilities.h"
#include "WiFiManager.h"
#include <WiFi.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>

class Api {
    public:
        Api();
        ~Api();
        void Init();
        bool IsConnected();
        void CreatePlayer(String name);
        void FetchPlayers();
        bool Connect();
        void Loop();
    private:
        void GetMacAddress();
        WiFiManager wm;
        String hostName = "145.92.189.173";
        WiFiUDP udp;
        char packetBuffer[255];
        unsigned int localPort = 44444;
};

#endif