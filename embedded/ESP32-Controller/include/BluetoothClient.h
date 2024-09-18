#ifndef BLUETOOTH_CLIENT_H
#define BLUETOOTH_CLIENT_H

#include "BLEDevice.h"

class BluetoothClient
{
    public:
        BluetoothClient();
        ~BluetoothClient();

        void Init();
        void Loop();
        void SendMessage();
    private:
        
};

#endif