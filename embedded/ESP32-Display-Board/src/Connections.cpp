/*
 * Author: Melvin Moes
 * Date: October 18, 2024
 * Description: This source file implements the Connections class, which manages Wi-Fi connections and UDP 
 * communication for the game application. The class provides methods for initializing a Wi-Fi connection for communicating with a remote API
 * and setting up a soft access point for handling UDP packet reception. It includes functionality for creating players and fetching player data 
 * via HTTP requests.
 * License: This project is licensed under the MIT License.
 */


#include "connections.h"

// Manual IP Configuration for Soft AP
IPAddress AP_LOCAL_IP(192, 168, 1, 1);
IPAddress AP_GATEWAY_IP(192, 168, 1, 254);
IPAddress AP_NETWORK_MASK(255, 255, 255, 0);

void Connections::init()
{
    Serial.println("------------[Wifi & Api]------------");
    getMacAddress();

    // Initialize wifi connection
    WiFi.mode(WIFI_AP_STA);
    wm.setDarkMode(true);
    // wm.resetSettings(); // To reset the saved wifi connections
    wm.autoConnect(kWifiManagerPortalName, kWifiManagerPortalPassword);

    // Enable SoftAP
    WiFi.softAPConfig(AP_LOCAL_IP, AP_GATEWAY_IP, AP_NETWORK_MASK);
    WiFi.softAPsetHostname(kSoftApHostname);
    if (!WiFi.softAP(kSSID, kPassword))
    {
        Serial.println("Soft AP creation failed.");
        while(1);
    }

    udp.begin(kLocalPort);
    Serial.printf("UDP server : %s:%i \n", WiFi.localIP().toString().c_str(), kLocalPort);

    isConnected = true;
}

bool Connections::getConnection()
{
    return isConnected;
}

bool Connections::connect()
{
    if(WiFi.status() == WL_CONNECTED) return true;

    bool res = wm.autoConnect("HootPursuitAP","password"); 
    if(!res) {
        Serial.println("Failed to connect");        
        // ESP.restart();
    } else { 
        Serial.println("**WiFi Connected**");
    }


    return res;
}

void Connections::loop()
{
    isConnected = connect();
    if(!isConnected) return;

    udpListen();
    vTaskDelay(UDP_DELAY / portTICK_PERIOD_MS);
}

void Connections::setListenForPackets(bool listen)
{
    listenForPackets = listen;
}

void Connections::udpListen()
{
    if(!listenForPackets) return;

    int packetSize = udp.parsePacket();

    if (packetSize) {
        int len = udp.read(packetBuffer, 255);
        if (len > 0) packetBuffer[len - 1] = 0;
        
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
            g.setGyroData({gX, gY});
            g.setJoystickData({jX, jY});
            //Serial.printf("From UDP: jX: %f jY: %f\n",jX ,jY );
            //Serial.printf("From Model: jX: %f jY: %f\n",g.GetJoystickX() ,g.GetJoystickY());

        } else if(method == TRIGGER_METHOD) {
            Serial.println("Trigger pressed");
            g.setTriggerPressed(true);
        } else if(method == JOYSTICK_CLICK_METHOD) {
            Serial.println("Joystick clicked");
            g.setJoystickClicked(true);
        } else {    
            Serial.println("Error: Method not recognized!");
        }
    }
}

JsonDocument Connections::makeAPICall(String method, String endpoint, JsonDocument* jsonDoc)
{
    WiFiClient wifiClient;
    HTTPClient http;
    JsonDocument jsonResponse;
    wifiClient.setTimeout(WIFI_TIMEOUT);

    String url = "http://" + kHostName + "/api/" + endpoint;
    Serial.println("API Call to: " + url);
    http.begin(wifiClient, url);

    int httpResponseCode = -1;
    
    String payload;
    if (jsonDoc != nullptr) {
        serializeJson(*jsonDoc, payload);
    } else {
        payload = "{}";
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


void Connections::createPlayer(String name)
{
    JsonDocument doc;
    doc["name"] = name;

    JsonDocument response = makeAPICall("POST", "player", &doc);

    if (!response.isNull()) {
        Serial.println("CreatePlayer: Player created successfully.");
        //serializeJsonPretty(response, Serial); 
    } else {
        Serial.println("CreatePlayer: Failed to create player.");
    }
}

void Connections::fetchPlayers()
{
    JsonDocument response = makeAPICall("GET", "player");

    if (!response.isNull()) {
        Serial.println("FetchPlayers: Fetched players");
        //serializeJsonPretty(response, Serial);
    } else {
        Serial.println("FetchPlayers: Failed to fetch players");
    }
}

int Connections::createSession()
{
    JsonDocument res = makeAPICall("POST", "session");
    String message = res["message"];
    int sessionId = res["id"];
    Serial.println("Create session: " + message);

    return sessionId;
}

JsonDocument Connections::getSessionById(int id)
{
    JsonDocument response = makeAPICall("GET", "session/" + String(id));

    if (!response.isNull()) {
        Serial.println("Session retrieved");
        //serializeJsonPretty(response, Serial);
        return response;
    } else {
        Serial.println("Failed to get session by id.");
        return JsonDocument(0);
    }

    
}

void Connections::updateSession(GameSettings &settings)
{
    JsonDocument doc;
    if(settings.completed) doc["completed"] = true;
    if(settings.startTime) doc["start_time"] = settings.startTime;
    if(settings.endTime) doc["end_time"] = settings.endTime;

    JsonDocument response = makeAPICall("PATCH", "session/" + String(settings.sessionId), &doc);

    // Check for the response
    if (!response.isNull()) {
        Serial.println("UpdateSession: ");
        serializeJsonPretty(response, Serial);
    } else {
        Serial.println("UpdateSession: Failed to update session.");
    }

}

void Connections::createScore(int sessionId, int score)
{
    JsonDocument doc;
    doc["session_id"] = sessionId;
    doc["score"] = score;

    JsonDocument response = makeAPICall("POST", "score", &doc);

    if (!response.isNull()) {
        Serial.println("CreateScore: ");
        serializeJsonPretty(response, Serial);
    } else {
        Serial.println("CreateScore: Failed to create score.");
    }
}

JsonDocument Connections::getHighscores() {
    JsonDocument doc = makeAPICall("GET", "actions/gethighscores?count=" + String(HIGHSCORE_AMOUNT));
    return doc;
}

void Connections::getMacAddress()
{
    // Get MAC address of the WiFi station interface
    uint8_t baseMac[6];
    esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
    
    Serial.print("Station MAC: ");
    for (int i = 0; i < 5; i++) {
        Serial.printf("%02X:", baseMac[i]);
    }
    Serial.printf("%02X\n", baseMac[5]);
}
