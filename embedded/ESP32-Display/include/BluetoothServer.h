#ifndef BLUETOOTH_HANDLER_H
#define BLUETOOTH_HANDLER_H

#include "utilities.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>


class BluetoothServer {
    public:
        BluetoothServer();
        ~BluetoothServer();
        void Init();
        void Loop();
    private:
        // https://www.uuidgenerator.net/
        #define SERVICE_UUID        "b2f6ac88-8216-4faf-b31e-3f37926031be"
        #define CHARACTERISTIC_UUID "797bd60e-c9f7-4657-ac8f-aca7b9dd4b58"
        
        static bool deviceConnected;
        bool isAdvertising = false;
        BLEServer *pServer = NULL;
        BLECharacteristic *pCharacteristic = NULL;

        // Callback when a message is written to the BT server
        class WriteCallback : public BLECharacteristicCallbacks {
            void onWrite(BLECharacteristic *pCharacteristic) {
                std::string value = pCharacteristic->getValue();

                if (value.length() > 0) {
                    Serial.print("New value: ");
                    for (int i = 0; i < value.length(); i++) {
                        Serial.print(value[i]);
                    }
                    Serial.println();
                }
            }
        };  

        class ServerCallbacks : public BLEServerCallbacks {
            void onConnect(BLEServer *pServer) {
                deviceConnected = true;
                BLEDevice::startAdvertising();
            };

            void onDisconnect(BLEServer *pServer) {
                deviceConnected = false;
            }
        };
};

#endif