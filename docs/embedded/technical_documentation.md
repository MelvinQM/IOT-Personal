# Technical documentation

Your Wiring Diagram, Bill of Materials, ... everything about how you built your embedded device should be documented here.

<br>

## Basic Concept
This project will be a Embedded system take on the game Duck Hunt. This project has as requirement 3 outputs and 3 inputs. 

<br>

### Outputs
- Display that will be either a monitor or a small LED display.
- A Rumble pack in the controller for extra satisfying game feedback.
- Buzzer/Speaker that will be used to generate various sound effects and music.

### Inputs
- Gyroscope that will serve as the means of calculating where the cursor on screen should be pointing
- Fire button (This will be a button on the controller which will trigger the fire function of the game).
- On/Off Switch (This will allow the controller to be turned on and off).

<br>

### Component list
- Console
    - External power source (Optional)
        - Power switch
    - Display
    - Speaker / Buzzer

- Controller (Gun)
    - External power source
        - Power Switch
    - Gyroscope
    - Trigger button
    - Rumble Pack

<br>

## Bill of materials

<br>

## Wiring Diagrams

### Project wiring diagram
The diagram for connecting the entire project:

TODO:

<br>

### Individual component wiring diagrams

#### MPU6050 
To connect the MPU6050 which is a gyroscope to measure 3 axis angles and 3 axis accelerations.
<div align="center">
  <img src="/../assets/images/MPU6050-diagram.png" alt="MPU6050">
</div>

The angles are defined as the following:
<div align="center">
  <img src="/../assets/images/yawpitchroll.png" alt="MPU6050">
</div>

<br>
