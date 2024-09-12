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
    WiFi.mode(WIFI_STA);
    WiFiManager wm;
    wm.setDarkMode(true);

    // wm.resetSettings(); // To reset the saved wifi connections

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
    wifiClient.setTimeout(10000);

    String url = "http://"+ hostName +"/api/player";
    Serial.println("API Call to: " + url);
    http.begin(wifiClient, url);
    http.addHeader("Content-Type", "application/json");

    String httpRequestData = "{\"name\":\"" + name + "\"}";

    // Send the HTTP POST request with the JSON data
    int httpResponseCode = http.POST(httpRequestData);
    Serial.println("HTTP Response code: " + String(httpResponseCode));
    
    if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("Response: " + response);
    } else {
        Serial.println("Error on sending POST request");
    }

    http.end();
}

void Api::FetchPlayers()
{
    WiFiClient wifiClient;
    HTTPClient http;
    wifiClient.setTimeout(10000);

    String url = "http://"+ hostName +"/api/player";
    Serial.println("API Call to: " + url);
    http.begin(wifiClient, url);
    int httpResponseCode = http.GET();
    Serial.println("HTTP Response code: " + String(httpResponseCode));
    
    if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("Response: " + response);
    } else {
        Serial.println("Error on sending GET request");
    }

    http.end();
}
