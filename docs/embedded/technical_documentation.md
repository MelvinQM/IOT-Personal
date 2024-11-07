# Technical documentation

## Contents
- **[1. Basic Concept](#1-basic-concept)**
    - **[1.1 Outputs](#11-outputs)**
    - **[1.2 Inputs](#12-inputs)**
    - **[1.3 Extra Components](#13-extra-components)**
    - **[1.4 Component List](#14-component-list)**
- **[2. Bill of Materials](#2-bill-of-materials)**
- **[3. Project Wiring Diagram](#3-project-wiring-diagram)**
- **[4. Components](#4-components)**
    - **[4.1 MPU6050](#41-mpu6050)**
    - **[4.2 ESP32-2432S024 (Display & Led)](#42-esp32-2432s024)**
    - **[4.3 Joystick](#43-joystick)**
    - **[4.4 Button](#44-button)**
    - **[4.5 DC-DC Multi-Output Buck-converter](#45-dc-dc-multi-output-buck-converter-33v5v9v12v)**



## 1. Basic Concept
This project will be an Embedded system take on the game Duck Hunt. This project has as requirement 3 outputs and 3 inputs. The goal is to make a wireless controller capable of moving a digital cursor on a screen.

### 1.1 Outputs
- A ESP32 powered Display
- RGB Led which will display the status through color.
- A Rumble pack in the controller for extra satisfying game feedback.

### 1.2 Inputs
- Gyroscope that will serve as the means of calculating where the cursor on screen should be pointing
- Fire button (This will be a button on the controller which will trigger the fire function of the game).
- Joystick to function as a secondary input for controlling the cursor on screen.

### 1.3 Component list
Below all components are specified for both the console and the controller. The components marked extra are only added if enough time is presented as they are not as important.

- Console
    - External power source (Extra)
        - Power switch (Extra)
    - Display
        - Onboard RGB Led
    - Speaker / Buzzer (Extra)

- Controller
    - External power source / 9v Battery
        - Power Switch (Extra)
        - DC - DC Converter
    - Gyroscope
    - Joystick
    - Trigger button
    - Vibration Motor

## 2. Bill of materials

A Bill of Materials (BOM) is a all encompassing list of parts, materials, and components required to build or assemble a product. It serves as a blueprint/shopping list for all the necessary materials and allows potential builders of this project to ensure all components are available before starting the project.

Below is the table that outlines the necessary parts for this project:

|**Part**|**Manufacturer**|**Description**|**Quantity**|**Price (incl VAT)**|**Subtotal (incl VAT)**|**URL**|
|-|-|-|-|-|-|-|
|MPU6050|Invensense|6 Axis gyroscope & Accelerometer|1|€8,50|€8,50| [Tinytronics](https://www.tinytronics.nl/nl/sensoren/acceleratie-rotatie/mpu-6050-accelerometer-en-gyroscope-3-axis-module-3.3v-5v)|
|ESP32-2432S024 Display |Guition |ESP32 Lvgl/Tft Lcd Display Development Board 240*320 2.4Inch|1|€17,99|€17,99| [Aliexpress](https://nl.aliexpress.com/item/1005005865107357.html?spm=a2g0o.order_list.order_list_main.60.7df579d2ajZa7L&gatewayAdapt=glo2nld)|
|ESP32-S3|Top Tech Store|ESP32-S3 Development Kit Module|1|€6,39|€6,39| [Aliexpress](https://nl.aliexpress.com/item/1005007310769585.html?src=google&pdp_npi=4%40dis%21EUR%217.22%212.32%21%21%21%21%210.9282%40%2112000040197381496%21ppc%21%21%21&src=google&albch=shopping&acnt=708-803-3821&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&gclsrc=aw.ds&&albagn=888888&&ds_e_adid=&ds_e_matchtype=&ds_e_device=c&ds_e_network=x&ds_e_product_group_id=&ds_e_product_id=nl1005007310769585&ds_e_product_merchant_id=5321504273&ds_e_product_country=NL&ds_e_product_language=nl&ds_e_product_channel=online&ds_e_product_store_id=&ds_url_v=2&albcp=19207327905&albag=&isSmbAutoCall=false&needSmbHouyi=false&gad_source=1&gclid=Cj0KCQjwpP63BhDYARIsAOQkATbpjDElRXK1qK98sC1XfxLuWsL4ofrS9Beu_nlAQvX9LkUJKmlZxioaAhaxEALw_wcB#nav-specification)|
|Vibration Motor|DIY Victor|Pwm Vibration Motor, Dc Motor|1|€1,28|€1,28|[Aliexpress](https://nl.aliexpress.com/item/1005006296840332.html?spm=a2g0o.order_list.order_list_main.41.ad5779d2DKfbb1&gatewayAdapt=glo2nld#nav-store)|
|DC-DC Converter 9v-5v |DFRobot|DFRobot DC-DC Multi-uitgang Buck-converter (3.3V/5V/9V/12V)|1|€5,99|€5,99|[Robotshop](https://eu.robotshop.com/nl/products/dfrobot-dc-dc-multi-uitgang-buck-converter-33v-5v-9v-12v)|
|Joystick Module|DIY TZT|Dual-Axis X/Y Joystick Module|1|€3,65|€3,65|[Aliexpress](https://nl.aliexpress.com/item/1005005985509291.html?spm=a2g0o.order_list.order_list_main.65.7df579d2X1lPCn&gatewayAdapt=glo2nld)|
|9V Battery|Varta|Long life max power 9V battery Alkaline|1|€3,79|€3,79|[Amazon](https://www.amazon.nl/Varta-4722-Batterijenideaal-brandmelder-stemapparaat/dp/B004WYN62O/ref=sr_1_7?__mk_nl_NL=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=1NYFQ5IK92CUI&dib=eyJ2IjoiMSJ9.s1hD60Ugo8pFFMPi4fvoNZ59OwH-o_S1I4o9JsPUSHyDJ4NbpOYfVZnNHxP1QVZqb02I-TrhUwM3D6Y7oElVe95_1rdtP96RLEHU7P_MPrtS64pPSoUp1ggzHNXBL_nAN95F4rNVTyWkDFQUmAKZUOXgrZo8OsK0837OatbVtaMupwxCpH2rJNnSAo1bOxpgtx3GtcPe0Fmf4thD5WZfPcVRbbDy0F_2p2I9TO9kPbDHQAnhaOe5zitPXqGgBbqFZmmwTYJCuYCDscReUmFzQXssVf4He2TrEqaO8Dvx3uY.jeb0MqclxsMAGyEBeiUkCezzQBYqjW2fsNd-cYCOJWc&dib_tag=se&keywords=9v+battery&qid=1729798531&sprefix=9v+battery%2Caps%2C76&sr=8-7)|


## 3 Project wiring diagram
The wiring diagram was created using Fusion360 Electronics. The components were created using a mix of custom made symbols in Fusion360 and some edited versions taken from [SnapEDA](https://www.snapeda.com). All fusion electronics files can be found in docs/assets/diagrams/FusionElectronics/...

A wiring diagram is a visual representation of an electrical circuit, showing the connections between different components. It uses standardized symbols to represent elements like power sources, switches, resistors, and wires. This diagram is useful for understanding how electricity flows through the circuit.

<img src="/../assets/diagrams/FusionElectronics/ControllerWiringDiagram.png" alt="ControllerWiringDiagram">

***As the console has no wiring involved no wiring diagram is needed. The console only needs to be connected to power using a USB-C cable.***

## 4. Components
### 4.2 MPU6050 

<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    <div>
      The MPU is a 6 axis gyroscope and accelerometer. It retrieves data from rotating and moving the component.
      This data can be quite fluctuating and not very precise. The MPU has a built in way of dealing with this called the DMP "Digital Motion Processor".
      This processor runs so called fusion algorithms internally allowing the ESP to receive clean and reliable "fused" motion information. More about this can be read in <a href="https://techexplorations.com/guides/arduino/peripherals/mpu6050/">this article</a>
    </div>
    <br>
    <div>
      The angles of the MPU can be defined using YAW PITCH and ROLL. A visual respresentation of this can be seen in the image shown.
    </div>
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/components/mpu6050.jpg" alt="MPU6050" width="50%">
    <img src="/../assets/images/yawpitchroll.png" alt="MPU6050" width="50%">
  </div>
</div>


### 4.3 ESP32-2432S024
#### 4.3.1 ESP32-2432S024 (ESP Display)
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    The ESP32-2432S024 or how it will be called for ease of reading the ESP Display is a 2.4 inch display with a resolution of 320x240. This display allows for full color display and touchscreen support. This display has an ESP32 onboard which allows the user to not have to wire anything to communicate from the esp to the display. This board also exposes some extra GPIO pins.

    To use the display a library is required called TFT_eSPI a important fact for using this library is that the library needs to configured before use. This is done by changing the User_Setup.h to use the correct pins and settings. This was all found in the user manual. Provided from the store page which can be found in the [BOM](#2-bill-of-materials)
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/components/display-dimensions.png" alt="rawmpudata" style="width: 75%; height: auto;">
  </div>
</div>


#### 4.3.2 RGB LED
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
  	The ESP32-2432S024 besides a display also has a RGB led allowing a broad range of colored light to be displayed. This allows the system to display a certain condition through a color indication.

    This Led is used to show certain conditions of the system.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/components/rgbled.png" alt="rawmpudata" style="width: 75%; height: auto;">
  </div>
</div>

### 4.4 Joystick
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    The joystick consists of 2 potentiometers one for the x axis and one for the y axis. This allows for 2d coordinate to be determined which in turn can be used for the cursor on screen. The joystick serves as an alternative to using gyro data. The joystick also has a click function so it also serves as a button.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/components/joystick.png" alt="rawmpudata" style="width: 75%; height: auto;">
  </div>
</div>

### 4.5 Button
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    A simple button is also used to be used as the "fire" button and as a general action button. This button simply gives a signal to a connected GPIO pin.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/components/button.png" alt="rawmpudata" style="width: 75%; height: auto;">
  </div>
</div>

### 4.5 Vibration Motor
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    The vibration motor serves as a way to provide a feedback to the player when pressing the trigger button. This motor is controlled through the use of a PWM signal. This allows differing levels of vibration to be achieved. The motor must be placed in a way where it is against a wall of the controller to allow for more vibrations to pass through.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/components/vibration-motor.png" alt="rawmpudata" style="width: 75%; height: auto;">
  </div>
</div>


### 4.6 DC-DC Multi-Output Buck-converter (3.3V/5V/9V/12V)
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    This DC-DC stepdown converter serves as the power management for the controller. This component allows the controller to be powered through the use of a 9v battery. The 9 volts is brought down to 5 volts which is able to power an ESP32-S3.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/components/dc-dc.png" alt="rawmpudata" style="width: 75%; height: auto;">
  </div>
</div>
