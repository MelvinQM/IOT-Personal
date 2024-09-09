#include "utilities.h"
#include "game.h"

Game game;

void setup() {
  game.Init();
}

void loop() {
  game.Run();
}