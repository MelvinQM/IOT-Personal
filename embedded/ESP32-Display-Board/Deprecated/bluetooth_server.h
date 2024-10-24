/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: This header file defines the BluetoothServer class, which implements a Bluetooth Low Energy (BLE)
 * server. The header defines methods for the initialization of the BLE server, advertising, and
 * connection management with Bluetooth clients. It defines characteristics and provides 
 * a callback mechanism for handling incoming data written to the server. The gyro data is extracted from
 * incoming JSON messages, allowing for communication between the server and connected devices. 
 * License: This project is licensed under the MIT License.
 */

#ifndef BLUETOOTH_HANDLER_H
#define BLUETOOTH_HANDLER_H

#include "utilities.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <ArduinoJson.h>


class BluetoothServer {
    public:
        void init();
        void loop();
        GyroData gyroData = {0, 0};
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
            private:
                BluetoothServer *server;
            public:
                WriteCallback(BluetoothServer *server)
                {
                    this->server = server;
                };

            private:
                void onWrite(BLECharacteristic *pCharacteristic) {
                    std::string value = pCharacteristic->getValue();

                    if (value.length() > 0) {
                        Serial.print("New value: ");
                        for (int i = 0; i < value.length(); i++) {
                            Serial.print(value[i]);
                        }
                        Serial.println();
                    }

                    // Deserialize the JSON data
                    JsonDocument doc;
                    DeserializationError error = deserializeJson(doc, value);

                    if (error) {
                        Serial.print("Failed to parse JSON: ");
                        Serial.println(error.c_str());
                        return;
                    }
                    
                    server->gyroData = {doc["x"], doc["y"]};
            }
        };  

        class ServerCallbacks : public BLEServerCallbacks {
            void onConnect(BLEServer *pServer) {
                Serial.println("BLE: Device connected");
                deviceConnected = true;
            };

            void onDisconnect(BLEServer *pServer) {
                Serial.println("BLE: Device disconnected");
                deviceConnected = false;
            }
        };
};

#endif