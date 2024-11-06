/*
 * Author: Melvin Moes
 * Date: November 6, 2024
 * Description: This header file defines the `Connections` class for managing ESP-NOW communication 
 * on the ESP32 platform. The class includes methods for initializing ESP-NOW, sending 
 * data, and retrieving the device's MAC address. It also includes a callback function 
 * for handling the status of sent data packets.
 * License: This project is licensed under the MIT License.
 */

#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include "utilities.h"
#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

class Connections {
    public:
        void init();
        void sendData(JsonDocument data);
        void getMacAddress();
    private:
        static uint8_t broadcastAddress[6];
        esp_now_peer_info_t peerInfo;

        const int kChannel = 11;

        // Callback when data is sent
        static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
            Serial.print("\r\nLast Packet Send Status:\t");
            Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
        }

};
#endif