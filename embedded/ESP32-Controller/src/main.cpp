#include "utilities.h"
#include "MotionController.h"

MotionController controller;

void setup() 
{
  Serial.begin(115200);
  controller.Init();
}

void loop() 
{
  controller.Run(); 
}