#include "api.h"

Api::Api() 
{

}

Api::~Api()
{

}

void Api::Init()
{
    Serial.println("----[Wifi & Api]----");
    // Serial.print("MAC-address of your WeMoS: ");
    // Serial.println(WiFi.macAddress());
    WiFi.mode(WIFI_STA);
    WiFiManager wm;

    // Resets settings (Should be commented for production)
    //wm.resetSettings();

    // Password protected ap
    bool res = wm.autoConnect("DuckHuntAP","password"); 

    if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
    }
}

bool Api::IsConnected() 
{
    return false;
}