#ifndef API_H
#define API_H

#include "utilities.h"
#include "WiFiManager.h"
#include "ESP8266HTTPClient.h"
#include "ESP8266WiFi.h"

class Api {
    public:
        Api();
        ~Api();
        void Init();
        bool IsConnected();
        void CreatePlayer(String name);
        void FetchPlayers();
    private:

};

#endif