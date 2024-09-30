#ifndef UDP_CONNECTION_H
#define UDP_CONNECTION_H

#include "utilities.h"
#include "Wifi.h"
#include "WiFiUdp.h"

class UdpConnection
{
    public:
        void ReceivePackets();
        void Init();
    private:
        const char *udpAddress = "192.168.1.1";
        const int udpPort = 44444;
        const char *ssid = "DuckHuntConsoleAP";
        const char *password = "duckhuntaccess";
        WiFiUDP udp;

};

#endif