/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: This header defines the UdpConnection class, which manages UDP communication for sending data 
 * from the gyroscope and joystick. It provides methods to initialize the connection, An option is also present to construct 
 * JSON documents containing relevant data and send them over the UDP connection. 
 * License: This project is licensed under the MIT License.
 */

#ifndef UDP_CONNECTION_H
#define UDP_CONNECTION_H

#include "utilities.h"
#include "Wifi.h"
#include "WiFiUdp.h"

class UdpConnection
{
    public:
        UdpConnection();
        ~UdpConnection();
        void Init();
        void SendJsonData(JsonDocument doc);
    private:
        const char *udpAddress = "192.168.1.1";
        const int udpPort = 44444;
        const char *ssid = "HootPursuitConsoleAP";
        const char *password = "hootpursuitaccess";
        WiFiUDP udp;

};

#endif