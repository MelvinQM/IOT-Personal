#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(){}
SpriteRenderer::~SpriteRenderer(){}

void SpriteRenderer::InitializeDisplay(int rotation, bool swapBytes, int fillColor)
{
    // Start the tft display
    tft.init();
    tft.setRotation(rotation);
    tft.setSwapBytes(swapBytes);

    // Clear the screen before writing to it
    tft.fillScreen(fillColor);

    cursor.setColorDepth(cursorColorDepth);
    cursor.createSprite(cursorSpriteRatio, cursorSpriteRatio);

    gyroText.createSprite(axisTextWidth, axisTextHeight);

    background.setColorDepth(backgroundColorDepth);
    background.createSprite(SCREEN_WIDTH, SCREEN_HEIGHT);
    background.setSwapBytes(true); // Correct color

    owl.setColorDepth(owlColorDepth);
    owl.createSprite(owlSpriteRatio, owlSpriteRatio);
    owl.pushImage(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, owlSpriteRatio, owlSpriteRatio, owlNeutralSprite); // Initial sprite
}

void SpriteRenderer::SetAxisData(GyroData *gData, JoystickData *jData)
{
    this->gData = gData;
    this->jData = jData;
}

unsigned long startTime;
unsigned long elapsedTime;
void SpriteRenderer::GameLoop(Difficulty diff, bool useGyro)
{
    bool isRunning = true;
    int x = SCREEN_WIDTH / 2;
    int y = SCREEN_HEIGHT / 2;

    startTime = millis();
    while(isRunning)
    {
        // Background and UI
        background.pushImage(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, SCREEN_WIDTH, SCREEN_HEIGHT, backgroundSprite);
        gyroText.setTextColor(TFT_WHITE,TFT_BLACK);
        gyroText.fillSprite(TFT_BLACK);
        gyroText.drawString("X: " + String(x) + ", Y: " + String(y), SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, 4);
        gyroText.pushToSprite(&background, 10, 10, TFT_BLACK);


        // Cursor logic
        cursor.pushImage(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, cursorSpriteRatio, cursorSpriteRatio, cursorSprite);
        if(USE_GYRO) {
            x = gData->x;
            y = gData->y;
        } else {
            x += jData->x * CURSOR_SPEED;
            y += jData->y * CURSOR_SPEED;

            if(x > SCREEN_WIDTH) x = SCREEN_WIDTH;
            if(y > SCREEN_HEIGHT) y = SCREEN_HEIGHT;
            if(x < SCREEN_ORIGIN_X) y = SCREEN_ORIGIN_X;
            if(y < SCREEN_ORIGIN_Y) y = SCREEN_ORIGIN_Y;
        }
        cursor.pushToSprite(&background, x, y, TFT_BLACK); 
        // cursor.pushImage(0, 0, cursorSpriteRatio, cursorSpriteRatio, cursorSpriteRed);
        // cursor.pushToSprite(&background, conn.gyroData.x, conn.gyroData.y, TFT_BLACK); 

        // Owl logic
        if((millis() - startTime) > animationDelay)   // Calculate elapsed time in microseconds)
        {
            animationIndex++;
            if(animationIndex == 4) animationIndex = 0;
            owl.pushImage(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, owlSpriteRatio, owlSpriteRatio, (const unsigned short*) pgm_read_ptr(&spriteArray[animationIndex]));
        }
        owl.pushToSprite(&background, 100, 100, TFT_BLACK);




        // Update screen
        background.pushSprite(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y);
        vTaskDelay(REFRESH_RATE / portTICK_PERIOD_MS);
    }
    // If end game is triggered set running to false
    // TODO: Think of a reason to end the game
}
