# Concept & Design

## Contents
- **[1. Concept](#1-concept)**
    - **[1.1 User Needs](#11-user-needs)**
    - **[1.2 Product Requirements](#12-product-requirements)**
    - **[1.3 Controller Concepts](#13-controller-concepts)**
    - **[1.4 Console Concepts](#14-console-concepts)**
- **[2. Design](#2-design)**
    - **[2.1 Software Decisions](#21-software-decisions)**
    - **[2.2 Controller Prototypes](#22-controller-prototyping)**
    - **[2.3 Console Prototypes](#23-console-prototyping)**

## 1. Concept
The concept for my project is to make a game similair to Duck Hunt. Where the player will be provided a controller and a display. Instead of using the traditional way I will be trying to put my own spin on it. The traditional way is by using an optical sensor in the gun/controller that when pressed will see if it is pointing at a portion of the screen that's white. This is made possible by making the screen go dark except for the duck's hitbox when pressing the trigger. The moment the screen flickers and the sensor sees a white spot on the screen it has hit a duck. 
<div align="center">
  <img src="/../assets/images/cursor_concept.png" alt="cursorconcept">
  <img src="/../assets/images/product_concept.png" alt="productconcept">
</div>

I wanted to put my own spin on it. The controller will have a gyroscope in it allowing it to serve as a motion controller. Similair to the Wii but not exactly as the wii uses a different technique. I wish to emulate the ease of use of the Wii controller but using a different technique.

Additionally the controller will be wireless and communicate with the display through an UDP connection. This will allow the controller to tell the display where to move the cursor.

### 1.1 User Needs
- **Inclusive Age Range**: The system should cater to users of all ages, from retro game enjoyers of old to young kids. This allows more people to enjoy the product and increase the amount of possible users.
- **Ease of Use**: The system must be simple to operate for users of different experience levels. Allowing an ease of access will allow more people to have fun playing the game which is the most important goal.
- **Fun Factor**: The primary goal is to ensure that the gaming experience is enjoyable for everyone. If the game is fun to play more people will be interested in attempting to play the game.
- **Non-Violent Design**: The controller design should avoid looking violent. It must not resemble a traditional gun. Since guns have a negative conotation it is essential to keep away from these kind of topics.
- **Comfortable Grip**: The handle of the controller must be appropriately sized to accommodate users of all ages and hand sizes. Allowing more people to be able to hold the controller allows for more possible players.


### 1.2 Product requirements
1. Setup Time
    - **Specific**: Users must be able to set up the game console with clear, step-by-step instructions.
    - **Measurable**: Setup should take no longer than 10 minutes from off to operational state.
    - **Achievable**: Instructions will include visual aids and step-by-step instructions.
    - **Relevant**: This ensures user satisfaction and a positive first experience.
    - **Time-bound**: The setup process should be tested and validated within the ten weeks of development.

2. Controller Design
    - **Specific**: The controller design must be non-violent and visually appealing to a broad demographic.
    - **Measurable**: Conduct surveys with at least 5 potential users to get opinions on appeal and ensure it resonates with all ages.
    - **Achievable**: There will be multiple iterations on concepts based on feedback within the 10 week development time.
    - **Relevant**: This is crucial for players across age groups.
    - **Time-bound**: Final design will be completed within 10 weeks.

3. Ergonomic Comfort
    - **Specific**: The wireless controller should be easy to hold for both children and adults.
    - **Measurable**: User testing with a sample size of at least 5 individuals across different age groups to assess comfort levels on a 1-10 scale.
    - **Achievable**: Feedback will be collected and incorporated into the design in two iterations over a four-month period.
    - **Relevant**: Comfort is important for user satisfaction and prolonged playtime.
    - **Time-bound**: Assessments will be conducted within the initial 10 weeks of development.

4. WiFi Connection Stability
    - **Specific**: The controller must maintain a stable Bluetooth connection to the display.
    - **Measurable**: The connection must not drop within a 10-meter range during continuous gameplay for at least 95% of the time.
    - **Achievable**: Testing in various environments to ensure reliability.
    - **Relevant**: A stable connection is essential for a smooth gaming experience.
    - **Time-bound**: Connection stability testing should be completed by the end of the development within 10 weeks.


### 1.3 Controller concepts
The controller is one of the most important elements of this entire projects. Having a solid concept is essential for the project to feel complete.
Below some concepts can be seen.
<div align="center">
  <img src="/../assets/images/controller-concepts-1.png" alt="cursorconcept" width="49%">
  <img src="/../assets/images/controller-concepts-2.png" alt="cursorconcept" width="49%">
</div>
<br>
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    An additional idea is to allow the controller to be plugged into an attachment to give it more of a gun feel. This allows the controller to be more multi purpose incase of additional games, but still allow it to be fitting for the main game being worked on.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/controller-concepts-attachment.png" alt="cursorconcept" width="75%">
  </div>
</div>
<br>

### 1.4 Console concepts

One of the inspirations for designing the console was from looking at existing 3d models. I came across the following model which seemed like a good fit. [Link]("https://cults3d.com/en/3d-model/gadget/fix-it-felix-jr-cabinet-with-lithophane")
<div align="center">
  <img src="/../assets/images/console-inspiration.png" alt="console-inspiration" width="75%">
</div>

The console is modeled after a classic arcade cabinet. This cabinet is modeled around the ESP32 display more about this display can be found in the [Embedded Technical Documentation](../embedded/technical_documentation.md#431-esp32-2432s024-esp-display)




### 1.5 Materials
For the purpose of designing and manufacturing a controller and console. The most important factor was being able to make a creative and functional product. This is why a 3D printed design was the most logical option. The controller can be made to have any kind of shape using 3D printing while techniques such as laser cutting would be a lot harder to make work for this purpose. 


## 2. Design

### 2.1 Software decisions

#### 2.1.1 Fusion360
- **Purpose:** Fusion360 is a cloud-based 3D CAD, CAM, and CAE tool for product design and manufacturing, enabling users to create and simulate complex models.
- **Decision for Choosing:** Chosen for its vast amount of features and prior experiences with this program.

#### 2.1.2 Fritzing
- **Purpose:** an open-source software that allows users to design and document electronic circuits, providing a platform for creating schematic diagrams and PCB layouts.
- **Decision for Choosing:** Selected for its user-friendly interface and accessibility for beginners in electronics. This software might be replaced to Fusion Electronics if designing a PCB is in the future plans as I've used Fusion for this in the past.

#### 2.1.3 Aseprite
- **Purpose:** Aseprite is a pixel art program that allows users to create 2D graphics and animations, focusing on pixel art.
- **Decision for Choosing:** A program was required to make low pixel count graphics that low memory for storing on an embedded device.

#### 2.1.4 Bambu Studio
- **Purpose:** Bambu studio is the slicer for the Bambu X1 Carbon 3d printer used in this project.
- **Decision for Choosing:** Bambu studio is the best way to interface with the X1C printer as it is the company's own 3D printing slicer specifically made to use for their printers.

### 2.2 Controller Prototyping
#### 2.2.1 Basic shape
To create the basic shape of the controller a fusion360 tutorial was used. Although this tutorial was in spanish I muted the audio and was still able to follow along quite nicely using the automatically generated subtitles. [Wii controller fusion tutorial](https://www.youtube.com/watch?v=6r9C27qcxtE&ab_channel=LuisAmaya)

This model was to create a basic shape for the controller. 
<div align="center">
  <img src="/../assets/images/fusion-controller-prototype1.png" alt="fusion-controller-prototype">
</div>
I then moved around all components around to see if everything would fit. *(This did not include the trigger yet so the spacing might not be correct here)*
<div align="center">
  <img src="/../assets/images/fusion-inside-controller.png" alt="inside-controller">
</div>


#### 2.2.2 Trigger mechanism

<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    One of the most important elements of the design was the trigger button. I opened up a wii controller to see how this was handled. I noticed that the button was loose and was connected using a T join see picture below.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/wiicontrollerinside.jpg" alt="wiicontrollerinside" width="75%">
  </div>
</div>
<br>
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    This joint allows the button to move up and down to press a button. I worked on making a system similair to this. I changed the button to have a sharper edge to allow for easier shooting. The wii controller has a softer edge which could lead to your finger sliding off easier when rapid firing.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/trigger-design.png" alt="trigger-design" width="75%">
    <img src="/../assets/images/trigger-fusion-model.png" alt="trigger-fusion-model" width="75%">
  </div>
</div>
<br>
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    After testing with this design through a few iterations a satisfying result was created to allow the trigger to press a switch. 
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/trigger-mechanism.png" alt="trigger-mechanism" width="75%">
  </div>
</div>

[Trigger prints can be found here](create_test.md#222-trigger-mechanism)

#### 2.2.3 Joystick Holder
The controller will also have a joystick on the top. To fasten this component a very simple push fit mechanism was used.
<div style="display: flex; justify-content: center; align-items: center;">
  <img src="/../assets/images/joystickholder-1.png" alt="joystickholder-1" width="50%">
  <img src="/../assets/images/joystickholder-2.png" alt="joystickholder-2" width="50%">
</div>

#### 2.2.4 Vibration Motor Holder
The vibration motor had an interesting requirement. The vibrating part had to be against a wall of the print to allow the vibrations to better travel through the plastic and to the player holding it. For that reason the motor was placed at the back facing a wall. The motor is fastened using a slide push fit mechanism.
<div style="display: flex; justify-content: center; align-items: center;">
  <img src="/../assets/images/vibrationmotorholder-1.png" alt="vibrationmotorholder-1.png" width="50%">
  <img src="/../assets/images/vibrationmotorholder-2.png" alt="vibrationmotorholder-2.png" width="50%">
</div>

#### 2.2.5 MPU6050 Holder
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    The holder for the MPU6050 was fixed to the top half of the controller and is fairly simple. The MPU has 2 holes meant for screwing it into constructions since the design did not allow for screws unless the print would be made significantly larger. This is why simple push fit "nubs" were used.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/mpuholder-2.png" alt="mpuholder-2" width="75%">
  </div>
</div>

#### 2.2.6 DC-DC Converter Holder

<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    The DC-DC converter is fastened the same way the MPU is. This similarily is fastened to the top half of the controller. Considerations were made to ensure the input of this converter was facing towards the battery cables to reduce the distance between them.
  </div>
  <div style="flex: 1; text-align: right; margin-left: 4px;">
    <img src="/../assets/images/dc-dc-holder2.png" alt="dc-dc-holder2">
  </div>
</div>


#### 2.2.7 Battery Holder

<img src="/../assets/images/batteryholder-1.png" alt="batteryholder-1" >

<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    To hold in a battery in the battery compartment, a battery lid mechanism was designed. By looking at the Wii controller as inspiration a similair mechanism was designed. This mechanism is also used in many television remotes. The basic idea is to use 2 nubs at the back to fast the lid into position first then to close it the front lid bends slightly to fit into place. Once into place it can be removed by bending this same front lid back and then pull it out.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/wii-battery-holder.jpg" alt="wii-battery-holder" width="75%">
  </div>
</div>
<br>
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    It allows for a small latch that can be openend with the use of a finger nail or a flat head screw driver or something similair. (The plastic used PLA was quite tough and doesn't bend like the traditional remote material. Using a screwdriver is reccomended because of this.)
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/batteryholder-2.png" alt="batteryholder-2" width="75%">
  </div>
</div>
<br>
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    The battery holder is fit into place using three mechanisms the latch in the front specified earlier. 2 nubs on the back to fit the lid into position.
    And a railing on the side to make sure the battery lid is positioned correctly and doesn't shift.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/batteryholder-4.png" alt="batteryholder-4" width="75%">
    <img src="/../assets/images/batteryholder-3.png" alt="batteryholder-3" width="75%">
  </div>
</div>


#### 2.2.8 Current Controller Design
<div style="display: flex; flex-direction: column;justify-content: center; align-items: center;">
  <img src="/../assets/images/currentdesign-1.png" alt="currentdesign-1">
  <img src="/../assets/images/currentdesign-2.png" alt="currentdesign-2">
</div>

#### 2.2.9 Prototype Breadboard Controller Design
To perform functionality testing the motion controller design above isn't quite optimal. As all the components take up quite a bit of space with wiring reliably testing with components can be quite the challenge. That's why the following controller design was made. It is designed to be a simpler version which can be easily open and closed. By allowing a breadboard to fit experimenting is quite a bit easier.

<div style="display: flex;">
  <img src="/../assets/images/breadboard-controller-design-1.png" alt="breadboard-controller-design-1" width=49%>
  <img src="/../assets/images/breadboard-controller-design-2.png" alt="breadboard-controller-design-2" width=49%>
</div>

The top and bottom are fitted using 4 push fit holes on the 4 corners and by using the same design for the joystick holder used for the previous motion controller 


### 2.3 Console Prototyping
I started off modeling the chosen display in Fusion360 with accurate measurements to make it easier to design a container around it.
<div align="center">
  <img src="/../assets/images/espdisplaymodel.png" alt="espdisplaymodel" width="75%">
</div>

#### 2.3.1 Basic shape
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    The basic shape of the console was created using the previous mentioned model as reference. The display has been tilted 10 degrees to allow for easier viewing from a top angle as the console will be quite small.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/consolemodel-1.png" alt="consolemodel-1" width="75%">
  </div>
</div>

#### 2.3.2 RGB Led
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    To allow the RGB led which is used as an indicator light to provide the user or developer to see the status of the system. A hole was made to allow the light to shine through the enclosure.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/consolemodel-2.png" alt="consolemodel-2" width="75%">
  </div>
</div>



#### 2.3.3 USB-C 
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    To power the system the use of a usb-c cable is required. To allow for a seamless way to plug this cable in a hole was added with enough tolerance to fit most usb-c cables.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/consolemodel-3.png" alt="consolemodel-3" width="75%">
  </div>
</div>


#### 2.3.4 Enclosure assembly
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    The enclosure is divided in two halfs. These halves connect through the use of 4 push fit nubs. By allowing for a small amount of tolerance these will allow for opening and closing of the console.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/consolemodel-4.png" alt="" width="50%">
    <img src="/../assets/images/consolemodel-5.png" alt="" width="50%">
  </div>
</div>

#### 2.3.5 Banner
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    To add some final bit of creativity to the console I added these banners. The banners are printed on its own and slides into the console. This also allows for modularity with the banners to hotswap if needed for example if a new game is able to created one day.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/consolemodel-6.png" alt="" width="50%">
  </div>
</div>

#### 2.2.8 Current Console Design
<div style="display: flex; justify-content: center; align-items: center;">
  <img src="/../assets/images/currentdesign-console-1.png" alt="currentdesign-console-1" width="33%">
  <img src="/../assets/images/currentdesign-console-2.png" alt="currentdesign-consolen-2" width="33%">
  <img src="/../assets/images/currentdesign-console-3.png" alt="currentdesign-console-3" width="33%">
</div>