#include "utilities.h"
#include "GameController.h"

GameController game;

void setup() {
  Serial.begin(115200);
  game.Init();
}

void loop() {
  game.Loop();
}