#include <Arduino.h>
/*
  An example showing rainbow colours on a 3.5" TFT LCD screen
  and to show a basic example of font use.

  Make sure all the display driver and pin connections are correct by
  editing the User_Setup.h file in the TFT_eSPI library folder.
#include "BluetoothServer.h"

  Note that yield() or delay(0) must be called in long duration for/while
  loops to stop the ESP8266 watchdog triggering.

  #########################################################################
  ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
  #########################################################################
*/

#include <TFT_eSPI.h>
BluetoothServer bluetooth;

TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);
  bluetooth.Init();
  // Start the tft display and set it to black
  tft.init();
  tft.setRotation(1); //This is the display in landscape
  
  // Clear the screen before writing to it
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  int x = 5;
  int y = 10;
  int fontNum = 2; 
  tft.drawString("Hello", x, y, fontNum); // Left Aligned
  x = 320 /2;
  y += 16;
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.drawCentreString("World", x, y, fontNum);

}

void loop() {
  // put your main code here, to run repeatedly:
  bluetooth.Loop();

}