#include "utilities.h"
#include <TFT_eSPI.h>
#include "BluetoothServer.h"
#include "sprites/sprites.h"


BluetoothServer bluetooth;

/**
 * DONT FORGET TO CHANGE THE USER_SETUP.H IN THE TFT_eSPI lib inside .pio/libdeps
 */
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite cursorSprite= TFT_eSprite(&tft);

void setup() {
  Serial.begin(115200);
  bluetooth.Init();

  // Start the tft display and set it to black
  tft.init();
  tft.setRotation(1); //This is the display in landscape
  
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



  cursorSprite.createSprite(16,16);
  cursorSprite.setSwapBytes(true);
  cursorSprite.pushImage(0, 0, 16, 16, cursor); // Use pushImage if cursor is in PROGMEM
  cursorSprite.pushSprite(50, 50, TFT_BLACK);
}
float x = 10;
void loop() {
  bluetooth.Loop();
  // tft.drawString("X: " + String(bluetooth.gyroData.x) + " Y: " + String(bluetooth.gyroData.y), 100, 100, 2); // Left Aligned
  // tft.fillScreen(TFT_BLACK);
  //cursorSprite.pushImage(0,0,16,16, &cursor);
  cursorSprite.pushSprite(x, 50);
  
  x++;

  if(x>330)
  x=-100;
  delay(100);
}