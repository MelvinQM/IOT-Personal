/*
 * Author: Melvin Moes
 * Date: November 6, 2024
 * Description: This class handles the rendering of sprites using the TFT_eSPI library. 
 * The class can initialize the display, handle rendering of the cursor, background, and owl/enemy sprites,
 * and their positions and logic such as collision. 
 * Based on given parameters the gameloop can be altered based on control schemes and difficulty
 * License: This project is licensed under the MIT License.
 */

#include "sprite_renderer.h"

void SpriteRenderer::init(int rotation, bool swapBytes, int fillColor)
{
    // Start the tft display
    tft.init();
    tft.setRotation(rotation);
    tft.setSwapBytes(swapBytes);

    // Clear the screen before writing to it
    tft.fillScreen(fillColor);

    
    background.setColorDepth(kBackgroundColorDepth);
    background.createSprite(SCREEN_WIDTH, SCREEN_HEIGHT);
    background.setSwapBytes(true); // Correct color
}

void SpriteRenderer::gameLoop(GameSettings &settings)
{
    renderCountdown();


    // Applying game difficulties
    if(settings.difficultyId == NORMAL) {
        movementStepSize = kMovementStepSizeNormal;
        owlKillScore = kOwlKillScoreNormal;
        totalBullets = kTotalBulletsNormal;
    } else if(settings.difficultyId == HARD) {
        movementStepSize = kMovementStepSizeHard;
        owlKillScore = kOwlKillScoreHard;
        totalBullets = kTotalBulletsHard;
    }

    // Game loop initialization
    createCursorSprite();

    //axisText.createSprite(kAxisTextSettings.width, kAxisTextSettings.height);
    scoreText.createSprite(kScoreTextSettings.width, kScoreTextSettings.height);
    bulletsText.createSprite(kBulletsTextSettings.width, kBulletsTextSettings.height);
    owlsText.createSprite(kOwlsTextSettings.width, kOwlsTextSettings.height);

    owl.setColorDepth(kOwlColorDepth);
    owl.createSprite(kOwlSpriteRatio, kOwlSpriteRatio);
    owl.pushImage(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, kOwlSpriteRatio, kOwlSpriteRatio, kOwlNeutralSprite); // Initial sprite
    resetOwl();

    // Gameloop
    startMovementTime, startAnimationTime, startCursorTime = millis();
    owlsKilled = 0;
    owlsMissed = 0;
    bool isRunning = true;
    g.setTriggerPressed(false); // Prevent buffered input
    while(isRunning)
    {
        // Background and UI
        updateUI(x, y, score);

        // Owl logic
        moveOwl();
        
        // Cursor logic
        updateCursorPosition(x, y, settings.useGyro);
        handleTriggerFire(x, y);

        // Update screen
        background.pushSprite(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y);

        if(!((owlsKilled + owlsMissed) < totalOwls))  
        {
            updateUI(x, y, score);
            background.pushSprite(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y);
            isRunning = false;
        }
    }

    // Gameloop cleanup
    //axisText.deleteSprite();
    scoreText.deleteSprite();
    bulletsText.deleteSprite();
    owlsText.deleteSprite();

    settings.score = score;
    score = 0;
}

void SpriteRenderer::updateCursorPosition(int& x, int& y, bool useGyro) 
{
        elapsedTime = millis() - startCursorTime;
        if(elapsedTime > kCursorMovementDelay)
        {
            if(useGyro) {
                x = g.getGyroX();
                y = g.getGyroY();
            } else {
                float jX = g.getJoystickX();
                float jY = g.getJoystickY();
                float magnitude = sqrt((jX * jX) + (jY * jY));
                if (magnitude > 0) {
                    x += jX / magnitude * CURSOR_SPEED;
                    y += jY / magnitude * CURSOR_SPEED;
                }
            }
            if(x > SCREEN_WIDTH - kCursorSpriteRatio) x = SCREEN_WIDTH - kCursorSpriteRatio;
            if(y > SCREEN_HEIGHT - kCursorSpriteRatio) y = SCREEN_HEIGHT - kCursorSpriteRatio;
            if(x < SCREEN_ORIGIN_X) x = SCREEN_ORIGIN_X;
            if(y < SCREEN_ORIGIN_Y) y = SCREEN_ORIGIN_Y;
            cursor.pushToSprite(&background, x, y, TFT_BLACK); 
            startCursorTime = millis();
        }
}

