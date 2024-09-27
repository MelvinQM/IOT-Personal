#include "utilities.h"
#include "BluetoothServer.h"
#include "game.h"

BluetoothServer bluetooth;
Game game;

void setup() {
  Serial.begin(115200);
  // bluetooth.Init();
  game.Init();
}

void loop() {
  // bluetooth.Loop();
  game.Loop();
  delay(100);
}