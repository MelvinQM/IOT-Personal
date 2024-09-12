#include "utilities.h"
#include "game.h"
#include <ESP8266WiFi.h>

Game game;

void setup() {
  Serial.begin(74880);
  game.Init();

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  Serial.print("Print\n");
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}