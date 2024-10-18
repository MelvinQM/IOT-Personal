/*
 * Author: Melvin Moes
 * Date: October 18, 2024
 * Description: An implementation of the UdpConnection header. It manages the 
 * connection to a WiFi access point and allows the sending of controller data, trigger inputs, and joystick 
 * click events to a specified UDP server. The Init function establishes the WiFi connection and initializes 
 * the UDP protocol. An option is also present to construct JSON documents containing relevant data and send them over the UDP connection. 
 * License: This project is licensed under the MIT License.
 */

#include "UdpConnection.h"

UdpConnection::UdpConnection() {}

UdpConnection::~UdpConnection() {}

void UdpConnection::Init()
{
    //Connect to the WiFi network
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        vTaskDelay(TIMEOUT_DELAY / portTICK_PERIOD_MS);
        Serial.print(".");
    }
    Serial.printf("\nConnected to: %s\n", ssid);
    Serial.printf("IP address: %s", WiFi.localIP().toString().c_str());
    
    //This initializes udp and transfer buffer
    udp.begin(udpPort);
}

void UdpConnection::SendJsonData(JsonDocument jsonDoc)
{
    // For debugging purposes
    // Serial.print(F("Sending to "));
    // Serial.print(udpAddress);
    // Serial.print(F(" on port "));
    // Serial.println(udpPort);
    // serializeJson(jsonDoc, Serial);
    // Serial.println();

    // Send the JSON string to the server
    udp.beginPacket(udpAddress, udpPort);
    serializeJson(jsonDoc, udp);
    udp.println();
    int err = udp.endPacket();
    if(err == EHOSTUNREACH) {
        vTaskDelay(TIMEOUT_DELAY / portTICK_PERIOD_MS);
        Serial.println("Host unreachable");
    } else if(err == ENOMEM) {
        Serial.println("Not enough memory");
    }


    // Incase the response needs to viewed
    // // Initialize a buffer to receive the server's response
    // uint8_t buffer[50] = {0};

    // // Clear buffer
    // memset(buffer, 0, 50);

    // // Processing incoming packet, must be called before reading the buffer
    // udp.parsePacket();

    // // Receive response from the server, it will be HELLO WORLD
    // if (udp.read(buffer, 50) > 0) {
    //     Serial.print("Server to client: ");
    //     Serial.println((char*)buffer);
    // }
}