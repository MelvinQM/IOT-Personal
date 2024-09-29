# Concept & Design

## Contents
- **[1. Concept](#1-concept)**
  - **[1.1 User Needs](#11-user-needs)**
  - **[1.2 Product Requirements](#12-product-requirements)**
  - **[1.3 Console Concepts](#13-console-concepts)**
  - **[1.4 Controller Concepts](#14-controller-concepts)**
- **[2. Design](#2-design)**
  - **[2.1 Software Decisions](#21-software-decisions)**
    - **[2.1.1 Fusion360](#211-fusion360)**
    - **[2.1.2 Fritzing](#212-fritzing)**
    - **[2.1.3 Aseprite](#213-aseprite)**
  - **[2.2 Prototypes](#22-prototypes)**
    - **[2.2.1 First Prototype Model/Print](#221-first-prototype-modelprint)**

## 1. Concept
The concept for my project is to make a game similair to Duck Hunt. Where the player will be provided a controller and a display. Instead of using the traditional way I will be trying to put my own spin on it. The traditional way is by using an optical sensor in the gun/controller that when pressed will see if it is pointing at a portion of the screen that's white. Also the moment the controller is pressed the whole screen goes black except for the target/duck. The moment the screen flickers and the sensor sees a white spot on the screen it has hit a duck. 
<div align="center">
  <img src="/../assets/images/cursor_concept.png" alt="cursorconcept">
  <img src="/../assets/images/product_concept.png" alt="productconcept">
</div>

I wanted to put my own spin on it. The controller will have a gyroscope in it allowing it to serve as a motion controller. Similair to the Wii but not exactly as the wii uses a different technique. I wish to emulate the easy of use of the Wii controller but using a different technique.

Additionally the controller will be wireless and communicate with the display through a bluetooth connection. This will allow the controller to tell the display where to move the cursor.

### 1.1 User Needs
- **Inclusive Age Range**: The system should cater to users of all ages, from retro game enjoyers of old to young kids.
- **Ease of Use**: The system must be simple to operate for users of different experience levels.
- **Fun Factor**: The primary goal is to ensure that the gaming experience is enjoyable for everyone.
- **Non-Violent Design**: The controller design should avoid looking violent. It must not resemble a traditional gun.
- **Comfortable Grip**: The handle of the controller must be appropriately sized to accommodate users of all ages and hand sizes.


### 1.2 Product requirements
1. Setup Time
    - **Specific**: Users must be able to set up the game console with clear, step-by-step instructions.
    - **Measurable**: Setup should take no longer than 10 minutes from off to operational state.
    - **Achievable**: Instructions will include visual aids and step-by-step instructions.
    - **Relevant**: This ensures user satisfaction and a positive first experience.
    - **Time-bound**: The setup process should be tested and validated within the ten weeks of development.

2. Controller Design
    - **Specific**: The controller design must be non-violent and visually appealing to a broad demographic.
    - **Measurable**: Conduct surveys with at least 5 potential users to get optinions on appeal and ensure it resonates with all ages.
    - **Achievable**: There will be multiple iterations on concepts based on feedback within the 10 week development time.
    - **Relevant**: This is crucial for players across age groups.
    - **Time-bound**: Final design will be completed within 10 weeks.

2. Ergonomic Comfort
    - **Specific**: The wireless controller should be easy to hold for both children and adults.
    - **Measurable**: User testing with a sample size of at least 5 individuals across different age groups to assess comfort levels on a 1-10 scale.
    - **Achievable**: Feedback will be collected and incorporated into the design in two iterations over a four-month period.
    - **Relevant**: Comfort is important for user satisfaction and prolonged playtime.
    - **Time-bound**: Comfort assessments will be conducted within the initial 10 weeks of development.

4. Bluetooth Connection Stability
    - **Specific**: The controller must maintain a stable Bluetooth connection to the display.
    - **Measurable**: The connection must not drop within a 10-meter range during continuous gameplay for at least 95% of the time.
    - **Achievable**: Testing in various environments to ensure reliability.
    - **Relevant**: A stable bluetooth connection is essential for a smooth gaming experience.
    - **Time-bound**: Connection stability testing should be completed by the end of the development within 10 weeks.


### 1.3 Console concepts

### 1.4 Controller concepts
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

### 2.2 Prototypes
#### 2.2.1 First prototype model/print
This model was to create a basic shape for the controller. 
<div align="center">
  <img src="/../assets/images/fusion-controller-prototype1.png" alt="fusion-controller-prototype">
</div>
I then moved around all components around to see if everything would fit. *(This did not include the trigger yet so the spacing might not be correct here)*
<div align="center">
  <img src="/../assets/images/fusion-inside-controller.png" alt="inside-controller">
</div>

This print was mostly to get a feeling of the size of the controller to see if everything would fit the way I expected from inspecting it in the CAD.
<div align="center">
  <img src="/../assets/images/first-print.jpg" alt="first-print">
</div>
Some adjustments that were quite obvious right away was the thickness of the model. 1mm was quite thin and fragile. Increasing the shell of the model to 2mm makes it a lot more robust. This does take some space away from the components inside the model.

Next I worked on the design for the trigger button. I opened up a wii controller to see how this was done here. I noticed that the button was loose and was connected using a T join see picture below.
<div align="center">
  <img src="/../assets/images/wiicontrollerinside.jpg" alt="wiicontrollerinside">
</div>


This joint allows the button to move up and down to press a button. I worked on making a system similair to this. I changed the button to have a sharper edge to allow for easier shooting. The wii controller has a softer edge which could lead to your finger sliding off easier when rapid firing.

<div style="display: flex; justify-content: center; align-items: center;">
  <img src="/../assets/images/trigger-design.png" alt="trigger-design" style="width:50%">
  <img src="/../assets/images/trigger-fusion-model.png" alt="trigger-fusion-model" style="width:50%">
</div>
