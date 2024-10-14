#include "UdpConnection.h"

UdpConnection::UdpConnection(Gyroscope *gyro, Joystick *joystick)
{
    this->gyro = gyro;
    this->joystick = joystick;
}

UdpConnection::~UdpConnection(){}

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

void UdpConnection::SendControllerData()
{
    // Get data from gyroscope
    GyroData gData = gyro->GetXYZ();
    JoystickData jData = joystick->GetAxis();

    // Create a JSON document
    JsonDocument jsonDoc;
    jsonDoc["method"] = "axisData";
    jsonDoc["data"]["gX"] = gData.x;
    jsonDoc["data"]["gY"] = gData.y;
    jsonDoc["data"]["jX"] = jData.x;
    jsonDoc["data"]["jY"] = jData.y;

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
    if(err == EHOSTUNREACH)
    {
        delay(1000);
        Serial.println("Host unreachable");
    } else if(err == ENOMEM)
    {
        Serial.println("Not enough memory");
    }
    

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

void UdpConnection::SendTriggerInput()
{
    // Create a JSON document
    JsonDocument jsonDoc;
    jsonDoc["method"] = "trigger";

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
    udp.endPacket();
}

void UdpConnection::SendJoystickClick()
{
    // Create a JSON document
    JsonDocument jsonDoc;
    jsonDoc["method"] = "joystickClick";

    Serial.print(F("Sending to "));
    Serial.print(udpAddress);
    Serial.print(F(" on port "));
    Serial.println(udpPort);
    serializeJson(jsonDoc, Serial);
    Serial.println();

    // Send the JSON string to the server
    udp.beginPacket(udpAddress, udpPort);
    serializeJson(jsonDoc, udp);
    udp.println();
    udp.endPacket();
}