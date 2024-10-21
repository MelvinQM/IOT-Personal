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

void SpriteRenderer::InitializeDisplay(int rotation, bool swapBytes, int fillColor)
{
    // Start the tft display
    tft.init();
    tft.setRotation(rotation);
    tft.setSwapBytes(swapBytes);

    // Clear the screen before writing to it
    tft.fillScreen(fillColor);
}


void SpriteRenderer::GameLoop(GameSettings &settings)
{
    // Game loop initialization
    cursor.setColorDepth(cursorColorDepth);
    cursor.createSprite(cursorSpriteRatio, cursorSpriteRatio);

    axisText.createSprite(axisTextSettings.width, axisTextSettings.height);
    scoreText.createSprite(scoreTextSettings.width, scoreTextSettings.height);
    bulletsText.createSprite(bulletsTextSettings.width, bulletsTextSettings.height);
    owlsText.createSprite(owlsTextSettings.width, owlsTextSettings.height);

    background.setColorDepth(backgroundColorDepth);
    background.createSprite(SCREEN_WIDTH, SCREEN_HEIGHT);
    background.setSwapBytes(true); // Correct color

    owl.setColorDepth(owlColorDepth);
    owl.createSprite(owlSpriteRatio, owlSpriteRatio);
    owl.pushImage(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, owlSpriteRatio, owlSpriteRatio, owlNeutralSprite); // Initial sprite

    // Gameloop
    startMovementTime, startAnimationTime, startCursorTime = millis();
    owlsKilled = 0;
    owlsMissed = 0;
    bool isRunning = true;
    while(isRunning)
    {
        // Background and UI
        UpdateUI(x, y, score);

        // Owl logic
        MoveOwl();
        
        // Cursor logic
        UpdateCursorPosition(x, y, settings.useGyro);
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

    // Gameloop cleanup
    axisText.deleteSprite();
    scoreText.deleteSprite();
    bulletsText.deleteSprite();
    owlsText.deleteSprite();
    background.deleteSprite();


    settings.score = score + 23;
}

void SpriteRenderer::UpdateCursorPosition(int& x, int& y, bool useGyro) 
{
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
            
            score += (100 + ((SCREEN_WIDTH - owlX) / EXTRA_SCORE_DIVISION_FACTOR)); // Extra points if killed really fast
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
    UpdateTextElement(axisText, axisTextSettings, "X: " + String(x) + ", Y: " + String(y));
    UpdateTextElement(scoreText, scoreTextSettings, "SCORE: " + String(score));
    UpdateTextElement(bulletsText, bulletsTextSettings, String(bullets) + "/" + String(bullets));
    UpdateTextElement(owlsText, owlsTextSettings, String(owlsKilled + owlsMissed) + "/" + String(totalOwls));
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

void SpriteRenderer::ShowIntro(int sessionId)
{
    // Intro screen initialization
    introText.createSprite(introTextSettings.width, introTextSettings.height);
    background.setColorDepth(backgroundColorDepth);
    background.createSprite(SCREEN_WIDTH, SCREEN_HEIGHT);
    background.setSwapBytes(true); // Correct color
    
    // Intro screen
    background.fillSprite(TFT_PURPLE);
    UpdateTextElement(introText, introTextSettings, "HOOT SHOOTER SESSION-ID:" + String(sessionId));
    
    // Update screen
    background.pushSprite(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y);

    // Intro screen cleanup
    introText.deleteSprite();
    background.deleteSprite();
}

void SpriteRenderer::ShowHighscores()
{

}

void SpriteRenderer::UpdateTextElement(TFT_eSprite &text, TextSpriteSettings &settings, String content)
{
    text.setTextColor(TFT_WHITE,TFT_BLACK);
    text.fillSprite(TFT_BLACK);
    text.drawString(content, SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, settings.fontSize);
    text.pushToSprite(&background, settings.posX, settings.posY, TFT_BLACK);
}