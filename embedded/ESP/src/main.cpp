#include "utilities.h"
#include "BluetoothHandler.h"

BluetoothHandler bluetooth;

void setup() {
    Serial.begin(115200);
    bluetooth.Init();
}

void loop() {
    bluetooth.Loop();
}