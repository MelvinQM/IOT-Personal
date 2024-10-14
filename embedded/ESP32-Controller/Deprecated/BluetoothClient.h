/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: This header defines the BluetoothClient class, which handles BLE communication between a gyroscope 
 * and a remote BLE server. It provides methods to initialize the BLE connection, manage the communication loop and send gyroscope data in JSON format.
 * License: This project is licensed under the MIT License.
 */

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