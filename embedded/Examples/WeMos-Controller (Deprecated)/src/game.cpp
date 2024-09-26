#include "game.h"

Game::Game()
{

}

Game::~Game()
{
  
}

void Game::Init()
{
    Serial.println("\n------------[Initializing Game]------------");
    //api.Init();
    //digitalWrite(BUTTON_PIN, LOW);
    gyro.Init();
}

void Game::Run()
{
    // if(digitalRead(BUTTON_PIN)) 
    // {
    //     Serial.println("Button pressed");
    //     api.CreatePlayer("Lucas");
    //     api.FetchPlayers();
    // }
    gyro.Loop();
    // delay(1000);        
}
