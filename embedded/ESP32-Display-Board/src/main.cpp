#include "utilities.h"
#include <TFT_eSPI.h>
#include "BluetoothServer.h"
#include "sprites/sprites.h"

/**
 * DONT FORGET TO CHANGE THE USER_SETUP.H IN THE TFT_eSPI lib inside .pio/libdeps
 */

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite arrowSprite= TFT_eSprite(&tft);
TFT_eSprite background= TFT_eSprite(&tft);
BluetoothServer bluetooth;

void setup() {
  Serial.begin(115200);
  // bluetooth.Init();

  // Start the tft display and set it to black
  tft.init();
  tft.setRotation(1); //This is the display in landscape
  tft.setSwapBytes(true);

  // Clear the screen before writing to it
  tft.fillScreen(TFT_BLACK);

  // tft.setTextColor(TFT_WHITE, TFT_BLACK);
  // int x = 5;
  // int y = 10;
  // int fontNum = 2; 
  // tft.drawString("Hello", x, y, fontNum); // Left Aligned
  // x = 320 /2;
  // y += 16;
  // tft.setTextColor(TFT_BLUE, TFT_BLACK);
  // tft.drawCentreString("World", x, y, fontNum);

  background.createSprite(320,170);
  background.setSwapBytes(true);
  arrowSprite.createSprite(32,32);
}

float x = 50;
float y = 50;
void loop() {
  // bluetooth.Loop();
  // tft.drawString("X: " + String(bluetooth.gyroData.x) + " Y: " + String(bluetooth.gyroData.y), 100, 100, 2); // Left Aligned

  // background.pushImage(0,0,320,170,city);
  background.fillSprite(TFT_PURPLE);
  arrowSprite.pushImage(0,0,16,16,cursor);
  arrowSprite.pushToSprite(&background,100,100,TFT_BLACK); 
  
  x++;
  y++;
  if (x > 320) {
      x = 0;
  }
  if (y > 240) {
      y = 0;
  }

  background.pushSprite(0,0);
  delay(100);
}