# Technical documentation

## Contents
1. **[Basic Concept](#1-basic-concept)**
2. **[Bill of Materials](#2-bill-of-materials)**
3. **[Components](#3-components)**
    - **[3.1 Project Wiring Diagram](#31-project-wiring-diagram)**
    - **[3.2 MPU6050](#32-mpu6050)**
    - **[3.3 ESP32-2432S024](#33-esp32-2432s024)**
4. **[Bluetooth (BLE)](#4-bluetooth-ble)**


## 1. Basic Concept
This project will be a Embedded system take on the game Duck Hunt. This project has as requirement 3 outputs and 3 inputs.

### 1.1 Outputs
- Display that will be either a monitor or a small LED display.
- A Rumble pack in the controller for extra satisfying game feedback.
- Buzzer/Speaker that will be used to generate various sound effects and music.

### 1.2 Inputs
- Gyroscope that will serve as the means of calculating where the cursor on screen should be pointing
- Fire button (This will be a button on the controller which will trigger the fire function of the game).
- On/Off Switch (This will allow the controller to be turned on and off).

### 1.3 Extra components
Additionally some components could be used if there is enough time.
- A joystick for additional game control or as a backup if the gyro doesn't produce good results.
- An external power source for both the console and the controller.
- Ultrasound sensor for extra gyro calibrations (Distance between screen and player might be usefull information)

### 1.4 Component list
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

## 2. Bill of materials

A Bill of Materials (BOM) is a all encompassing list of parts, materials, and components required to build or assemble a product. It serves as a blueprint/shopping list for all the necessary materials and allows potential builders of this project to ensure all components are available before starting the project.

Below is the table that outlines the necessary parts for this project:

|**Part**|**Manufacturer**|**Description**|**Quantity**|**Price (incl VAT)**|**Subtotal (incl VAT)**|**URL**|
|-|-|-|-|-|-|-|
|MPU6050|Invensense|6 Axis gyroscope & Accelerometer|1|€8,50|€8,50| [Tinytronics](https://www.tinytronics.nl/nl/sensoren/acceleratie-rotatie/mpu-6050-accelerometer-en-gyroscope-3-axis-module-3.3v-5v)|
|ESP32-2432S024 Display |Guition |ESP32 Lvgl/Tft Lcd Display Development Board 240*320 2.4Inch|1|€17,99|€17,99| [Aliexpress](https://nl.aliexpress.com/item/1005005865107357.html?spm=a2g0o.order_list.order_list_main.60.7df579d2ajZa7L&gatewayAdapt=glo2nld)|


## 3. Components
### 3.1 Project wiring diagram
The diagram for connecting the entire project:


### 3.2 MPU6050 
#### 3.2.1 Wiring Diagram
To connect the MPU6050 which is a gyroscope to measure 3 axis angles and 3 axis accelerations.
<div align="center">
  <img src="/../assets/images/MPU6050-diagram.png" alt="MPU6050">
</div>

##### 3.2.2 Understanding the MPU6050
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

### 3.3 ESP32-2432S024
#### 3.3.1 Wiring Diagram
##### 3.3.2 Understanding the ESP32-2432S024