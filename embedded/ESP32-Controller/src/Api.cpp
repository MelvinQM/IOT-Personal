#include "Api.h"

Api::Api() {}
Api::~Api() {}

void Api::Init()
{
    Serial.println("------------[Wifi & Api]------------");
    GetMacAddress();
    WiFi.mode(WIFI_STA);
    WiFiManager wm;
    wm.setDarkMode(true);

    // wm.resetSettings(); // To reset the saved wifi connections

    // Password protected ap
    bool res = wm.autoConnect("DuckHuntAP","password"); 

    if(!res) {
        Serial.println("Failed to connect");        // ESP.restart();

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

void Api::GetMacAddress()
{
    // Variable to store the MAC address
    uint8_t baseMac[6];
    
    // Get MAC address of the WiFi station interface
    esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
    Serial.print("Station MAC: ");
    for (int i = 0; i < 5; i++) {
        Serial.printf("%02X:", baseMac[i]);
    }
    Serial.printf("%02X\n", baseMac[5]);
    
    // Get the MAC address of the Wi-Fi AP interface
    esp_read_mac(baseMac, ESP_MAC_WIFI_SOFTAP);
    Serial.print("SoftAP MAC: ");
    for (int i = 0; i < 5; i++) {
        Serial.printf("%02X:", baseMac[i]);
    }
    Serial.printf("%02X\n", baseMac[5]);
    
    // Get the MAC address of the Bluetooth interface
    esp_read_mac(baseMac, ESP_MAC_BT);
    Serial.print("Bluetooth MAC: ");
    for (int i = 0; i < 5; i++) {
        Serial.printf("%02X:", baseMac[i]);
    }
    Serial.printf("%02X\n", baseMac[5]);

    // Get the MAC address of the Ethernet interface
    esp_read_mac(baseMac, ESP_MAC_ETH);
    Serial.print("Ethernet MAC: ");
    for (int i = 0; i < 5; i++) {
        Serial.printf("%02X:", baseMac[i]);
    }
    Serial.printf("%02X\n", baseMac[5]);
}
