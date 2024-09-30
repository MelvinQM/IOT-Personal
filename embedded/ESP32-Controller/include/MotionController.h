#ifndef MOTION_CONTROLLER_H
#define MOTION_CONTROLLER_H

#include "utilities.h"
#include "Gyroscope.h"

#include "Wifi.h"
#include "WiFiUdp.h"

class MotionController {
    public:
        MotionController();
        ~MotionController();
        void Init();
        void Run();
    private:
        Gyroscope gyro;
        const char *ssid = "DuckHuntConsoleAP";
        const char *password = "duckhuntaccess";

};


#endif