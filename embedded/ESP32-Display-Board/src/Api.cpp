#include "Api.h"

Api::Api() {}
Api::~Api() {}
const char *ssid = "DuckHuntConsoleAP";
const char *password = "duckhuntaccess";

// Manual IP Configuration for Soft AP
IPAddress AP_LOCAL_IP(192, 168, 1, 1);
IPAddress AP_GATEWAY_IP(192, 168, 1, 254);
IPAddress AP_NETWORK_MASK(255, 255, 255, 0);
void Api::Init()
{
    Serial.println("------------[Wifi & Api]------------");
    GetMacAddress();
    WiFi.mode(WIFI_STA);
    wm.setDarkMode(true);
    // wm.resetSettings(); // To reset the saved wifi connections
    
    // Enable SoftAP
    WiFi.softAPConfig(AP_LOCAL_IP, AP_GATEWAY_IP, AP_NETWORK_MASK);
    WiFi.softAPsetHostname("DuckHuntHost");

    // To initiate the Soft AP, pause the program if the initialization process encounters an error.
    if (!WiFi.softAP(ssid, password))
    {
        Serial.println("Soft AP creation failed.");
        while (1);
    }

    udp.begin(localPort);
    Serial.printf("UDP server : %s:%i \n", WiFi.localIP().toString().c_str(), localPort);

    Connect();
}


bool Api::Connect()
{
    if(WiFi.status() == WL_CONNECTED) return true;

    // Password protected ap
    bool res = wm.autoConnect("DuckHuntAP","password"); 

    if(!res) {
        Serial.println("Failed to connect");        
        // ESP.restart();
    } else { 
        Serial.println("**WiFi Connected**");
    }

    return res;
}

void Api::Loop()
{
    if(!Connect()) return;

    int packetSize = udp.parsePacket();
    Serial.print(" Received packet from : "); Serial.println(udp.remoteIP());
    Serial.print(" Size : "); Serial.println(packetSize);
    if (packetSize) {
        int len = udp.read(packetBuffer, 255);
        if (len > 0) packetBuffer[len - 1] = 0;
        Serial.printf("Data : %s\n", packetBuffer);
        udp.beginPacket(udp.remoteIP(), udp.remotePort());
        udp.printf("UDP packet was received OK\r\n");
        udp.endPacket();
    }
    Serial.println("\n");
    delay(500);
    Serial.print("[Server Connected] ");
    Serial.println (WiFi.localIP());
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
        Serial.println("Response: " + http.getString());
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
}
