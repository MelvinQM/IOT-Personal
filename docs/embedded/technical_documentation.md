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
|ESP32-S3|Espressif|ESP32-S3 Development Kit Module|1|€6,39|€6,39| [Aliexpress](https://nl.aliexpress.com/item/1005007310769585.html?src=google&pdp_npi=4%40dis%21EUR%217.22%212.32%21%21%21%21%210.9282%40%2112000040197381496%21ppc%21%21%21&src=google&albch=shopping&acnt=708-803-3821&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&gclsrc=aw.ds&&albagn=888888&&ds_e_adid=&ds_e_matchtype=&ds_e_device=c&ds_e_network=x&ds_e_product_group_id=&ds_e_product_id=nl1005007310769585&ds_e_product_merchant_id=5321504273&ds_e_product_country=NL&ds_e_product_language=nl&ds_e_product_channel=online&ds_e_product_store_id=&ds_url_v=2&albcp=19207327905&albag=&isSmbAutoCall=false&needSmbHouyi=false&gad_source=1&gclid=Cj0KCQjwpP63BhDYARIsAOQkATbpjDElRXK1qK98sC1XfxLuWsL4ofrS9Beu_nlAQvX9LkUJKmlZxioaAhaxEALw_wcB#nav-specification)|
|PWM Vibration Motor|DIY Victor|Pwm Vibration Motor, Dc Motor|1|€1,28|€1,28|[Aliexpress](https://nl.aliexpress.com/item/1005006296840332.html?spm=a2g0o.order_list.order_list_main.41.ad5779d2DKfbb1&gatewayAdapt=glo2nld#nav-store)|


### 3 Project wiring diagram
## 4. Components
The diagram for connecting the entire project:


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
  <div style="flex: 1; text-align: right; height: 25%;">
    <img src="/../assets/images/components/mpu6050.jpg" alt="MPU6050" >
  </div>
</div>

<img src="/../assets/images/yawpitchroll.png" alt="MPU6050" >



### 4.3 ESP32-2432S024
### 4.3.1 ESP32-2432S024 (ESP Display)
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    The ESP32-2432S024 or how it will be called for ease of reading the ESP Display is a 2.4 inch display with a resolution of 320x240. This display allows for full color display and touchscreen support. This display has an ESP32 onboard which allows the user to not have to wire anything to communicate from the esp to the display. This board also exposes some extra GPIO pins.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/components/display-dimensions.png" alt="rawmpudata" style="width: 75%; height: auto;">
  </div>
</div>


#### 4.3.2 RGB LED
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">

  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/components/rgbled.png" alt="rawmpudata" style="width: 75%; height: auto;">
  </div>
</div>

### 4.4 Joystick
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">

  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/components/joystick.png" alt="rawmpudata" style="width: 75%; height: auto;">
  </div>
</div>

### 4.5 Button
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">

  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/components/button.png" alt="rawmpudata" style="width: 75%; height: auto;">
  </div>
</div>

### 4.5 DC-DC Converter
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">

  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/components/dc-dc.png" alt="rawmpudata" style="width: 75%; height: auto;">
  </div>
</div>
