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

A Bill of Materials (BOM) is a all encompassing list of parts, materials, and components required to build or assemble a product. It serves as a blueprint/shopping list for all the necessary materials and allows potential builders of this project to ensure all components are available before starting the project.

Below is the table that outlines the necessary parts for this project:
| **Part**        | **Manufacturer** | **Description**                  | **Quantity** | **Price (incl VAT)** | **Subtotal (incl VAT)** | **URL**                             |
| --------------- | ---------------- | -------------------------------- | ------------ | -------------------- | ----------------------- | ----------------------------------- |
| MPU6050         | Invensense       | 6 Axis gyroscope & Accelerometer | 1            | €8,50                | €8,5 0                  | [Tinytronics](https://www.tinytronics.nl/nl/sensoren/acceleratie-rotatie/mpu-6050-accelerometer-en-gyroscope-3-axis-module-3.3v-5v) |

<br>

## Project wiring diagram
The diagram for connecting the entire project:

TODO:

<br>

## Components

#### MPU6050 
To connect the MPU6050 which is a gyroscope to measure 3 axis angles and 3 axis accelerations.
<div align="center">
  <img src="/../assets/images/MPU6050-diagram.png" alt="MPU6050">
</div>

##### Understanding the MPU6050
The angles are defined as the following:
<div align="center">
  <img src="/../assets/images/yawpitchroll.png" alt="MPU6050">
</div>

<br>

The MPU6050 will return a series of raw data if you communicate with it like so:
<div align="center">
  <img src="/../assets/images/rawmpudata.png" alt="rawmpudata">
</div>

This data is fluctuating a lot and not very precise. The MPU has a built in way of dealing with this called the DMP "Digital Motion Processor".
This processor runs so called fusion algorithms internally allowing the ESP to receive clean and reliable "fused" motion information. More about this can be read in [this article](https://techexplorations.com/guides/arduino/peripherals/mpu6050/)