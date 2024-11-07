/*
 * Author: Melvin Moes
 * Date: November 6, 2024
 * Description: This header file defines the Connections class, which manages 
 * network connections for the project. It includes functionalities for initializing 
 * Wi-Fi connections, creating player entities through an API connection, and handling ESP-NOW communications. 
 * The class utilizes the WiFiManager library for easy Wi-Fi management and ArduinoJson 
 * for parsing JSON data.
 * License: This project is licensed under the MIT License.
 */

#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include "utilities.h"
#include "WiFiManager.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include "game_data_model.h"
#include <esp_now.h>

class Connections {
    public:
        /**
         * Constructor for the connections class assigning the instance of the class to the instance variable.
         */
        Connections();

        /**
         * Initializes the Connections class and sets up network configurations for use of ESP-NOW and an API conneciton.
         */
        void init();

        /**
         * Main loop function to periodically check if the connection is still valid.
         */
        void loop();

        /**
         * Connects to the configured Wi-Fi network.
         * @return true if connection is successful, false otherwise.
         */
        bool connect();

        /**
         * Checks if the device is currently connected to Wi-Fi.
         * @return true if connected, false otherwise.
         */
        bool getConnection();

        /**
         * Creates a player entity on the server using the provided name.
         * @param name The name of the player to create.
         */
        void createPlayer(String name);

        /**
         * Fetches a list of players from the server.
         */
        void fetchPlayers();

        /**
         * Creates a new game session on the server.
         * @return The ID of the created session.
         */
        int createSession();

        /**
         * Fetches the high scores from the server.
         * @return A JSON document containing the high scores.
         */
        JsonDocument getHighscores();

        /**
         * Retrieves session details by session ID.
         * @param id The ID of the session to retrieve.
         * @return A JSON document containing the session data.
         */
        JsonDocument getSessionById(int id);

        /**
         * Ends a game session with the specified ID.
         * @param id The ID of the session to end.
         */
        void endSession(int id);

        /**
         * Creates a score entry on the server for a given session and score.
         * @param sessionId The ID of the session.
         * @param score The score to record.
         */
        void createScore(int sessionId, int score);

        /**
         * Callback function for ESP-NOW data reception.
         * @param macAddr The MAC address of the sender.
         * @param data The data received.
         * @param dataLen The length of the data received.
         */
        void onDataRecvCallback(const uint8_t *macAddr, const uint8_t *data, int dataLen);

    private:
        static IPAddress AP_LOCAL_IP;
        static IPAddress AP_GATEWAY_IP;
        static IPAddress AP_NETWORK_MASK;
        static uint8_t broadcastAddress[6];

        const char* kWifiManagerPortalName = "HootPursuitAP";
        const char* kWifiManagerPortalPassword = "password";
        // const String kHostName = "192.168.0.8";
        static Connections* instance;
        const String kHostName = "145.92.189.173";

        WiFiManager wm;
        GameDataModel& g = GameDataModel::getInstance();
        bool isConnected = false;

        /**
         * ESP-NOW data receive callback.
         * @param macAddr MAC address of the sender.
         * @param data Data received.
         * @param dataLen Length of data received.
         */
        static void OnDataRecv(const uint8_t *macAddr, const uint8_t *data, int dataLen);

        /**
         * Makes an API call to the specified endpoint.
         * @param method HTTP method (e.g., GET, POST).
         * @param endpoint The API endpoint (ex: /api/player).
         * @param jsonDoc (Optional) JSON document for the request body.
         * @return A JSON document containing the server response.
         */
        JsonDocument makeAPICall(String method, String endpoint, JsonDocument* jsonDoc = nullptr);

        /**
         * Retrieves the MAC address of the device.
         */
        void getMacAddress();
};

#endif