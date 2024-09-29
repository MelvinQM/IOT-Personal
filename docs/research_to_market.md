# Research to market

1. **[Introduction](#1-intro)**
2. **[Research Question](#2-research-question)**
3. **[Research Method](#3-research-method)**
4. **[Implementations and Results](#4-implementations-and-results)**
5. **[Conclusion](#5-conclusion)**
6. **[Recommendations](#6-recommendations)**
7. **[References](#7-references)**

## 1. Intro
During my Minor in Internet of Things I was tasked with making an IoT device. There were some "blueprints" that I could choose from. I ended up choosing the game console blueprint. This blueprint involved creating an Embedded device which would serve as the game. This device needed to connect to an API which handled storing data from sensors and possibly from the game itself into a database. This data has to than be shown on a frontend website. This was the bare minimum required for the project. 

One of my first ideas was to make some sort of motion controller. This idea seemed like a fun project as I could easily introduce new games and functionalities to the controller later on. This controller primarily revolves around a trigger/button that could invoke a reaction on screen and a gyroscope to handle the movement of a digital cursor on screen. The basic idea of having a controllers gyroscopic angles being able to control a cursor on screen is a very expandable idea and made for a perfect route to take my project. The game that fits this gameplay the best is Duck Hunt.


## 2. Research question
To start out with I wanted to look into some concepts for my game console project. I needed to think of an idea that could be reasonably made in 10 weeks time.
I started looking at some known items on the market. I wanted to make a game console with no need of connecting it to a computer. Unless it was for statistics on a website. My initial thought was that I wanted to make a game inspired by Duck Hunt.

This led to the creation of some questions to be researched with the main question being:
**What is a realistic design for a game console that makes use of a motion controller that can move a digital cursor on an embedded device screen**
Additionally some sub questions:
- What are some existing motion controller designs on the market?
- What are some displays that can be used to create a game console screen?
- What are techniques that can be used to communicate between the controller and the console?
- What are some design choices that would make the controller more accessible to all audiences? 

## 3 Research method


## 4. Implementations and results
### 4.1 Existing motion controllers on the market.
In hopes to answer the sub question "What are some existing motion controller designs on the market?" I looked into some products that already exists.
<div style="display: flex; align-items: center;">
    <div style="flex: 1;">
        <img src="/../assets/images/duckhuntbox.jpg" alt="cursorconcept" style="max-width: 100%;">
    </div>
    <div style="flex: 1;">
        <h4>Duck Hunt Light Gun</h4>
        <p>Duck hunt was a game for the NES which made use of a so called light gun to shoot flying by ducks on screen. The game was released back in April of 1984 in Japan and later in October 1985 in America. Duck hunt's gameplay involved shooting ducks and clay pigeons. The player got 3 attempts per round to get a certain number of hits or get a gameover. </p>
        <p><span style="font-weight: bold;">Technical Details:</span>The game worked by leveraging the CRT tv technology of the time. The gun consists of a trigger and a photodiode(light sensor). When the trigger is pressed the screen will go black for one frame except for the duck. The duck would light up white causing the light sensor "if aimed correctly" to sense the duck and register it as a hit.</p>
        <p style="font-weight: bold;">Keypoints: Screen flicker, Light sensor</p>
    </div>
</div>

<br>
<hr>

<div style="display: flex; align-items: center;">
  <div style="display: flex; flex-direction: column;justify-content: center; align-items: left; width: 50%;">
      <img src="/../assets/images/wii-controller.jpg" alt="wii-controller" style="width: 50%;margin-bottom: 5%;">
      <img src="/../assets/images/wiimotionplus.jpg" alt="wiimotionplus" style="width: 50%;">
  </div>
  <div style="flex: 1;">
    <h4>Wii Motion Controller</h4>
    <p>The wii motion controller is the signature controller for the Nintendo Wii which released worldwide in 2006. The Wii controller was used for motion control games such as Wii Sports and other wii games. It allowed a digital cursor to be shown on screen based on the angle you pointed the controller at a sensor bar. It also allowed for motion controls such as registering movements such as; shaking, swinging and more.</p>
    <p><span style="font-weight: bold;">Technical Details:</span> Using 2 different systems make motion controls possible; the linear accelerometer and infrared sensor. The linear accelerometer measures the acceleration of gravity when tilted it doesnt receive the full force of gravity onto the sensor allowing to measure the tilt of the controller. It does this in 3 axis to sense the orientation of the wii remote. Later in the lifespan of the Wii the wii motion plus was introduced. This was an optional addition that cold be plugged into the wii controller. This device has a gyroscope that accomplishes a similair result as the accelerometer that is more accurate. The position of the controller relative to the screen is done using the infrared sensors. The Wii is fitted with a infrared light source known at the sensor bar. This bar has 5 infrared lights on both sides. Measuring the position of the two sources on the sensor allows the controller to be able to determine the angle the light is coming from.</p>
    <p style="font-weight: bold;">Keypoints: Accelerometer, Gyroscope, Infrared Sensor</p>
  </div>
</div>

After looking into some techniques for desiging a motion controlled game console. A decision was made to use the MPU6050 which allows for both gyroscopic and accelerometer angles. This allows the controller to be able to control a digital cursor by rotating on the vertical and horizontal axis.

### 4.2 What are some displays that can be used to create a game console screen?

### 4.3 What are techniques that can be used to communicate between the controller and the console?

### 4.4 Existing motion controllers on the market.

### 4.5 What are some design choices that would make the controller more accessible to all audiences? 



## 5. Conclusion




## 6. Reccomendations



## 7. References
1. Simon Whistler. *How the Gun on the Original Duck Hunt Worked*. Channel: Today I Found Out, Year. [Link](https://www.youtube.com/watch?v=cu83tZIAzlA&t=72s&ab_channel=TodayIFoundOut).
2. TheChiptide. *How did the Wii Remote Actually Work?*. Channel: TheChipTide. [Link](https://www.youtube.com/watch?v=WZUibjOXMqI&ab_channel=TheChiptide).
3. Wikipedia contributors. *Duck Hunt*. Wikipedia, [Link](https://en.wikipedia.org/wiki/Duck_Hunt).
4. Wikipedia contributors. *Wii controller*. Wikipedia, [Link](https://en.wikipedia.org/wiki/Wii_Remote).