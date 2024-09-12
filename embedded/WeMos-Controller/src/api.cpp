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
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    // String httpRequestData = "name=" + name;           
    // int httpResponseCode = http.POST(httpRequestData);
    int httpResponseCode = http.GET();
    Serial.println("HTTP Response code: " + String(httpResponseCode));

    // if(IsConnected()) {
    //     Serial.println("HELP ME PLS");
    // }
    // WiFiClient wifiClient;
    // HTTPClient http;

    // // Specify the correct endpoint, assuming it's /player for creating a player
    // http.begin(wifiClient, "http://TUNNEL-URL/api/player");

    // // Add header to specify we're sending form-encoded data
    // http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // // Format the data for the POST body
    // // String httpRequestData = "name=" + name;

    // // Send POST request
    // int httpResponseCode = http.GET();

    // // Print the response code
    // Serial.println("HTTP Response code: " + String(httpResponseCode));

    // // End the HTTP connection
    // http.end();
}