#include "api.h"
#include "ESP8266HTTPClient.h"
#include "ESP8266WiFi.h"
#include "ping.h"

Api::Api() 
{

}

Api::~Api()
{

}

void Api::Init()
{
    Serial.println("----[Wifi & Api]----");
    WiFi.mode(WIFI_STA);
    WiFiManager wm;

    //wm.resetSettings(); // To reset the saved wifi connections

    // Password protected ap
    bool res = wm.autoConnect("DuckHuntAP","password"); 

    if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else { 
        Serial.println("**WiFi Connected**");
    }
}

bool Api::IsConnected() 
{
    return WiFi.status() == WL_CONNECTED;
}

void Api::CreatePlayer(String name)
{
    WiFiClient wifiClient;
    HTTPClient http;

    http.begin(wifiClient, "http://moesmq.loca.lt/api/player");
    // http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    // String httpRequestData = "name=" + name;           
    // int httpResponseCode = http.POST(httpRequestData);
    int httpResponseCode = http.GET();
    Serial.println("HTTP Response code: " + String(httpResponseCode));
    
    if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("Response: " + response);
    } else {
        Serial.println("Error on sending POST request");
    }

    http.end();
}