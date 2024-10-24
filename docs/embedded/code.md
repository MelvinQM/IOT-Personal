# Embedded code

## Contents
- **[1. Project Structure](#1-project-structure)**
    - **[1.1 Code conventions](#11-code-conventions)**
    - **[1.2 Platform.io](#12-platformio)**
    - **[1.3 Used Libraries](#13-used-libraries)**
- **[2. Features](#2-features)**
    - **[2.1 Game State Machine](#21-game-statemachine)**
    - **[2.2 Communication](#22-communication)**
    - **[2.3 Gyroscope](#22-gyroscope)**
    - **[2.4 Joystick](#24-joystick)**
    - **[2.5 Sprite Rendering](#25-sprite-rendering)**

## 1. Project Structure
### 1.1 Code conventions
The project is written in C++ and to format this code the use of the standard Arduino/C++ conventions were used. These conventions were used to ensure the readability and maintainability of the code. Another benefit is that most libraries follow this format so the code can be consistent.

These conventions consist of most importantly but not exclusively:

- Classes are written in `Camelcase`.
- The use of **guards** in header files is **mandatory** to prevent multiple inclusions.
- Functions and variable names are written using `camelCase`.
- Filenames should be `lowercase` and can include `dashes` or `underscores`.
- Variables declared as a const, and whose value is fixed for the duration of the program, are named with a leading "k" followed by mixed case `kUpdateSpeed` *(not mandatory)*.
- Constants defined using `#define` are written in `SCREAMING_SNAKE_CASE`.

### 1.2 Platform.io
The development environment for this project will be PlatformIO, a platform for embedded systems development. Integrated into Visual Studio Code, it simplifies building, uploading, and monitoring/debugging microcontrollers. PlatformIO supports various board types, including for example the ESP32-S3 and standard ESP32, and provides package management for libraries. The most important benefit of using Platform.io is that I found it easier to work in Object oriented program which arduino doesn't support by default.

### 1.3 Used libraries
|**Library**    | **Description**                                       | **Version** |**Environment**|**Creator**    | **Link**                                            |
|---------------|-------------------------------------------------------|-------------|---------------|---------------|-----------------------------------------------------|
|**Arduino**    |The Core framework for Arduino projects.               |arduino-esp32|All            |Arduino        |[GitHub](https://github.com/espressif/arduino-esp32) |
|**ArduinoJSON**|Library allowing for easy JSON parsing and creation.   |7.2.0        |All            |blanchon       |[GitHub](https://github.com/bblanchon/ArduinoJson)   |
|**WiFiManager**|WiFi Configuration manager with a configuration portal.|2.0.17       |Display        |tzapu          |[GitHub](https://github.com/tzapu/WiFiManager)       |
|**XPT2046**    |*Optional* library to use touchscreen functionalities. |0.0.0        |Display        |paulstoffregen |[GitHub](https://github.com/PaulStoffregen/XPT2046_Touchscreen)|
|**MPU6050**    |MPU-6050 6-axis accelerometer/gyroscope Library.       |1.3.1        |Controller     |Electronic Cats|[GitHub](https://github.com/ElectronicCats/mpu6050)  |
|**I2Cdev**     |I2C device library used in MPU6050 lib                 |0.0.0        |Controller     |jrowberg       |[GitHub](https://github.com/jrowberg/i2cdevlib)      |


## 2. Features
Features means the diverse capabilities of the system some topics will go over the implementation on both the console and controller while other topics are device specific. This is specified at the start of each topic.


### 2.1. Game statemachine
***--Display logic--***

The game that will be run on the game console. Makes use of the following state diagram as a reference for the code structure:
<div align="center">
  <img src="/../assets/images/game-statemachine.drawio.png" alt="game-statemachine.drawio">
</div>
As seen in the diagram the game can only go the next state and no differing routes are possible according to this design.

The state is saved by creating an instance of the enum GameState as seen below it starts in the Intro state.
```cpp
enum GameState
{
    Intro,
    Playing,
    EndGame,
    ShowingHighScores,
};
GameState state = Intro;
```

### 2.2 Communication
***--Display and controller logic--***

The communication between the controller console and the api is handled through WiFi. The connection from the console to the API is handled through a WiFi connection and the connection between the console and the controller is handled through the use of a Soft Access Point and a UDP stream.
#### 2.2.1 API Connection through WiFiManager
Using the library WiFiManager setting up a connection to a Access Point is relatively simple. 
By calling:
```cpp 
wm.autoConnect(kWifiManagerPortalName, kWifiManagerPortalPassword);
```
The system will first try to connect to any wifi connections already saved in memory. If no connection was found a portal will open. To connect to this portal you will have to connect to the hotspot created named based on `kWifiManagerPortalName`. To connect to this portal you will also need to insert `kWifiManagerPortalPassword`.

#### 2.2.1 UDP Connection through SoftAccessPoint
To establish the connection between console and controller the SoftAP needs to be initialized on the console first. Using the local ip, gateway ip and a network mask the access point is intialized. A hostname is then specified allowing the controller to find the AP.

The controller will attempt to connect to the AP and begin to send UDP packets containing the following json formatted data:
    jsonDoc["method"] = CONTROLLER_AXIS_DATA_METHOD;
    jsonDoc["data"]["gX"] = gData.x;
    jsonDoc["data"]["gY"] = gData.y;
    jsonDoc["data"]["jX"] = jData.x;
    jsonDoc["data"]["jY"] = jData.y;

AxisData:
```json
{
    "method": "axisData",
    "data": {
        "gX": 0.0,
        "gY": 0.0,
        "jX": 0.0,
        "gX": 0.0
    }
}
```

Upon clicking either the joystick or the trigger a packet will also be sent:

**Joystick Clicked**:
```json
{
    "method": "joystickClick",
}
```

**Trigger Pressed**:
```json
{
    "method": "trigger",
}
```

The console will receive these packets and store them in an instance of the `GameDataModel` class. This class holds all data and is created to serve as the middle man between the `SpriteRenderer` class and the `Connections` class

### 2.3 Gyroscope
***--Controller logic--***
To work with the MPU6050 first see the [wiring diagram](../technical_documentation/#321-wiring-diagram)

### 2.4 Joystick
***--Controller logic--***

### 2.5 Sprite Rendering
***--Display logic--***
