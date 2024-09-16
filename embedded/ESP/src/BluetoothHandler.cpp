
#include "BluetoothHandler.h"


BluetoothHandler::BluetoothHandler(){};
BluetoothHandler::~BluetoothHandler(){};

void BluetoothHandler::Init()
{
    Serial.println("Starting BLE work!");

    BLEDevice::init("ESP32-S3 Bluetooth server");
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Allow read and write
    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                            CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ | 
                                            BLECharacteristic::PROPERTY_WRITE
                                        );

    pCharacteristic->setCallbacks(new MyCallbacks());    

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

void BluetoothHandler::Loop() {
  delay(2000);
}