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