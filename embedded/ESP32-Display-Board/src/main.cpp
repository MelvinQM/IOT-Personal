#include "utilities.h"
#include "game.h"

Game game;

void setup() {
  Serial.begin(115200);
  game.Init();
}

void loop() {
  game.Loop();
  delay(100);
}