void SpriteRenderer::handleTriggerFire(int& x, int& y)
{
    bool firedTrigger = g.getTriggerPressed() && !shootOnCooldown && bullets != 0;
    unsigned long currentTime = millis();

    if(firedTrigger)
    {
        shootDelayStartTime = millis();
        shootOnCooldown = true;
        bullets--;
        g.setTriggerPressed(false);
    }

    if(shootOnCooldown)
    {
        g.setTriggerPressed(false);
        unsigned long elapsedFlashTime = currentTime - shootDelayStartTime;
        if (elapsedFlashTime < kShootCooldownDuration) {
            if ((elapsedFlashTime / dFlashInterval) % 2 == 0) {
                cursor.deleteSprite();
            } else {
                createCursorSprite();
            }
        } else {
            shootOnCooldown = false;
            createCursorSprite();
        }
    }

    

    // Collision detection
    if (checkCollision(x, y, kCursorSpriteRatio - kCursorHitBoxMargin, owlX, owlY, kCursorSpriteRatio - kCursorHitBoxMargin) && owlAlive) {
        cursor.pushImage(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, kCursorSpriteRatio, kCursorSpriteRatio, cursorSpriteRed);
        if (firedTrigger) {
            owlAlive = false;
            owlsKilled++;
            Serial.println("Owl killed!");
            
            score += (owlKillScore + ((SCREEN_WIDTH - owlX) / EXTRA_SCORE_DIVISION_FACTOR)); // Extra points if killed really fast
            owl.fillSprite(TFT_BLACK);
            g.setTriggerPressed(false);

            bullets = totalBullets;
        }
    } else {
        cursor.pushImage(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, kCursorSpriteRatio, kCursorSpriteRatio, kCursorSprite);
    }
}

bool SpriteRenderer::checkCollision(int cursorX, int cursorY, int cursorHitBoxSize, int owlX, int owlY, int owlHitBoxSize) {
    // Check if the bounding boxes overlap
    return (cursorX < owlX + owlHitBoxSize && 
            cursorX + cursorHitBoxSize > owlX && 
            cursorY < owlY + owlHitBoxSize && 
            cursorY + cursorHitBoxSize > owlY);
}

void SpriteRenderer::updateUI(int& x, int& y, int& score)
{
    background.pushImage(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, SCREEN_WIDTH, SCREEN_HEIGHT, kBackgroundSprite);
    //updateTextElement(axisText, kAxisTextSettings, "X: " + String(x) + ", Y: " + String(y));
    updateTextElement(scoreText, kScoreTextSettings, "SCORE: " + String(score));
    updateTextElement(bulletsText, kBulletsTextSettings, String(bullets) + "/" + String(totalBullets));
    updateTextElement(owlsText, kOwlsTextSettings, String(owlsKilled + owlsMissed) + "/" + String(totalOwls));
}

void SpriteRenderer::moveOwl()
{
    animateOwl();
    elapsedTime = millis() - startMovementTime;
    if(elapsedTime > kMovementDelay)
    {
        owlX += movementStepSize;
        // If owl flies offscreen
        if(owlX > SCREEN_WIDTH + kOwlSpriteRatio) {
            if(!owlAlive) {
                resetOwl();
            } else {
                //Serial.println("Owl missed!");
                owlsMissed++;
                bullets = totalBullets;
                resetOwl();
            }

        }
        owl.pushToSprite(&background, owlX, owlY, TFT_BLACK);
        startMovementTime = millis();
    }
}

void SpriteRenderer::animateOwl()
{
    elapsedTime = millis() - startAnimationTime;
    if(elapsedTime > kAnimationDelay && owlAlive)   // Calculate elapsed time in microseconds)
    {
        animationIndex = (animationIndex + 1) % kTotalAnimationFrames;
        owl.pushImage(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, kOwlSpriteRatio, kOwlSpriteRatio, (const unsigned short*) pgm_read_ptr(&kSpriteArray[animationIndex]));
        startAnimationTime = millis();
    }
}

