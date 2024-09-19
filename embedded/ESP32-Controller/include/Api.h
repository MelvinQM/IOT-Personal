#ifndef API_H
#define API_H

#include "utilities.h"
#include "WiFiManager.h"
// #include "ESP8266HTTPClient.h"
// #include "ESP8266WiFi.h"
#include <WiFi.h>
#include <HTTPClient.h>

class Api {
    public:
        Api();
        ~Api();
        void Init();
        bool IsConnected();
        void CreatePlayer(String name);
        void FetchPlayers();
        void Connect();
    private:
        void GetMacAddress();
        WiFiManager wm;
        String hostName = "145.92.189.173";
};

#endif