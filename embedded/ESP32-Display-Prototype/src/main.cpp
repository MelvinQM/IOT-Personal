#include "utilities.h"
#include "BluetoothServer.h"

BluetoothServer bluetooth;

void setup() {
    Serial.begin(115200);
    bluetooth.Init();
}

void loop() {
    bluetooth.Loop();
}