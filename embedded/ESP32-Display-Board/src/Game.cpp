#include "game.h"

/**
 * DONT FORGET TO CHANGE THE USER_SETUP.H IN THE TFT_eSPI lib inside .pio/libdeps
 */

void Game::Init()
{
    // Initiate communication with controller
    // bluetooth.Init();

    // Start the tft display and set it to black
    tft.init();
    tft.setRotation(1); //This is the display in landscape
    tft.setSwapBytes(true);

    // Clear the screen before writing to it
    tft.fillScreen(TFT_BLACK);
}


float x = 50;
float y = 50;
void Game::Loop()
{
    // Communication with controller
    // bluetooth.Loop();


    /////////////////////////////////////////////////////////////////////////////

    background.createSprite(screenWidth, screenHeight);
    background.setSwapBytes(true); // Correct color
    background.setColorDepth(8);
    background.pushImage(0, 0, screenWidth, screenHeight, backgroundSprite);

    cursor.createSprite(16,16);
    cursor.setColorDepth(8);

    gyroText.createSprite(240,40);
    gyroText.setTextColor(TFT_WHITE,TFT_BLACK);
    gyroText.fillSprite(TFT_BLACK);
    gyroText.drawString("X: " + String(x) + ", Y: " + String(y),0,0,4);
    gyroText.pushToSprite(&background,10,10,TFT_BLACK);

    cursor.pushImage(0, 0, 16, 16, cursorSprite);
    cursor.pushToSprite(&background, x, y, TFT_BLACK); 
    
    background.pushSprite(0,0);

    ///////////////////////////////////////////////////////////////
    x++;
    y++;
    if (x > screenWidth) {
        x = 0;
    }
    if (y > screenHeight) {
        y = 0;
    }
}