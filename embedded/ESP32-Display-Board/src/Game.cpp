#include "game.h"

/**
 * DONT FORGET TO CHANGE THE USER_SETUP.H IN THE TFT_eSPI lib inside .pio/libdeps
 */

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite cursor = TFT_eSprite(&tft);
TFT_eSprite background = TFT_eSprite(&tft);

void Game::Init()
{
    // Start the tft display and set it to black
    tft.init();
    tft.setRotation(1); //This is the display in landscape
    tft.setSwapBytes(true);

    // Clear the screen before writing to it
    tft.fillScreen(TFT_BLACK);

    background.createSprite(screenWidth, screenHeigth);
    background.setSwapBytes(true);
    cursor.createSprite(16,16);

    background.setColorDepth(8);
    cursor.setColorDepth(8);
}


float x = 50;
float y = 50;
void Game::Loop()
{
    // tft.drawString("X: " + String(bluetooth.gyroData.x) + " Y: " + String(bluetooth.gyroData.y), 100, 100, 2);
    background.pushImage(0, 0, screenWidth, screenHeigth, backgroundSprite);
    cursor.pushImage(0,0,16,16,cursorSprite);
    cursor.pushToSprite(&background,100,100,TFT_BLACK); 
    
    x++;
    y++;
    if (x > screenWidth) {
        x = 0;
    }
    if (y > screenHeigth) {
        y = 0;
    }

    background.pushSprite(0,0);
}