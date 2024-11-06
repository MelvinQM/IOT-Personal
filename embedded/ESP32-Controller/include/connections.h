/*
 * Author: Melvin Moes
 * Date: November 5, 2024
 * Description: 
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
        
        typedef struct struct_message {
            char a[32];
            int b;
            float c;
            bool d;
        } struct_message;

        // Create a struct_message called myData
        struct_message myData;
        static uint8_t broadcastAddress[6];
        esp_now_peer_info_t peerInfo;

        // callback when data is sent
        static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
            Serial.print("\r\nLast Packet Send Status:\t");
            Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
        }

};
#endif