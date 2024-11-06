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
    - **[2.5 Button](#25-button)**
    - **[2.6 Vibration Motor](#26-vibration-motor)**
    - **[2.7 Sprite Rendering](#27-sprite-rendering)**
    - **[2.8 RGB LED](#28-rgb-led)**
    

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

[game_controller.cpp](https://gitlab.fdmci.hva.nl/IoT/2024-2025-semester-1/individual-project/nuufoowaamee68/-/blob/main/embedded/ESP32-Display-Board/src/game_controller.cpp?ref_type=heads)
[game_controller.h](https://gitlab.fdmci.hva.nl/IoT/2024-2025-semester-1/individual-project/nuufoowaamee68/-/blob/main/embedded/ESP32-Display-Board/include/game_controller.h?ref_type=heads)


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

[Controller: connections.cpp](https://gitlab.fdmci.hva.nl/IoT/2024-2025-semester-1/individual-project/nuufoowaamee68/-/blob/main/embedded/ESP32-Controller/src/connections.cpp?ref_type=heads)
[Controller: connections.h](https://gitlab.fdmci.hva.nl/IoT/2024-2025-semester-1/individual-project/nuufoowaamee68/-/blob/main/embedded/ESP32-Controller/include/connections.h?ref_type=heads)
[Console: connections.cpp](https://gitlab.fdmci.hva.nl/IoT/2024-2025-semester-1/individual-project/nuufoowaamee68/-/blob/main/embedded/ESP32-Display-Board/src/Connections.cpp?ref_type=heads)
[Console: connections.h](https://gitlab.fdmci.hva.nl/IoT/2024-2025-semester-1/individual-project/nuufoowaamee68/-/blob/main/embedded/ESP32-Display-Board/include/Connections.h?ref_type=heads)

The `Connections` class provides an interface for initializing and managing the connection for both the controller and console.
The communication between the controller console and the api is handled through WiFi. The connection from the console to the API is handled through a WiFi connection and the connection between the console and the controller is handled through the use of an Access Point and a ESP-NOW connection.

#### 2.2.1 API Connection through WiFiManager
***--Display logic--***

Using the library WiFiManager setting up a connection to a Access Point is relatively simple. 
By calling:
```cpp 
wm.autoConnect(kWifiManagerPortalName, kWifiManagerPortalPassword);
```
The system will first try to connect to any wifi connections already saved in memory. If no connection was found a portal will open. To connect to this portal you will have to connect to the hotspot created named based on `kWifiManagerPortalName`. To connect to this portal you will also need to insert `kWifiManagerPortalPassword`. In this portal you can then select the WiFi accespoint the device should connect to.

Api calls can be made by using the `makeApiCall()` function of the `connections` class.

Various methods are available to perform api calls:
- `fetchPlayers()`: Sends a GET request to retrieve a list of players from the API. This method returns player JSON data that can be used to verify player existence or retrieve player statistics.
- `getSessionById()`: Sends a GET request with a specific session ID to retrieve the session details. The response includes session information, such as the session ID, associated player ID, and any other relevant session data. This method is crucial for polling until a session is associated with a player.
- `getHighscores()`: Sends a GET request to fetch the JSON list of high scores. This method retrieves the top 10 scores across all sessions and players as a JsonDocument.
- `createScore()`: Sends a POST request to submit a new score to the API. This method takes the player’s score and session id as parameters to make this call.
- `createSession()`: Sends a POST request to start a new session for the game. The API responds with a session ID which is returned by the function.
- `endSession()`: Sends a PATCH request to mark a session as ended. This method updates the session status, ensuring no further game actions can be recorded for that session.

#### 2.2.2 ESP-NOW
***--Display and Controller logic--***

***Server Side (Console)***:

The **server side** (console) handles communication with other ESP32 devices over **ESP-NOW**. It initializes the ESP-NOW protocol, registers a peer device, and processes incoming data.

*Initialization*:

- **Wi-Fi Mode**: Set the controller to **Station mode (WIFI_AP_STA)** to send data over ESP-NOW but also be able to connect to a wifi access point.
- **Channel Setting**: Use `esp_wifi_set_channel` to set the Wi-Fi channel to ensure communication between devices on the same channel.
- **ESP-NOW Initialization**: Call `esp_now_init()` to initialize the ESP-NOW communication protocol.
- **Callback Registration**: Register a callback function (`OnDataRecv`) using `esp_now_register_recv_cb` to handle incoming data from peers.
- **Peer Registration**: Use `esp_now_add_peer()` to register the peer (motion controller) by providing the MAC address. Encryption is disabled for simplicity.

*Receiving Data*:

- The callback function `OnDataRecv` is triggered when the server receives data from the peer.
- Incoming data is parsed as JSON. Based on the method in the JSON payload (e.g., `CONTROLLER_AXIS_DATA_METHOD`, `TRIGGER_METHOD`), the server updates its state (e.g., setting gyro data, trigger state, etc.).



***Client Side (Motion Controller)***:

The **client side** (motion controller) communicates with the console using **ESP-NOW** to send data, such as gyroscope, joystick and button data.

*Initialization*:

- **Wi-Fi Mode**: Set the controller to **Station mode (WIFI_STA)**.
- **Channel Setting**: Configure the communication channel using `esp_wifi_set_channel` to match the server’s channel.
- **ESP-NOW Initialization**: Call `esp_now_init()` to initialize the ESP-NOW protocol.
- **Callback Registration**: Register a callback (`OnDataSent`) to handle the status of sent messages.
- **Peer Registration**: Provide the MAC address of the console and add the peer with `esp_now_add_peer()`.

*Sending Data*:

- The `sendData()` method is responsible for sending JSON data to the console.
- Serialize the data into a string and send it using `esp_now_send()` to the console’s MAC address.
- The controller sends different types of data (e.g., gyroscope, joystick values, trigger presses) as JSON payloads. Each method or input type is identified in the JSON payload (e.g., `CONTROLLER_AXIS_DATA_METHOD`, `TRIGGER_METHOD`).

*Example of received data*:
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


### 2.3 Gyroscope
***--Controller logic--***

[gyroscope.cpp](https://gitlab.fdmci.hva.nl/IoT/2024-2025-semester-1/individual-project/nuufoowaamee68/-/blob/main/embedded/ESP32-Controller/src/Gyroscope.cpp?ref_type=heads)
[gyroscope.h](https://gitlab.fdmci.hva.nl/IoT/2024-2025-semester-1/individual-project/nuufoowaamee68/-/blob/main/embedded/ESP32-Controller/include/Gyroscope.h?ref_type=heads)

The `Gyroscope` class provides an interface for initializing and managing the MPU6050 sensor, which includes a gyroscope and accelerometer. It handles the collection and processing of gyroscope data, including orientation in Euler angles and other sensor readings. 

- **Initialization**: The class sets up the I2C communication with the MPU6050 sensor, checks the connection, and initializes the DMP (Digital Motion Processor).
- **Data Collection**: The class collects sensor data from the MPU6050, including quaternion values, Euler angles, real and world-frame acceleration, and linear acceleration.
- **Data Processing**: It processes raw sensor data to compute screen coordinates based on gyroscope movement.
- **Interrupt Handling**: The class uses an interrupt-based system to trigger data collection when new sensor data is available.


### 2.4 Joystick
***--Controller logic--***

[joystick.cpp](https://gitlab.fdmci.hva.nl/IoT/2024-2025-semester-1/individual-project/nuufoowaamee68/-/blob/main/embedded/ESP32-Controller/src/Joystick.cpp?ref_type=heads)
[joystick.h](https://gitlab.fdmci.hva.nl/IoT/2024-2025-semester-1/individual-project/nuufoowaamee68/-/blob/main/embedded/ESP32-Controller/include/Joystick.h?ref_type=heads)

The `Joystick` class provides an interface for handling joystick input, including initialization, reading joystick axis values, and detecting button presses. It also includes methods to normalize joystick axis values to a specific range and filter out minor joystick movements (dead zone).

- **Initialization**: Sets up the joystick pins for reading input.
- **Button Detection**: Detects whether the joystick button has been pressed.
- **Axis Reading**: Reads the joystick axis values (X and Y) and normalizes them to a specific range.
- **Dead Zone Handling**: Filters out small joystick movements by applying a dead zone to the normalized axis values.
  

### 2.5 Button
***--Controller logic--***

[game_controller.cpp](https://gitlab.fdmci.hva.nl/IoT/2024-2025-semester-1/individual-project/nuufoowaamee68/-/blob/main/embedded/ESP32-Display-Board/src/game_controller.cpp?ref_type=heads)
[game_controller.h](https://gitlab.fdmci.hva.nl/IoT/2024-2025-semester-1/individual-project/nuufoowaamee68/-/blob/main/embedded/ESP32-Display-Board/include/game_controller.h?ref_type=heads)

The button handling logic in the `MotionController` class is responsible for detecting button presses, managing debounce and cooldown times, and triggering vibration feedback when the button is pressed. The button press also sends data to the console via the `sendTriggerInput()` method.

- **Button Press Detection**: Detects when the button is pressed, with debounce to prevent multiple triggers from a single press.
- **Cooldown Mechanism**: Prevents multiple button presses from being registered in quick succession by enforcing a cooldown period.
- **Vibration Feedback**: Activates the vibration motor when the button is pressed, and stops it after a predefined duration.

### 2.6 Vibration motor
***--Controller logic--***

[game_controller.cpp](https://gitlab.fdmci.hva.nl/IoT/2024-2025-semester-1/individual-project/nuufoowaamee68/-/blob/main/embedded/ESP32-Display-Board/src/game_controller.cpp?ref_type=heads)
[game_controller.h](https://gitlab.fdmci.hva.nl/IoT/2024-2025-semester-1/individual-project/nuufoowaamee68/-/blob/main/embedded/ESP32-Display-Board/include/game_controller.h?ref_type=heads)

The vibration motor logic in the `MotionController` class is responsible for providing feedback to the user when certain actions occur, such as pressing a button. The motor is controlled by activating it at full intensity (PWM) when a button is pressed and deactivating it after a set duration.

- **Vibration Activation**: The vibration motor is activated when a button is pressed, providing feedback to the user.
- **Vibration Duration**: The vibration motor remains active for a specified period, after which it is deactivated automatically.
- **Cooldown Handling**: The vibration motor logic ensures that the motor is not triggered multiple times too quickly, and it is controlled independently of the button press handling logic.


### 2.7 Sprite Rendering
***--Display logic--***

[sprite_renderer.cpp](https://gitlab.fdmci.hva.nl/IoT/2024-2025-semester-1/individual-project/nuufoowaamee68/-/blob/main/embedded/ESP32-Display-Board/src/sprite_renderer.cpp?ref_type=heads)
[sprite_renderer.h](https://gitlab.fdmci.hva.nl/IoT/2024-2025-semester-1/individual-project/nuufoowaamee68/-/blob/main/embedded/ESP32-Display-Board/include/sprite_renderer.h?ref_type=heads)

The Sprite Rendering logic in the `SpriteRenderer` class is responsible for rendering sprites on the display using the `TFT_eSPI` library. It manages the initialization of the display, rendering of sprites for the cursor, background, owl (enemy) sprites, and UI elements such as score, bullets, and owls killed. The class includes logic for sprite movement, collision detection, user input handling (via joystick or gyro), and game flow management, including different difficulty settings and game state transitions.

- **Display Initialization**: The display is initialized using the `TFT_eSPI` library, and the screen is configured for optimal use with support for rotation and byte swapping.
- **Cursor Movement and Input**: The cursor is controlled via gyro or joystick input, and its position is dynamically updated on the display. It can be used to aim and interact with the game environment.
- **Sprite Animation and Logic**: The owl sprite is animated and moves across the screen, with collision detection to check for hits. If the owl moves offscreen or is missed, it resets to a starting position.
- **Intro and Highscore Screens**: The class renders an introductory screen displaying the session ID and game instructions, and it can also display high scores by fetching data from an external JSON source.
- **End Screen and Replay Option**: At the end of the game, an end screen is displayed with options to play again or end the session, with user interaction based on cursor input.

*Gameplay*:

- **Game Loop Handling**: The class implements a flexible game loop that adapts to the current game state, ensuring smooth sprite rendering and handling owl movement, player input, and collision detection. The loop is initialized based on session settings such as difficulty levels, affecting gameplay mechanics such as speed, score per kill, and the number of bullets available for the player.
- **UI Updates**: The class updates the display to show the player's score, remaining bullets, and other game statistics, keeping the player informed about their progress.
- **Collision Detection**: Detects collisions between the cursor and the owl sprite using bounding box checks to award points for successful hits.

### 2.8 RGB LED
***--Display logic--***

[game_controller.cpp](https://gitlab.fdmci.hva.nl/IoT/2024-2025-semester-1/individual-project/nuufoowaamee68/-/blob/main/embedded/ESP32-Display-Board/src/game_controller.cpp?ref_type=heads)
[game_controller.h](https://gitlab.fdmci.hva.nl/IoT/2024-2025-semester-1/individual-project/nuufoowaamee68/-/blob/main/embedded/ESP32-Display-Board/include/game_controller.h?ref_type=heads)

The RGB LED control logic in the `GameController` class is responsible for managing the RGB LED to provide visual feedback to the user based on the game state. The LED color changes to indicate different game phases such as wifi initialization, polling and gameplay.

- **LED Initialization**: The LED is initialized with a specific pins for the Red, Green and Blue channels, allowing it to control the LED.
- **Dynamic Color Changes**: The LED color is updated dynamically to provide feedback, such as:
    - **Red** during startup.
    - **Blue** during wifi initialization.
    - **Yellow** when the game is waiting for a player to connect.
    - **Green** when the player has successfully connected and the game is in progress.
- **Brightness Control**: The LED brightness can be adjusted by modifying the intensity of the color channels.