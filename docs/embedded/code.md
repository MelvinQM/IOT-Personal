# Embedded code

This is not a place to put your code, but to describe the code that you have written. You can describe the code in a general way, but also go into detail on specific parts of the code. You can also refer to the code in your repository. So just add a link to the code in your repository.

## Contents
1. **[Game State Machine](#1-game-statemachine)**
2. **[Bluetooth](#2-bluetooth)**
   1. **[Server](#21-server)**
   2. **[Client](#22-client)**
3. **[WiFi](#3-wifimanager)**

## 1. Game statemachine


## 2. Bluetooth (BLE)

### 2.1 BLE Server
For more information about the workings of see the [Techincal documentation](./technical_documentation.md##4-bluetooth-ble).

#### 2.1.1 Initialization
Initializes the BLE server, sets up the service and characteristic.
```c++
BLEDevice::init("ESP32 Bluetooth server");
pServer = BLEDevice::createServer();
BLEService *pService = pServer->createService(SERVICE_UUID);

// Allow read and write
pCharacteristic = pService->createCharacteristic(
                                CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ | 
                                BLECharacteristic::PROPERTY_WRITE
                            );
```


Setting up the callbacks for the characteristic write events and the Server events more on this in [Callbacks](#212-callbacks)
```c++
pCharacteristic->setCallbacks(new WriteCallback(this));    
pServer->setCallbacks(new ServerCallbacks());
```
Finally starting the service through the use of the start() function and enabling advertising to allow the client to connect and send data to the server.

```c++
pService->start();

BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
pAdvertising->addServiceUUID(SERVICE_UUID);
pAdvertising->setScanResponse(true);

BLEDevice::startAdvertising();
```

#### 2.1.2 Callbacks

**WriteCallback**: Handles write operations to the BLE characteristic.

**Functions**:
```c++
void onWrite(BLECharacteristic *pCharacteristic){}
```

**Usage**: Called when a client writes data to the characteristic.
Deserializes the JSON data and updates gyroData.

**ServerCallbacks**: Manages connection and disconnection events.

**Functions**:
```c++
// Called when a device connects.
void onConnect(BLEServer *pServer)

// Called when a device disconnects.
void onDisconnect(BLEServer *pServer)
```


### 2.2 BLE Client


## 3. WifiManager


## 4. Components


### 4.1 MPU6050


### 4.2 ESP32-2432S024
