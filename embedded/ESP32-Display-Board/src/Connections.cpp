#include "Connections.h"

Connections::Connections() {}
Connections::~Connections() {}
const char *ssid = "HootPursuitConsoleAP";
const char *password = "hootpursuitaccess";

// Manual IP Configuration for Soft AP
IPAddress AP_LOCAL_IP(192, 168, 1, 1);
IPAddress AP_GATEWAY_IP(192, 168, 1, 254);
IPAddress AP_NETWORK_MASK(255, 255, 255, 0);
void Connections::Init()
{
    Serial.println("------------[Wifi & Api]------------");
    GetMacAddress();
    WiFi.mode(WIFI_STA);
    wm.setDarkMode(true);
    // wm.resetSettings(); // To reset the saved wifi connections
    wm.autoConnect("HootPursuitAP", "password");

    // Enable SoftAP
    WiFi.mode(WIFI_AP_STA);  // Enable both AP and STA modes simultaneously
    WiFi.softAPConfig(AP_LOCAL_IP, AP_GATEWAY_IP, AP_NETWORK_MASK);
    WiFi.softAPsetHostname("HootPursuitHost");

    // To initiate the Soft AP, pause the program if the initialization process encounters an error.
    if (!WiFi.softAP(ssid, password))
    {
        Serial.println("Soft AP creation failed.");
        while(1);
    }

    udp.begin(localPort);
    Serial.printf("UDP server : %s:%i \n", WiFi.localIP().toString().c_str(), localPort);


    Connect();
}


bool Connections::Connect()
{
    if(WiFi.status() == WL_CONNECTED) return true;

    // Password protected ap
    bool res = wm.autoConnect("HootPursuitAP","password"); 

    if(!res) {
        Serial.println("Failed to connect");        
        // ESP.restart();
    } else { 
        Serial.println("**WiFi Connected**");
    }


    return res;
}

void Connections::Loop()
{
    if(!Connect()) return;
    UdpListen();
    delay(10);
}

void Connections::UdpListen()
{
    int packetSize = udp.parsePacket();

    // If no packet is received, avoid printing or spamming output
    if (packetSize <= 0) {
        delay(1000);  
        return;      
    }

    if (packetSize) {
        // Serial.printf("\nReceived packet from : %s\n", udp.remoteIP().toString());
        // Serial.printf("Size : %d", packetSize);
        // Serial.printf("[Server Connected]: %s", AP_LOCAL_IP.toString().c_str());
        int len = udp.read(packetBuffer, 255);
        if (len > 0) packetBuffer[len - 1] = 0;
        // udp.beginPacket(udp.remoteIP(), udp.remotePort());
        // udp.printf("UDP packet was received OK\r\n");
        // udp.endPacket();
        // Serial.println("\n");
        
        JsonDocument jsonDoc;
        DeserializationError error = deserializeJson(jsonDoc, packetBuffer);

        // Test if parsing succeeds.
        if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            return;
        }
        // serializeJson(jsonDoc, Serial);
        // Serial.println();
        String method = jsonDoc["method"].as<String>();
        if(method == "axisData") {
            // Serial.println("\nAxis Data received");
            gyroData.x = jsonDoc["data"]["gX"];
            gyroData.y = jsonDoc["data"]["gY"];
            joystickData.x = jsonDoc["data"]["jX"];
            joystickData.y = jsonDoc["data"]["jY"];
            Serial.printf("gX: %d gY: %d", gyroData.x, gyroData.y);
            Serial.printf(" | jX: %.1f jY: %.1f\n", joystickData.x, joystickData.y);
        } else if(method == "trigger") {
            Serial.println("Trigger pressed");
        } else if(method == "joystickClick") {
            Serial.println("Joystick clicked");
        } else {    
            Serial.println("Error: Method not recognized!");
        }
    } else {
        Serial.print(".");
    }
}

void Connections::CreatePlayer(String name)
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

void Connections::FetchPlayers()
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

void Connections::GetMacAddress()
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
