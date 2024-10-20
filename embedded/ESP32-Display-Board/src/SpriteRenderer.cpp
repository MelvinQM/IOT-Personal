/*
 * Author: Melvin Moes
 * Date: October 18, 2024
 * Description: This class handles the rendering of sprites using the TFT_eSPI library. 
 * The class can initialize the display, handle rendering of the cursor, background, and owl/enemy sprites,
 * and their positions and logic such as collision. 
 * Based on given parameters the gameloop can be altered based on control schemes and difficulty
 * License: This project is licensed under the MIT License.
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

    axisText.createSprite(axisTextWidth, axisTextHeight);
    scoreText.createSprite(scoreTextWidth, scoreTextHeight);
    bulletsText.createSprite(bulletsTextWidth, bulletsTextHeight);
    owlsText.createSprite(owlsTextWidth, owlsTextHeight);

    background.setColorDepth(backgroundColorDepth);
    background.createSprite(SCREEN_WIDTH, SCREEN_HEIGHT);
    background.setSwapBytes(true); // Correct color

    owl.setColorDepth(owlColorDepth);
    owl.createSprite(owlSpriteRatio, owlSpriteRatio);
    owl.pushImage(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, owlSpriteRatio, owlSpriteRatio, owlNeutralSprite); // Initial sprite
}


void SpriteRenderer::GameLoop(Difficulty diff, bool useGyro)
{
    startMovementTime, startAnimationTime, startCursorTime = millis();
    bool isRunning = true;
    while(isRunning)
    {
        // Background and UI
        UpdateUI(x, y, score);

        // Owl logic
        MoveOwl();
        
        // Cursor logic
        UpdateCursorPosition(x, y, useGyro);
        HandleCursorCollision(x, y);

        // Update screen
        background.pushSprite(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y);

        if(!((owlsKilled + owlsMissed) < totalOwls))  
        {
            UpdateUI(x, y, score);
            background.pushSprite(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y);
            isRunning = false;
        }
    }
}

void SpriteRenderer::UpdateCursorPosition(int& x, int& y, bool useGyro) {
        elapsedTime = millis() - startCursorTime;
        if(elapsedTime > cursorMovementDelay)
        {
            if(useGyro) {
                x = g.GetGyroX();
                y = g.GetGyroY();
            } else {
                float jX = g.GetJoystickX();
                float jY = g.GetJoystickY();
                float magnitude = sqrt((jX * jX) + (jY * jY));
                if (magnitude > 0) {
                    x += jX / magnitude * CURSOR_SPEED;
                    y += jY / magnitude * CURSOR_SPEED;
                }
            }
            if(x > SCREEN_WIDTH - cursorSpriteRatio) x = SCREEN_WIDTH - cursorSpriteRatio;
            if(y > SCREEN_HEIGHT - cursorSpriteRatio) y = SCREEN_HEIGHT - cursorSpriteRatio;
            if(x < SCREEN_ORIGIN_X) x = SCREEN_ORIGIN_X;
            if(y < SCREEN_ORIGIN_Y) y = SCREEN_ORIGIN_Y;
            cursor.pushToSprite(&background, x, y, TFT_BLACK); 
            startCursorTime = millis();
        }
}

void SpriteRenderer::HandleCursorCollision(int& x, int& y)
{
    // Collision detection
    if (CheckCollision(x, y, cursorSpriteRatio - 10, owlX, owlY, owlSpriteRatio - 10) && owlAlive) {
        cursor.pushImage(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, cursorSpriteRatio, cursorSpriteRatio, cursorSpriteRed);
        if (g.GetTriggerPress()) {
            owlAlive = false;
            owlsKilled++;
            Serial.println("Owl killed!");
            score += 100;
            owl.fillSprite(TFT_BLACK);
            g.SetTriggerPressed(false);
        }
    } else {
        cursor.pushImage(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, cursorSpriteRatio, cursorSpriteRatio, cursorSprite);
    }
}

bool SpriteRenderer::CheckCollision(int cursorX, int cursorY, int cursorHitBoxSize, int owlX, int owlY, int owlHitBoxSize) {
    // Check if the bounding boxes overlap
    return (cursorX < owlX + owlHitBoxSize && 
            cursorX + cursorHitBoxSize > owlX && 
            cursorY < owlY + owlHitBoxSize && 
            cursorY + cursorHitBoxSize > owlY);
}

void SpriteRenderer::UpdateUI(int& x, int& y, int& score)
{
    background.pushImage(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, SCREEN_WIDTH, SCREEN_HEIGHT, backgroundSprite);
    
    axisText.setTextColor(TFT_WHITE,TFT_BLACK);
    axisText.fillSprite(TFT_BLACK);
    axisText.drawString("X: " + String(x) + ", Y: " + String(y), SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, axisTextFontSize);
    axisText.pushToSprite(&background, axisPosX, axisPosY, TFT_BLACK);

    scoreText.setTextColor(TFT_WHITE,TFT_BLACK);
    scoreText.fillSprite(TFT_BLACK);
    scoreText.drawString("SCORE: " + String(score) , SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, scoreTextFontSize);
    scoreText.pushToSprite(&background, scorePosX, scorePosY, TFT_BLACK);

    bulletsText.setTextColor(TFT_WHITE,TFT_BLACK);
    bulletsText.fillSprite(TFT_BLACK);
    bulletsText.drawString(String(bullets) + "/" + String(bullets) , SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, bulletsTextFontSize);
    bulletsText.pushToSprite(&background, bulletsTextPosX, bulletsTextPosY, TFT_BLACK);

    owlsText.setTextColor(TFT_WHITE,TFT_BLACK);
    owlsText.fillSprite(TFT_BLACK);
    owlsText.drawString(String(owlsKilled + owlsMissed) + "/" + String(totalOwls) , SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, owlsTextFontSize);
    owlsText.pushToSprite(&background, owlsTextPosX, owlsTextPosY, TFT_BLACK);
}

void SpriteRenderer::MoveOwl()
{
    AnimateOwl();

    elapsedTime = millis() - startMovementTime;
    if(elapsedTime > movementDelay)
    {
        owlX += movementStepSize;
        // If owl flies offscreen
        if(owlX > SCREEN_WIDTH + owlSpriteRatio) {
            if(!owlAlive) {
                ResetOwl();
            } else {
                Serial.println("Owl missed!");
                owlsMissed++;
                ResetOwl();
            }

        }
        owl.pushToSprite(&background, owlX, owlY, TFT_BLACK);
        startMovementTime = millis();
    }
}

void SpriteRenderer::AnimateOwl()
{
    elapsedTime = millis() - startAnimationTime;
    if(elapsedTime > animationDelay && owlAlive)   // Calculate elapsed time in microseconds)
    {
        animationIndex++;
        if(animationIndex == 4) animationIndex = 0;
        owl.pushImage(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, owlSpriteRatio, owlSpriteRatio, (const unsigned short*) pgm_read_ptr(&spriteArray[animationIndex]));
        startAnimationTime = millis();
    }
}

void SpriteRenderer::ResetOwl()
{
    // Respawn the owl at the starting position
    owlX = -owlSpriteRatio; // Start owl offscreen on the left
    owlY = random(SCREEN_ORIGIN_Y, SCREEN_HEIGHT - owlSpriteRatio);
    owlAlive = true;

    bullets = 3;
}

void SpriteRenderer::ShowHighscores()
{

}

void SpriteRenderer::ShowIntro()
{

}

