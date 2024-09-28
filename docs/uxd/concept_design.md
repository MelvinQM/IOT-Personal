# Concept & Design
## 1. Market Research

### 1.1 Intro
During my Minor in Internet of Things I was tasked with making an IoT device. There were some "blueprints" that I could choose from. I ended up choosing the game console blueprint. This blueprint involved creating an Embedded device which would serve as the game. This device needed to connect to an API which handled storing data from sensors and possibly from the game itself into a database. This data has to than be shown on a frontend website. This was the bare minimum required for the project. 

One of my first ideas was to make some sort of motion controller. This idea seemed like a fun project as I could easily introduce new games and functionalities to the controller later on. This controller primarily revolves around a trigger/button that could invoke a reaction on screen and a gyroscope to handle the movement of a digital cursor on screen. The basic idea of having a controllers gyroscopic angles being able to control a cursor on screen is a very expandable idea and made for a perfect route to take my project. The game that fits this gameplay the best is Duck Hunt.


### 1.2 Research question
To start out with I wanted to look into some concepts for my game console project. I needed to think of an idea that could be reasonably made in 10 weeks time.
I started looking at some known items on the market. I wanted to make a game console with no need of connecting it to a computer. Unless it was for statistics on a website. My initial thought was that I wanted to make a game inspired by Duck Hunt.

This led to the creation of some questions to be researched with the main question being:
**What is a realistic design for a game console that makes use of a motion controller that can move a digital cursor on an embedded device screen**
Additionally some sub questions:
- What are some existing motion controller designs on the market?
- What are some displays that can be used to create a game console screen?
- What are techniques that can be used to communicate between the controller and the console?
- What are some design choices that would make the controller more accessible to all audiences? 

### 1.3 Research method


### 1.4 Implementations and results
#### 1.4.1 Existing motion controllers on the market.
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

#### 1.4.2 What are some displays that can be used to create a game console screen?

#### 1.4.3 What are techniques that can be used to communicate between the controller and the console?

#### 1.4.4 Existing motion controllers on the market.

#### What are some design choices that would make the controller more accessible to all audiences? 



### 1.5 Conclusion




### 1.6 Reccomendations



### 1.7 References
1. Simon Whistler. *How the Gun on the Original Duck Hunt Worked*. Channel: Today I Found Out, Year. [Link](https://www.youtube.com/watch?v=cu83tZIAzlA&t=72s&ab_channel=TodayIFoundOut).
2. TheChiptide. *How did the Wii Remote Actually Work?*. Channel: TheChipTide. [Link](https://www.youtube.com/watch?v=WZUibjOXMqI&ab_channel=TheChiptide).
3. Wikipedia contributors. *Duck Hunt*. Wikipedia, [Link](https://en.wikipedia.org/wiki/Duck_Hunt).
4. Wikipedia contributors. *Wii controller*. Wikipedia, [Link](https://en.wikipedia.org/wiki/Wii_Remote).



<br>
<hr>





# 2. Demographic
The demographic of people using this system would be an all ages demographic from retro game enjoyers of old to young kids. The system must be easy to use and most importantly fun. This will influence some design decisions such as the controller. The gun can't look too violent and shouldn't look like a traditional gun. Also the handle can't be too large to allow all types of people to be able to comfortably hold the controller.


# 3. Concept
The concept for my project is to make a game similair to Duck Hunt. Where the player will be provided a controller and a display. Instead of using the traditional way I will be trying to put my own spin on it. The traditional way is by using an optical sensor in the gun/controller that when pressed will see if it is pointing at a portion of the screen that's white. Also the moment the controller is pressed the whole screen goes black except for the target/duck. The moment the screen flickers and the sensor sees a white spot on the screen it has hit a duck. 
<div align="center">
  <img src="/../assets/images/cursor_concept.png" alt="cursorconcept">
  <img src="/../assets/images/product_concept.png" alt="productconcept">
</div>

I wanted to put my own spin on it. The controller will have a gyroscope in it allowing it to serve as a motion controller. Similair to the Wii but not exactly as the wii uses a different technique. I wish to emulate the easy of use of the Wii controller but using a different technique.

Additionally the controller will be wireless and communicate with the display through a bluetooth connection. This will allow the controller to tell the display where to move the cursor.

# 4. Product requirements
- The game console must be set up by users in under 15 minutes, with clear instructions provided.
- The controller's design should be non-violent and appealing to users of all ages.
- The wireless controller should be easy to hold for both children and adults, with a comfortable design.
- The controller must maintain a stable Bluetooth connection to the display within a 10-meter range.

## Controller concepts
The controller is one of the most important elements of this entire projects. Having a solid concept is essential for the project to feel complete.
Below some concepts can be seen.
<p align="center">
  <img src="/../assets/images/controller-concepts-1.png" alt="cursorconcept" width="75%">
</p>

<p align="center">
  <img src="/../assets/images/controller-concepts-2.png" alt="cursorconcept" width="75%">
</p>

An additional idea is to allow the controller to be plugged into an attachment to give it more of a gun feel. This allows the controller to be more multi purpose incase of additional games, but still allow it to be fitting for the main game being worked on.
<p align="center">
  <img src="/../assets/images/controller-concepts-attachment.png" alt="cursorconcept" width="75%">
</p>



<br>


## Design

### The first prototype
This model was mostly to get a feeling of the size of the controller to see if everything would fit the way I expted from inspecting it in the CAD.
<div align="center">
  <img src="../assets/images/first-print.jpg" alt="first-print">
</div>
<div align="center">
  <img src="../assets/images/fusion-inside-controller.png" alt="inside-controller">
</div>
Some adjustments that were quite obvious right away was the thickness of the model. 1mm was quite thin and fragile. Increasing the shell of the model to 2mm makes it a lot more robust. This does take some space away from the components inside the model.

I worked on drawing up some designs for my controller. This can be seen in the concept and design documentation.

I also started working on some prototype 3D models in fusion.
<div align="center">
  <img src="/../assets/images/fusion-controller-prototype1.png" alt="fusion-controller-prototype">
</div>

Next I worked on the design for the trigger button. I opened up a wii controller to see how this was done here. I noticed that the button was loose and was connected using a T join see picture below.

<div align="center">
  <img src="/../assets/images/wiicontrollerinside.jpg" alt="wiicontrollerinside">
</div>

This joint allows the button to move up and down to press a button. I worked on making a system similair to this. I changed the button to have a sharper edge to allow for easier shooting. The wii controller has a softer edge which could lead to your finger sliding off easier when rapid firing.

<div align="center">
  <img src="/../assets/images/trigger-design.png" alt="trigger-design">
</div>
