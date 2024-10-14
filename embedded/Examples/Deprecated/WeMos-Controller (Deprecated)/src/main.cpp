#include "utilities.h"
#include "game.h"
#include <ESP8266WiFi.h>

Game game;

void setup() 
{
  Serial.begin(74880);
  game.Init();
  
}

void loop() 
{
  game.Run(); 
}