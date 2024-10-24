/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: The main program file for the motion controller project. It initializes the 
 * Serial communication and the MotionController instance. The loop function continuously runs the 
 * motion controller's main loop.
 * License: This project is licensed under the MIT License.
 */

#include "motion_controller.h"

MotionController controller;

void setup() 
{
  controller.init();
}

void loop() 
{
  controller.loop(); 
}