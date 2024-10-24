
/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: An implementation of the BluetoothServer header using the BLE. It initializes the BLE 
 * device, creates a service and characteristic for communication, and handles connections from 
 * Bluetooth clients. The server can send and receive data, allowing interaction with connected devices. 
 * It also manages advertising to make the device discoverable to potential clients. The Loop function 
 * monitors the connection state and notifies connected devices of any updates.
 * License: This project is licensed under the MIT License.
 */

#include "bluetooth_server.h"

BluetoothServer::BluetoothServer(){};
BluetoothServer::~BluetoothServer(){};

bool BluetoothServer::deviceConnected = false;
void BluetoothServer::Init()
{
    Serial.println("Starting BLE work!");

    BLEDevice::init("ESP32-S3 Bluetooth server");
    pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Allow read and write
    pCharacteristic = pService->createCharacteristic(
                                  CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ | 
                                  BLECharacteristic::PROPERTY_WRITE
                              );

    pCharacteristic->setCallbacks(new WriteCallback(this));    
    pServer->setCallbacks(new ServerCallbacks());

    pCharacteristic->setValue("Hello World");
    pService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);

    // Functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x06);  
    pAdvertising->setMinPreferred(0x12);
    
    BLEDevice::startAdvertising();


    Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void BluetoothServer::Loop() {
  if (deviceConnected) {
    pCharacteristic->notify();
    isAdvertising = false;
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
  
  if(!isAdvertising && !deviceConnected){
    pServer->startAdvertising();
    Serial.println("Device disconnected - Start advertising");
    isAdvertising = true;
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}