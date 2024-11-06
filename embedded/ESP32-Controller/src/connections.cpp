/*
 * Author: Melvin Moes
 * Date: November 6, 2024
 * Description: This file defines the `Connections` class for managing ESP-NOW communication 
 * between ESP32 devices. It includes methods for initializing the connection, 
 * sending data, and retrieving the device's MAC address.
 * License: This project is licensed under the MIT License.
 */

#include "connections.h"

// Mac address of the console
uint8_t Connections::broadcastAddress[] = {0x24, 0xDC, 0xC3, 0x4A, 0x5D, 0x00};

void Connections::init()
{
    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);
    esp_wifi_set_channel(kChannel, WIFI_SECOND_CHAN_NONE);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register CallBack to get the status of sent message.
    //esp_now_register_send_cb(OnDataSent);
    
    // Register peer
    memcpy(peerInfo.peer_addr, broadcastAddress, sizeof(broadcastAddress));
    peerInfo.channel = kChannel;  
    peerInfo.encrypt = false;
    
    // Add peer        
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("Failed to add peer");
        return;
    }
}

void Connections::sendData(JsonDocument data)
{
    // Serialize json to string
    String payload = "";
    serializeJson(data, payload);   
    // serializeJson(data, Serial);

    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) payload.c_str(), payload.length());
    
    if (result != ESP_OK) {
        Serial.println("Error sending the data");
    } else {
        //Serial.println("Sent with success");
    }
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