/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: The main entry point for the game console application. This file initializes the GameController instance. 
 * The setup function initializes the game controller. The loop function continuously calls the game controller's loop method, 
 * which handles the main game logic and rendering.
 * License: This project is licensed under the MIT License.
 */

#include "GameController.h"

GameController game;

void setup() {
  game.Init();
}

void loop() {
  game.Loop();
}