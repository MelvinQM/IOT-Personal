#include "game.h"

Game::Game()
{

}

Game::~Game()
{
  
}

void Game::Init()
{
    Serial.println("----[Initializing Game]----");
    api.Init();
    //gyro.Init();
}

void Game::Run()
{

}
