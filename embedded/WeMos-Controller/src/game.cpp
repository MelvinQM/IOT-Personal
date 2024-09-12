#include "game.h"

Game::Game()
{

}

Game::~Game()
{
  
}

void Game::Init()
{
    Serial.println("\n----[Initializing Game]----");
    api.Init();
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    digitalWrite(BUTTON_PIN, LOW);
    // pinMode(LED_BUILTIN, OUTPUT);
    //gyro.Init();
}

void Game::Run()
{
    if(digitalRead(BUTTON_PIN)) 
    {
        Serial.println("Button pressed");
        // api.CreatePlayer("Lucas");
        api.FetchPlayers();
    }

    delay(100);        
}
