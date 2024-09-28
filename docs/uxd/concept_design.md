# Concept & Design


## 1. Market Research
To start out with I wanted to look into some concepts for my project. I needed to think of an idea that could be reasonably made in 10 weeks time.
I started looking at some known items on the market. I wanted to make a game console with no need of connecting it to a computer. Unless it was for statistics on a website. My initial thought was that I wanted to make a game inspired by Duck Hunt.

<div style="display: flex; align-items: center;">
    <div style="flex: 1;">
        <img src="/../assets/images/duckhuntbox.jpg" alt="cursorconcept" style="max-width: 100%;">
    </div>
    <div style="flex: 1;">
        <h2>Duck Hunt</h2>
        <p>Duck hunt was a game for the NES which made use of a so called light gun to shoot flying by ducks on screen. The game was released back in April of 1984 in Japan and later in October 1985 in America. Duck hunt's gameplay involved shooting ducks and clay pigeons. The player got 3 attempts per round to get a certain number of hits or get a gameover. The game worked by leveraging the CRT tv technology of the time. The gun consists of a trigger and a photodiode(light sensor). When the trigger is pressed the screen will go black for one frame except for the duck. The duck would light up white causing the light sensor "if aimed correctly" to sense the duck and register it as a hit.</p>
    </div>
</div>
<br>
<div style="display: flex; align-items: center;">
    <div style="flex: 1;">
        <img src="/../assets/images/wii-controller.jpg" alt="cursorconcept" style="max-width: 100%;">
    </div>
    <div style="flex: 1;">
        <h2>Wii Motion Controller</h2>
        <p>The wii motion controller is the signature controller for Nintendo Wii which released worlwide in 2006. The wii motion controller was used to </p>
    </div>
</div>
<br>



## 2. Demographic
The demographic of people using this system would be an all ages demographic from retro game enjoyers of old to young kids. The system must be easy to use and most importantly fun. This will influence some design decisions such as the controller. The gun can't look too violent and shouldn't look like a traditional gun. Also the handle can't be too large to allow all types of people to be able to comfortably hold the controller.


## 3. Concept
The concept for my project is to make a game similair to Duck Hunt. Where the player will be provided a controller and a display. Instead of using the traditional way I will be trying to put my own spin on it. The traditional way is by using an optical sensor in the gun/controller that when pressed will see if it is pointing at a portion of the screen that's white. Also the moment the controller is pressed the whole screen goes black except for the target/duck. The moment the screen flickers and the sensor sees a white spot on the screen it has hit a duck. 
<div align="center">
  <img src="/../assets/images/cursor_concept.png" alt="cursorconcept">
</div>
<div align="center">
  <img src="/../assets/images/product_concept.png" alt="productconcept">
</div>

I wanted to put my own spin on it. The controller will have a gyroscope in it allowing it to serve as a motion controller. Similair to the Wii but not exactly as the wii uses a different technique. I wish to emulate the easy of use of the Wii controller but using a different technique.

Additionally the controller will be wireless and communicate with the display through a bluetooth connection. This will allow the controller to tell the display where to move the cursor.

## 4. Product requirements
- The game console must be set up by users in under 15 minutes, with clear instructions provided.
- The controller's design should be non-violent and appealing to users of all ages.
- The wireless controller should be easy to hold for both children and adults, with a comfortable design.
- The controller must maintain a stable Bluetooth connection to the display within a 10-meter range.

### Controller concepts
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
