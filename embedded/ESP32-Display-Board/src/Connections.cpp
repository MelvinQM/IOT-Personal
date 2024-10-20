/*
 * Author: Melvin Moes
 * Date: October 18, 2024
 * Description: This source file implements the Connections class, which manages Wi-Fi connections and UDP 
 * communication for the game application. The class provides methods for initializing a Wi-Fi connection for communicating with a remote API
 * and setting up a soft access point for handling UDP packet reception. It includes functionality for creating players and fetching player data 
 * via HTTP requests.
 * License: This project is licensed under the MIT License.
 */


#include "Connections.h"

Connections::Connections() {}
Connections::~Connections() {}

// Manual IP Configuration for Soft AP
IPAddress AP_LOCAL_IP(192, 168, 1, 1);
IPAddress AP_GATEWAY_IP(192, 168, 1, 254);
IPAddress AP_NETWORK_MASK(255, 255, 255, 0);

void Connections::Init()
{
    Serial.println("------------[Wifi & Api]------------");
    GetMacAddress();
    WiFi.mode(WIFI_AP_STA);
    wm.setDarkMode(true);
    // wm.resetSettings(); // To reset the saved wifi connections
    wm.autoConnect("HootPursuitAP", "password");

    // Enable SoftAP
    //WiFi.mode(WIFI_AP_STA);  // Enable both AP and STA modes simultaneously
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
    vTaskDelay(UDP_DELAY / portTICK_PERIOD_MS);
}

void Connections::UdpListen()
{
    int packetSize = udp.parsePacket();

    // If no packet is received, avoid printing or spamming output
    // if (packetSize <= 0) {
    //     vTaskDelay(TIMEOUT_DELAY / portTICK_PERIOD_MS);
    //     return;      
    // }

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
            
        String method = jsonDoc["method"].as<String>();
        if(method == CONTROLLER_AXIS_DATA_METHOD) {
            int gX = jsonDoc["data"]["gX"];
            int gY = jsonDoc["data"]["gY"];
            float jX = jsonDoc["data"]["jX"];
            float jY = jsonDoc["data"]["jY"];
            g.SetGyroData({gX, gY});
            g.SetJoystickData({jX, jY});
            //Serial.printf("From UDP: jX: %f jY: %f\n",jX ,jY );
            //Serial.printf("From Model: jX: %f jY: %f\n",g.GetJoystickX() ,g.GetJoystickY());

        } else if(method == TRIGGER_METHOD) {
            Serial.println("Trigger pressed");
            g.SetTriggerPressed(true);
        } else if(method == JOYSTICK_CLICK_METHOD) {
            Serial.println("Joystick clicked");
            g.SetJoystickClicked(true);
        } else {    
            Serial.println("Error: Method not recognized!");
        }
    } else {
        //Serial.print(".");
    }
}

JsonDocument Connections::MakeAPICall(String method, String endpoint, JsonDocument* jsonDoc)
{
    WiFiClient wifiClient;
    HTTPClient http;
    JsonDocument jsonResponse;
    wifiClient.setTimeout(WIFI_TIMEOUT);

    String url = "http://" + hostName + "/api/" + endpoint;
    Serial.println("API Call to: " + url);
    http.begin(wifiClient, url);

    int httpResponseCode = -1;
    
    // If a JsonDocument is provided, serialize it to a string
    String payload;
    if (jsonDoc != nullptr) {
        serializeJson(*jsonDoc, payload);
    }

    if (method == "GET") {
        httpResponseCode = http.GET();
    } else if (method == "POST") {
        http.addHeader("Content-Type", "application/json");
        httpResponseCode = http.POST(payload);
    } else {
        Serial.println("Unsupported HTTP method: " + method);
        http.end();
        return JsonDocument(0);
    }

    Serial.println("HTTP Response code: " + String(httpResponseCode));
    
    if (httpResponseCode > 0) {
        
        String response = http.getString();
        Serial.println("Response: " + response);
        
        DeserializationError error = deserializeJson(jsonResponse, response);
        
        if (error) {
            Serial.print("Failed to parse JSON: ");
            Serial.println(error.f_str());
            return JsonDocument(0);
        }
    } else {
        Serial.println("Error on sending " + method + " request");
    }

    http.end();

    return jsonResponse;
}

void Connections::CreatePlayer(String name)
{
    WiFiClient wifiClient;
    HTTPClient http;
    wifiClient.setTimeout(WIFI_TIMEOUT);

    String url = "http://"+ hostName +"/api/player";
    Serial.println("API Call to: " + url);
    http.begin(wifiClient, url);
    http.addHeader("Content-Type", "application/json");
    
    JsonDocument doc;
    //String httpRequestData = "{\"name\":\"" + name + "\"}";
    doc["name"] = name;  // Adds the "name" key with the value of the 'name' variable
    String httpRequestData;
    serializeJson(doc, httpRequestData);  // Converts JSON object to a string


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
    wifiClient.setTimeout(WIFI_TIMEOUT);

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
