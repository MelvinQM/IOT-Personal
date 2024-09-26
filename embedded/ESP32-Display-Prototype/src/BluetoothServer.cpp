
#include "BluetoothServer.h"


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

    pCharacteristic->setCallbacks(new WriteCallback());    
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
    delay(500);
  }
  
  if(!isAdvertising && !deviceConnected){
    pServer->startAdvertising();
    Serial.println("Device disconnected - Start advertising");
    isAdvertising = true;
    delay(500);
  }
}