/*
 * Author: Melvin Moes
 * Date: October 17, 2024
 * Description: 
 */

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

unsigned long startMovementTime;
unsigned long startAnimationTime;
unsigned long startCursorTime;
unsigned long elapsedTime;
void SpriteRenderer::GameLoop(Difficulty diff, bool useGyro)
{
    bool isRunning = true;
    int x = SCREEN_WIDTH / 2 -  cursorSpriteRatio / 2;
    int y = SCREEN_HEIGHT / 2 - cursorSpriteRatio / 2;

    startMovementTime, startAnimationTime, startCursorTime = millis();
    while(isRunning)
    {
        // Background and UI
        background.pushImage(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, SCREEN_WIDTH, SCREEN_HEIGHT, backgroundSprite);
        gyroText.setTextColor(TFT_WHITE,TFT_BLACK);
        gyroText.fillSprite(TFT_BLACK);
        gyroText.drawString("X: " + String(x) + ", Y: " + String(y), SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, 4);
        gyroText.pushToSprite(&background, 10, 10, TFT_BLACK);


        // Owl logic
        elapsedTime = millis() - startAnimationTime;
        if(elapsedTime > animationDelay)   // Calculate elapsed time in microseconds)
        {
            animationIndex++;
            if(animationIndex == 4) animationIndex = 0;
            owl.pushImage(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, owlSpriteRatio, owlSpriteRatio, (const unsigned short*) pgm_read_ptr(&spriteArray[animationIndex]));
            startAnimationTime = millis();
        }

        elapsedTime = millis() - startMovementTime;
        if(elapsedTime > movementDelay)
        {
            owlX += movementStepSize;
            if(owlX > SCREEN_WIDTH + owlSpriteRatio) owlX = -owlSpriteRatio;
            owl.pushToSprite(&background, owlX, owlY, TFT_BLACK);
            startMovementTime = millis();
        }
        




        // Cursor logic
        
        // Collision detection
        if (CheckCollision(x, y, cursorSpriteRatio - 10, owlX, owlY, owlSpriteRatio - 10)) {
            cursor.pushImage(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, cursorSpriteRatio, cursorSpriteRatio, cursorSpriteRed);
        } else {
            cursor.pushImage(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, cursorSpriteRatio, cursorSpriteRatio, cursorSprite);
        }

        elapsedTime = millis() - startCursorTime;
        if(elapsedTime > cursorMovementDelay)
        {
            if(useGyro) {
                x = gData->x;
                y = gData->y;
            } else {
                float magnitude = sqrt((jData->x * jData->x) + (jData->y * jData->y)); // Calculate the magnitude
                if (magnitude > 0) {
                    float normalizedX = jData->x / magnitude;
                    float normalizedY = jData->y / magnitude;

                    x += normalizedX * CURSOR_SPEED;
                    y += normalizedY * CURSOR_SPEED;
                }
            }
            if(x > SCREEN_WIDTH - cursorSpriteRatio) x = SCREEN_WIDTH - cursorSpriteRatio;
            if(y > SCREEN_HEIGHT - cursorSpriteRatio) y = SCREEN_HEIGHT - cursorSpriteRatio;
            if(x < SCREEN_ORIGIN_X) x = SCREEN_ORIGIN_X;
            if(y < SCREEN_ORIGIN_Y) y = SCREEN_ORIGIN_Y;
            cursor.pushToSprite(&background, x, y, TFT_BLACK); 
            startCursorTime = millis();
        }





        // Update screen
        background.pushSprite(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y);
        //vTaskDelay(REFRESH_RATE / portTICK_PERIOD_MS);
    }
    // If end game is triggered set running to false
    // TODO: Think of a reason to end the game
}

bool SpriteRenderer::CheckCollision(int cursorX, int cursorY, int cursorHitBoxSize, int owlX, int owlY, int owlHitBoxSize) {
    // Check if the bounding boxes overlap
    return (cursorX < owlX + owlHitBoxSize && 
            cursorX + cursorHitBoxSize > owlX && 
            cursorY < owlY + owlHitBoxSize && 
            cursorY + cursorHitBoxSize > owlY);
}
