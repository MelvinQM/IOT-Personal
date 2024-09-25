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
|**Part**|**Manufacturer**|**Description**|**Quantity**|**Price (incl VAT)**|**Subtotal (incl VAT)**|**URL**|
|-|-|-|-|-|-|-|
|MPU6050|Invensense|6 Axis gyroscope & Accelerometer|1|€8,50|€8,50| [Tinytronics](https://www.tinytronics.nl/nl/sensoren/acceleratie-rotatie/mpu-6050-accelerometer-en-gyroscope-3-axis-module-3.3v-5v)|
|Esp32 Display 2.4Inch TFT |Guition |Esp32 Arduino Lvgl Wifi & Bluetooth Development Board 2.4 "240*320 Smart Display Scherm 2.4Inch Lcd Tft Module|1|€17,99|€17,99| [Aliexpress](https://nl.aliexpress.com/item/1005005865107357.html?spm=a2g0o.order_list.order_list_main.60.7df579d2ajZa7L&gatewayAdapt=glo2nld)|



<br>

## Project wiring diagram
The diagram for connecting the entire project:

TODO:

<br>

## Bluetooth
To communicate between the controller and display a bluetooth connection is needed. For this project we use BLE (Bluetooth low energy). Beware of using Bluetooth classic as these are not compatible with each other. 

BLE is suited for data transfers that are more bursty and don't require high bandwith. The range of Bluetooth varies on the configuration used. From a few meters to over a kilometer. Using the FEC (Forward Error Correction) the range of a kilometer is made possible. Something to keep in mind is that range and data throughput are not mutually exclusive. For example if you go for a higher range you are reducing the max data throughput.

### Peripherals and Centrals
A peripheral is the device that sents out "advertisement" data to other devices to discover it. Central is the device that discovers "advertisements" and if the advertisement allows it connects to it.

### Advertisements and Scanning
When a peripheral sends data called advertisement packets for other devices to discover it. This could lead to discovery or simply just to let the other device read the advertisement data. The central is continously scanning advertisement channels for new advertisement packets from other devices. Some advertisement packets allow connections some are only meant to send out advertisement data.

You can expect to receive the following data from an advertisement packet (Not in all cases):
- Device name
- TX Power level (Transmit power standard BLE: 0dBm)
- Service supported by device
- Appearance ID (Identifies the type of device)

### Connection
To connect a device to a BLE device a few things need to happen:
- Peripheral starts advertising
- Central scanning for advertisements
- Central needs to send a connection request
- Peripheral responds
- Connection established!

### Services and Characteristics (Attributes)
How a BLE device organizes and structures the data that it exposes to other devices to discover it. A characteristic represents a piece of information or data that a BLE device wants to expose to other devices. An example of this is sensor data. Another example is a characteristic for allowing another device to control the behaviour of the BLE device.

A service is a grouping of one or more characteristics. Example of this having environmental data like air quality humidity and temperature all represented by a characteristic but grouped into one service called "Environmental Service".

[Source](https://www.youtube.com/watch?v=JSQhRyTKnW4&ab_channel=NovelBits)

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