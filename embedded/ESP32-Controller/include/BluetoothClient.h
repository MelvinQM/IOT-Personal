#ifndef BLUETOOTH_CLIENT_H
#define BLUETOOTH_CLIENT_H

#include <BLEDevice.h>
#include <ArduinoJson.h>
#include "utilities.h"
#include "Gyroscope.h"

class BluetoothClient
{
    public:
        BluetoothClient(Gyroscope *gyro);
        ~BluetoothClient();

        void Init();
        void Loop();
        String SendGyroData();
    private:
        Gyroscope *gyro;
        
};

#endif