void SpriteRenderer::resetOwl()
{
    // Respawn the owl at the starting position
    owlX = -kOwlSpriteRatio; // Start owl offscreen on the left
    owlY = random(SCREEN_ORIGIN_Y, SCREEN_HEIGHT - kOwlSpriteRatio);
    owlAlive = true;

    bullets = totalBullets;
}

void SpriteRenderer::renderIntro(int sessionId)
{
    // Clear screen
    background.fillSprite(TFT_BLACK);
    background.pushSprite(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y);

    tft.drawString("HOOT PURSUIT", 75, 30, 4);
    tft.drawLine(40, 75, 285, 75, TFT_WHITE);
    if(sessionId) {
        tft.drawString("SESSION-ID : " + String(sessionId), 110, 120, 2);
    } else {
        tft.drawString("Unable to connect retrying..." , 80, 120, 2);
    }

    tft.drawString("Enter the above session id into the web portal", 13, 200, 2);
}

void SpriteRenderer::renderCountdown()
{
    background.fillSprite(TFT_BLACK);
    background.pushSprite(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y);
    
    int countdown = 3;
    while (countdown > 0)
    {
        // Alternate background color
        uint16_t bgColor = (countdown % 2 ? TFT_BLACK : TFT_WHITE);
        uint16_t textColor = (countdown % 2 ? TFT_WHITE : TFT_BLACK);

        background.fillSprite(bgColor);
        
        // Set the text color to the opposite of the background color
        background.setTextColor(textColor);

        // Convert countdown to a character ('3', '2', '1') and display it
        background.drawString(String(countdown), 150, 110, 6);

        countdown--;

        // Push the updated sprite to the screen
        background.pushSprite(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y);
        vTaskDelay(TIMEOUT_DELAY / portTICK_PERIOD_MS);
    }
}


void SpriteRenderer::renderHighscores(JsonDocument highscores)
{
    background.fillSprite(TFT_BLACK);
    background.pushSprite(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y);

    // Render highscores on page
    tft.drawString("HIGHSCORES", kHighscoreTitleX, kTitleY, kTitleFontSize);
    int y = kInitialY;
    for (JsonObject obj : highscores.as<JsonArray>()) {
        const char* name = obj["name"];
        const int score = obj["score"];

        tft.drawString(String(name) + " : " + String(score), kNameX, y, kFontSize);
        y += kYIncrement;
    }

    vTaskDelay(HIGHSCORE_KEEPALIVE / portTICK_PERIOD_MS);
}

bool SpriteRenderer::renderEndScreen(bool useGyro)
{
    background.fillSprite(TFT_BLACK);
    background.pushSprite(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y);
    createCursorSprite();

    // Add buttons for Keep Playing and End Session
    bool keepPlaying = false;
    bool optionChosen = false;
    startCursorTime = millis();

    g.setTriggerPressed(false); // Prevent buffered input
    while(!optionChosen)
    {
        background.fillSprite(TFT_BLACK);
        background.drawRect(kEndButtonOriginX, kEndButtonOriginY, kButtonWidth, kButtonHeight, TFT_RED);
        background.drawRect(kPlayButtonOriginX, kPlayButtonOriginY, kButtonWidth, kButtonHeight, TFT_GREEN);
        background.drawString("Play Again!", kPlayButtonTextOriginX, kButtonTextOriginY, kButtonTextFontSize);
        background.drawString("End Session", kEndButtonTextOriginX, kButtonTextOriginY, kButtonTextFontSize);

        updateCursorPosition(x, y, false);

        if(g.getTriggerPressed())
        {
            if(x > SCREEN_WIDTH / 2){
                keepPlaying = true;
            } else {
                keepPlaying = false;
            }
            optionChosen = true;
        }
        
        background.pushSprite(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y);
    }

    return keepPlaying;
}

void SpriteRenderer::updateTextElement(TFT_eSprite &text, const TextSpriteSettings &settings, String content)
{
    text.setTextColor(TFT_WHITE,TFT_BLACK);
    text.fillSprite(TFT_BLACK);
    text.drawString(content, SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, settings.fontSize);
    text.pushToSprite(&background, settings.posX, settings.posY, TFT_BLACK);
}

void SpriteRenderer::createCursorSprite()
{
    cursor.createSprite(kCursorSpriteRatio, kCursorSpriteRatio);
    cursor.pushImage(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, kCursorSpriteRatio, kCursorSpriteRatio, kCursorSprite);
}