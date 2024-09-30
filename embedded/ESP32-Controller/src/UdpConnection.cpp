#include "UdpConnection.h"

void UdpConnection::Init()
{
    //Connect to the WiFi network
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.printf("\nConnected to: %s\n", ssid);
    Serial.printf("IP address: %s", WiFi.localIP().toString().c_str());
    
    //This initializes udp and transfer buffer
    udp.begin(udpPort);
}

void UdpConnection::ReceivePackets()
{
    //data will be sent to server
    uint8_t buffer[50] = "hello world";
    //send hello world to server
    udp.beginPacket(udpAddress, udpPort);
    udp.write(buffer, 12);
    udp.endPacket();
    memset(buffer, 0, 50);
    //processing incoming packet, must be called before reading the buffer
    udp.parsePacket();
    //receive response from server, it will be HELLO WORLD
    if(udp.read(buffer, 50) > 0){
        Serial.print("Server to client: ");
        Serial.println((char *)buffer);
    }
}