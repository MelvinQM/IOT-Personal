# Learning journal

## Contents
1. **[Week 1](#week-1)**
1. **[Week 2](#week-2)**
1. **[Week 3](#week-3)**
1. **[Week 4](#week-4)**
1. **[Week 5](#week-5)**
1. **[Week 6](#week-6)**
1. **[Week 7](#week-7)**
1. **[Week 8](#week-8)**
1. **[Week 9](#week-9)**
1. **[Week 10](#week-10)**

<br>

## Week 1
<hr>

Monday I was unfortunately not able to attend the lesson. In my own time I spent some time looking through all the online files about the lectures I also asked a few fellow students about the information i missed. 

I started the course setting up all seperate parts of the project and seeing if they would run. I installed all necessary programs and setup the template project. After this I started working on an ERD for a Database design.

<br>

<div align="center">
  <img src="/assets/images/ERD.drawio.png" alt="ERD">
</div>

<br>

### Feedback
**🌐 Database**

**Reviewer: Nick Schokker**

**Feedback:** looks good but in the highscore field you should add the player because you would like to know who has the highest score.

**Takeaway:** Although I ended up not using this feedback as I instead completely removed the highscore table as it was redundant due to the existence of a score table that could just be sorted.

<br>

### Feedback
**🌐 Database**

**Reviewer: Mats Otten**

**Feedback:** Without context, it's hard to say if your ERD (Entity-Relationship Diagram) is suitable for your application. However, it seems that you might not need a 'Highscore' entity if you already have a 'Score' entity. Additionally, you also have a score in the Player entity? And you also have a Shot which might also contain a Score?

**Takeaway:** Coincidentally I had already applied the above feedback but it was good to have a confirmation of the assumption that the highscore table was not needed.

<br>

### EER Diagram
After making my first draft of ERD I started designing the Database itself to show this I've made an EER Diagram.

<br>

<div align="center">
  <img src="/assets/images/EER.png" alt="EER">
</div>

<br>

### PHP Learning
I spent some time learning the basics of PHP and setting up some basic scripts. I followed this [tutorial](https://www.youtube.com/watch?v=OK_JCtrrv-c&ab_channel=freeCodeCamp.org). I was able to skip a big portion of it as it went over a lot of programming basics.

<br>

### Setting up platform.io project
For my embedded part I decided to not use the Arduino IDE and instead choose platform.io as this was more familiar for me. This also allows me to easily create multiple files and work in a more OOP fashion. Another benefit is that platform.io is an extension in vscode allowing me to work in vscode for all parts of the project.

<br>

### Environmental variabels
To run the project a file named .env is needed which includes all login details for connecting to the database. This information is something you don't want to upload to the repository that's why I worked on being able to load these in through code and exclude the .env file from being pushed to the repository.

<br>

### Documentation
This week I also worked on some documentation. I wrote documentation for my database and embedded requirements.

<br>


## Week 2
<hr>

### REST API
I worked on creating the first version of my API. I worked on this through a [tutorial](https://www.youtube.com/watch?v=X51KOJKrofU&ab_channel=DaveHollingworth) this tutorial taught me to make a simple rest API capable of performing CRUD operations with a single table. This doesn't allow for full communication with my database as of yet. It's a great start however, as it allows control over atleast the player table which is sufficient for now for testing purposes.

Additionally I added a custom http error code display using the http.cat API
<div align="center">
  <img src="/assets/images/errorcodedisplay.png" alt="errorcodedisplay">
</div>

<br>

### Frontend 
To visualise the data I worked on my frontend a bit. I added tailwindcss as i've already worked with bootstrap a lot and wanted to learn a bit more about tailwind.
<div align="center">
  <img src="/assets/images/frontend.png" alt="frontendexample">
</div>

I ended up improving the frontend by adding a scrollable table body allowing the page to not extend endlessly with the size of the tabe. Also cell border dividers were added to improve the readability.

<br>

### Feedback

**🌐 Application Code.**

**Reviewer: Lucas Hilgevoord**

**Feedback:** Please add a summary in your php code above your functions. The rest looks good! Nice to see the comments in your functions it self.

**Takeaway:** I've added comments above all functions in my API to explain more clearly what kind of parameters are expected, a summary about the function and what the function might return.

<br>

### Start of embedded device
After having a basic API up and running the start of the embedded device was next. The goal was to have a simple embedded device with a button that can trigger some API calls to test the connection between the different elements.

Result:

<div align="center">
  <img src="/assets/images/frontend.png" alt="frontendexample">
</div>

<div align="center">
  <img src="/assets/images/basicembeddeddevice.jpg" alt="basicembeddeddevice" style="width: 50%; height: auto;">
</div>

<br>


<br>

### Wifi Manager
To connect the WeMos and any other embedded device that will be needed for my project I made use of the library WiFiManager. This allows the WeMos to connect to a wifi access point without needing to hard code the SSID and password inside the code. This is more user friendly.

<br>

<div align="center">
  <img src="/assets/images/wifimanager.jpg" alt="wifimanager">
</div>

<br>

### Gyroscope

I worked on getting data from the gyroscope. The gyroscope gives me 3 axis xyz data to see the tilt of the sensor. This will be used to determine the orientation of the controller.

<div align="center">
  <img src="/assets/images/mpu-setup.jpg" alt="mpu-setup">
</div>

<br>

<div align="center">
  <img src="/assets/images/mpu-data.png" alt="mpu-data">
</div>

<br>

### Documentation
During week 2 I worked on several portions of documentation. I started with fixing some images not correctly showing up in the documentation. After this I wrote documentation explaining my API. For now this only explains the endpoints for fetching, creating, deleting and updating players. I also went around all my documentatin to add some br tags to improve readability. Finally I worked throughout the week to keep my journal up to date to prevent having to write it all in one go.

In the weekend I additionally worked on writing some documentation about working with the MPU6050.

## Week 3
<hr>

### MPU6050
Improved mpu data collection by using the [DMP](embedded/technical_documentation.md#). The data collected is now processed before being retrieved from the sensor. 
<div align="center">
  <img src="/assets/images/mpuimproveddata.png" alt="mpu-data">
</div>

<br>

### Concept sketches
To visualize the end product better I drew up some concept sketches.
<div align="center">
  <img src="/assets/images/product_concept.png" alt="product_concept">
  <img src="/assets/images/cursor_concept.png" alt="cursor_concept">
</div>

<br>

### Bluetooth

#### Bluetooth server
To connect the controller to the display in the future a form of communication was needed. I worked on setting up a bluetooth server that can receive data through a bluetooth connection.

I used the app: BluetoothLE (IOS)
<div align="center">
  <img src="/assets/images/bluetooth_data.png" alt="bluetooth_data">
</div>
<div align="center">
  <img src="/assets/images/bluetooth_app_connection.jpg" alt="bluetooth_app_connection" style="width: 25%; height: auto;">
</div>

#### Bluetooth client
To test the connectivity between the controller and the display. I established a Bluetooth client for the controller. This allows the controller to connect to the other ESP32

#### Reconnection
I also added an option to reconnect to the BT server when the device is disconnected. This wasn't working automatically before so I added this feature by making the server resume advertising after its device is disconnected.

#### Data communication
I worked on communicating between two ESP32's to send over the MPU data below is the result of this work:
<div align="center">
  <img src="/assets/images/bt-mpu-data.png" alt="bt-mpu-data" style="width: 75%;">
  <img src="/assets/images/bt-setup.jpg" alt="bt-setup" style="width: 75%;">
</div>


<br>

### Switching WeMos to ESP32-S3
The WeMos allows for a wifi connection but not a bluetooth connection. Together with some other issues I encountered I decided to switch to the ESP32-S3. This not only allows me to use bluetooth but also opens some other options such as using 2 cores, better performance and ability to connect to 5Ghz wifi channels which the WeMos could not.

### Rubrics Frontend, Backend & Database
During the course of IoT we discussed the requirements of all 3 elements. From this I learned not much from the backend and frontend side of the discussion, but I did however get reminded to normalize my database. This is good information to get reminded of and I've added this to my todo list.

### Concept design for controller
I worked on drawing up some designs for my controller. This can be seen in the concept and design documentation.

I also started working on some prototype 3D models in fusion.
<div align="center">
  <img src="/assets/images/fusion-controller-prototype1.png" alt="fusion-controller-prototype">
</div>

<div align="center">
  <img src="/assets/images/joystick-model.png" alt="joystick-model">
</div>

## Week 4

### 3D printing
I worked on a fusion model for the controller. For this I used Fusion360.
<div align="center">
  <img src="/assets/images/first-print.jpg" alt="bluetooth_app_connection">
</div>
This model was mostly to get a feelig of the size of the controller to see if everything would fit the way I expted from inspecting it in the CAD.
<div align="center">
  <img src="/assets/images/fusion-inside-controller.png" alt="bluetooth_app_connection">
</div>
Some noticeable missing components in the CAD above are:

- Trigger button
- Hole for joystick
- DC DC Converter

After reviewing my print I changed the following properties:
- Changed the shell width from 1mm to 2mm
- Moved the battery holder cutting line down but keeping the size of the battery holder.


Next I worked on the design for the trigger button. I opened up a wii controller to see how this was done here. I noticed that the button was loose and was connected using a T join see picture below.

<div align="center">
  <img src="/assets/images/trigger-design.png" alt="trigger-design">
</div>

This joint allows the button to move up and down to press a button. I worked on making a system similair to this. For now I've only made the design of the button itself. I changed the button to have a sharper edge to allow for easier shooting. The wii controller has a softer edge which could lead to your finger sliding off easier when rapid firing.

<div align="center">
  <img src="/assets/images/wiicontrollerinside.jpg" alt="wiicontrollerinside">
</div>

### Display board
I worked on setting up the display board I ordered: [Link](https://nl.aliexpress.com/item/1005005865107357.html?spm=a2g0o.order_list.order_list_main.60.7df579d2vYjQyw&gatewayAdapt=glo2nld) I encountered a lot of problems trying to get any example code to run. I looked into the most used resource for this screen through this repo: https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display. None of the example seemed to work after some research I found out my screen used a slightly different model number than the repo. The display has an onboard ESP32-2432S024 while the repo used ESP32-2432S024. A repo with resources about this model: https://github.com/NoosaHydro/2.4inch_ESP32-2432S024/blob/main/6-User_Manual/Getting%20started%202.4%20Inch.pdf. 

I followed the [User manual](https://github.com/NoosaHydro/2.4inch_ESP32-2432S024/blob/main/6-User_Manual/Getting%20started%202.4%20Inch.pdf) in the Arduino IDE to see if I could get the display running. I plan on moving over to platform.io later but the documentation was written in Arduino.

To use the display a library is required called TFT_eSPI a important fact for using this library is that the library needs to configured before use. This is done by changing the User_Setup.h to use the correct pins and settings. This was all found in the user manual.

Setup a project using the right board in my case its the "esp32dev" in arduino in platformio this would be "Espressif ESP32 Dev Module"

#### Display board fusion model
In the future an enclosure needs to be made for the display. This is why I worked on making a fusion model of the display itself. I used the official dimensions provided by the official documentation from the store page.

<div align="center">
  <img src="/assets/images/components/display-dimensions.png" alt="display-dimensions">
</div>

<div align="center">
  <img src="/assets/images/components/display-model.png" alt="display-model">
</div>

### Additional additions to display code
Later in the week I worked on writing code for the display esp32. I moved over the bluetooth code from the esp32-s3 test project. I set up the TFTeSPI library with correct configurations. This involved looking up the specifics for the display as the UserSetup.h fil had to be edited to accomodate differing screens. I made some basic sprite renderings. I added a temporary background:
<div align="center">
  <img src="/assets/sprites/background.png" alt="display-model" style= image-rendering: pixelated;">
</div>

And a cursor:
<div align="center">
  <img src="/assets/sprites/cursor.png" alt="display-model" style="width:50%; image-rendering: pixelated; filter: drop-shadow(2px 2px 5px black);">
</div>

The cursor is way too small on screen right now. I'm looking into currently if I can just resize the image in code otherwise I will just make my sprites bigger from now on.

## Week 5

### Reorganize embedded projects
Since the display arrived last week I still hadn't gotten around to moving all the code to the correct device. The WIFI/API connection was still in the controller project as this was done for testing purposes. I moved all the classes including Bluetooth and Wifi classes to the correct project.

### Removing bluetooth from project in favor for UDP
After having bluetooth and wifi running on the display I noticed that the screen wouldn't turn on anymore. I wasn't able to figure out the cause of this, but I think it's due to power consumption. Knowing this I had to make a decision since I didn't want to spend anymore time debugging this problem. I ended up ditching Bluetooth entirely in favor of using an UDP stream. The display now acts as a STA and AP which means it can connect to a wifi network but also host it's own access point. The controller connects to that access points and sends JSON formatted UDP packets which deliver any communication needed between the controller and display.

### Cursor moving
After establishing the UDP connection and parsing the data accordingly. I started working on translating the yaw, pitch and roll data from the gyroscope to logical values to move a cursor on screen. I was able to establish a satisfactory result allowing the user to now use the controller as a remote. Further improvements can be done as the gyroscope still seems to deviate slightly here and now. 

Additionally I added new sprites for the cursor to allow the user to see the sprite more easily and to allow the cursor to change to red. 