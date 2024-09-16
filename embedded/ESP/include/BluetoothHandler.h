#ifndef BLUETOOTH_HANDLER_H
#define BLUETOOTH_HANDLER_H

#include "utilities.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>


class BluetoothHandler {
    public:
        BluetoothHandler();
        ~BluetoothHandler();
        void Init();
        void Loop();
    private:
        // See the following for generating UUIDs:
        // https://www.uuidgenerator.net/
        #define SERVICE_UUID        "b2f6ac88-8216-4faf-b31e-3f37926031be"
        #define CHARACTERISTIC_UUID "797bd60e-c9f7-4657-ac8f-aca7b9dd4b58"

        // Callback when a message is written to the BT server
        class MyCallbacks : public BLECharacteristicCallbacks {
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
};

#endif