/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: This header defines the UdpConnection class, which manages UDP communication for sending data 
 * from the gyroscope and joystick. It provides methods to initialize the connection, send joystick input, and 
 * transmit controller data over the network.
 * License: This project is licensed under the MIT License.
 */

#ifndef UDP_CONNECTION_H
#define UDP_CONNECTION_H

#include "utilities.h"
#include "Wifi.h"
#include "WiFiUdp.h"
#include "Gyroscope.h"
#include "Joystick.h"
#include <ArduinoJson.h>

class UdpConnection
{
    public:
        UdpConnection(Gyroscope *gyro, Joystick *joystick);
        ~UdpConnection();
        void SendTriggerInput();
        void SendJoystickClick();
        void Init();
        void SendControllerData();
    private:
        const char *udpAddress = "192.168.1.1";
        const int udpPort = 44444;
        const char *ssid = "HootPursuitConsoleAP";
        const char *password = "hootpursuitaccess";
        WiFiUDP udp;
        Gyroscope *gyro;
        Joystick *joystick;

};

#endif