/*
 * Author: Melvin Moes
 * Date: November 6, 2024
 * Description: This class is an implementation of the connections.h which handles 
 * network communication tasks for the project. It provides methods for managing 
 * Wi-Fi connections using the `WiFiManager` library, creating and fetching player 
 * entities through an API, and handling ESP-NOW communication. The class includes 
 * functionality to initialize Wi-Fi, create player profiles, manage game sessions, 
 * and interact with a remote server for player data and scoring.
 * License: This project is licensed under the MIT License.
 */


#include "connections.h"


uint8_t Connections::broadcastAddress[] = {0x68, 0xB6, 0xB3, 0x2A, 0xB5, 0xCC};
IPAddress Connections::AP_LOCAL_IP(192, 168, 1, 1);
IPAddress Connections::AP_GATEWAY_IP(192, 168, 1, 254);
IPAddress Connections::AP_NETWORK_MASK(255, 255, 255, 0);
Connections* Connections::instance = nullptr;

Connections::Connections() {
    instance = this;
}

void Connections::init()
{
    Serial.println("------------[Wifi & Api]------------");
    getMacAddress();

    // Initialize wifi connection
    WiFi.mode(WIFI_AP_STA);
    wm.setDarkMode(true);
    // wm.resetSettings(); // To reset the saved wifi connections
    wm.autoConnect(kWifiManagerPortalName, kWifiManagerPortalPassword);


    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    
    // Registering callback for receiving messages    
    esp_now_register_recv_cb(OnDataRecv);


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
    } else { 
        Serial.println("**WiFi Connected**");
    }


    return res;
}

void Connections::loop()
{
    isConnected = connect();
    if(!isConnected) return;


    vTaskDelay(UDP_DELAY / portTICK_PERIOD_MS);
}

void Connections::onDataRecvCallback(const uint8_t * mac, const uint8_t *incomingData, int len) 
{
    char* buff = (char*) incomingData;
    String jsonData = String(buff);
    JsonDocument doc;

    DeserializationError error = deserializeJson(doc, jsonData);

    if(!error) {
        //serializeJsonPretty(doc, Serial);
    } else {
        Serial.printf("Error: %s\n", error.f_str());
        return;
    }

    String method = doc["method"].as<String>();
    if(method == CONTROLLER_AXIS_DATA_METHOD) {
        int gX = doc["data"]["gX"];
        int gY = doc["data"]["gY"];
        float jX = doc["data"]["jX"];
        float jY = doc["data"]["jY"];

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

void Connections::OnDataRecv(const uint8_t *macAddr, const uint8_t *data, int dataLen) 
{
    if (instance) {
        instance->onDataRecvCallback(macAddr, data, dataLen);
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
    } else if (method == "PATCH"){
        http.addHeader("Content-Type", "application/json");
        httpResponseCode = http.PATCH(payload);
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

void Connections::endSession(int id)
{
    JsonDocument doc;
    doc["completed"] = true;

    JsonDocument response = makeAPICall("PATCH", "session/" + String(id), &doc);


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
        //serializeJsonPretty(response, Serial);
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