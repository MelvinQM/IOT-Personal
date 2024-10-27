/*
 * Author: Melvin Moes
 * Date: October 18, 2024
 * Description: An implementation of the UdpConnection header. It manages the 
 * connection to a WiFi access point and allows the sending of controller data, trigger inputs, and joystick 
 * click events to a specified UDP server. The Init function establishes the WiFi connection and initializes 
 * the UDP protocol. An option is also present to construct JSON documents containing relevant data and send them over the UDP connection. 
 * License: This project is licensed under the MIT License.
 */

#include "udp_connection.h"


void UdpConnection::init()
{
    //Connect to the WiFi network
    WiFi.begin(kSSID, kPassword);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        vTaskDelay(TIMEOUT_DELAY / portTICK_PERIOD_MS);
        Serial.print(".");
    }
    Serial.printf("\nConnected to: %s\n", kSSID);
    Serial.printf("IP address: %s", WiFi.localIP().toString().c_str());
    
    //This initializes udp and transfer buffer
    udp.begin(kUDPPort);
}

void UdpConnection::sendJsonData(JsonDocument jsonDoc, bool response, bool retry)
{
    // Clear previous UDP buffer
    udp.flush();
    
    // Send the JSON string to the server
    int attempts = retry ? 2 : 1;
    bool sendSuccess = false;
    for (int i = 0; i < attempts && !sendSuccess; i++) {
        udp.beginPacket(kUDPAddress, kUDPPort);
        serializeJson(jsonDoc, udp);
        udp.println();
        sendSuccess = udp.endPacket() > 0;
    }

    if (response && udp.parsePacket()) {
        char buffer[50] = {0};
        int len = udp.read(buffer, sizeof(buffer) - 1);
        if (len > 0) {
            buffer[len] = '\0';
            Serial.print("Server to client: ");
            Serial.println(buffer);
        }
    }
    
}