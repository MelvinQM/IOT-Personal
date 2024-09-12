#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  pinMode(16, INPUT);
  digitalWrite(16, LOW);
}

void loop() {
  bool pressed = digitalRead(16);
  Serial.println(pressed);
  if(pressed) 
  {
      Serial.println("Button pressed");
      //api.CreatePlayer("Lucas");
  }

  delay(1000);
}