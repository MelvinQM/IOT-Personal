/*
 * Author: Melvin Moes Moes Moes Moes
 * Date: October 14, 2024
 * Description: An implementation of the Bluetoothclient header. This Bluetooth client handles communication with a remote BLE server, receiving data from a gyroscope 
 * and sending it to the server. The client connects to the BLE server, subscribes to notifications, and sends gyroscope  data in JSON format through a Bluetooth characteristic.
 * License: This project is licensed under the MIT License.
 */

#include "utilities.h"
#include "bluetooth_client.h"

BluetoothClient::BluetoothClient(Gyroscope *gyro) : gyro(gyro) {}
BluetoothClient::~BluetoothClient() {}

// The remote service we wish to connect to.
static BLEUUID serviceUUID("b2f6ac88-8216-4faf-b31e-3f37926031be");

// The characteristic of the remote service we are interested in.
static BLEUUID charUUID("797bd60e-c9f7-4657-ac8f-aca7b9dd4b58");

static boolean doConnect = false;
static boolean connected = false;
static boolean doScan = false;
static BLERemoteCharacteristic *pRemoteCharacteristic;
static BLEAdvertisedDevice *myDevice;

static void notifyCallback(BLERemoteCharacteristic *pBLERemoteCharacteristic, uint8_t *pData, size_t length, bool isNotify) {
  Serial.print("Notify callback for characteristic ");
  Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
  Serial.print(" of data length ");
  Serial.println(length);
  Serial.print("data: ");
  Serial.write(pData, length);
  Serial.println();
}

class MyClientCallback : public BLEClientCallbacks {
  void onConnect(BLEClient *pClient) {}

  void onDisconnect(BLEClient *pClient) {
    connected = false;
    Serial.println("onDisconnect");
  }
};

bool connectToServer() {
  Serial.print("Forming a connection to ");
  Serial.println(myDevice->getAddress().toString().c_str());

  BLEClient *pClient = BLEDevice::createClient();
  pClient->setClientCallbacks(new MyClientCallback());

  // Connect to the remote BLE Server.
  pClient->connect(myDevice);  // If you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
  Serial.println(" - Connected to server");
  // Set client to request maximum MTU from server (default is 23 otherwise)
  pClient->setMTU(517);  

  // Obtain a reference to the service we are after in the remote BLE server.
  BLERemoteService *pRemoteService = pClient->getService(serviceUUID);
  if (pRemoteService == nullptr) {
    Serial.print("Failed to find our service UUID: ");
    Serial.println(serviceUUID.toString().c_str());
    pClient->disconnect();
    return false;
  }
  Serial.println(" - Found our service");

  // Obtain a reference to the characteristic in the service of the remote BLE server.
  pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
  if (pRemoteCharacteristic == nullptr) {
    Serial.print("Failed to find our characteristic UUID: ");
    Serial.println(charUUID.toString().c_str());
    pClient->disconnect();
    return false;
  }
  Serial.println(" - Found our characteristic");

  // Read the value of the characteristic.
  if (pRemoteCharacteristic->canRead()) {
    std::string value = pRemoteCharacteristic->readValue();
    Serial.print("The characteristic value was: ");
    Serial.println(value.c_str());
  }

  if (pRemoteCharacteristic->canNotify()) {
    pRemoteCharacteristic->registerForNotify(notifyCallback);
  }

  connected = true;
  return true;
}

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  //Called for each advertising BLE server.
  void onResult(BLEAdvertisedDevice advertised_device) {
    if (advertised_device.haveServiceUUID() && advertised_device.isAdvertisingService(serviceUUID)) {
      BLEDevice::getScan()->stop();
      myDevice = new BLEAdvertisedDevice(advertised_device);
      doConnect = true;
      doScan = true;
    }
  }
};

void BluetoothClient::Init()
{
  Serial.println("Starting Arduino BLE Client application...");
  BLEDevice::init("");

  BLEScan *pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);
}

void BluetoothClient::Loop()
{
  // Try to connect once
  if (doConnect == true) {
    if (connectToServer()) {
      Serial.println("We are now connected to the BLE Server.");
    } else {
      Serial.println("We have failed to connect to the server; there is nothing more we will do.");
    }
    doConnect = false;
  }

  // When connection is established send data
  if (connected) {
    String data = SendGyroData();
    Serial.println("Setting new characteristic value to \"" + data + "\"");
    pRemoteCharacteristic->writeValue(data.c_str(), data.length());
  } else if (doScan) {
    BLEDevice::getScan()->start(0);
  }
}

String BluetoothClient::SendGyroData()
{
  // Get data from gyroscope
  GyroData data = gyro->GetXYZ();

  // Create a JSON document
  JsonDocument jsonDoc;
  jsonDoc["x"] = data.x;
  jsonDoc["y"] = data.y;

  // Serialize the JSON document to a string
  String output;
  serializeJson(jsonDoc, output);

  return output;
}