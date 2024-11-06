# Requirements

## Contents
1. **[Embedded Requirements](#1-embedded-requirements)**
2. **[HTTP Client (EMBRQ#01)](#2-http-client-embrq01)**
3. **[HTTP Server (EMBRQ#02)](#3-http-server-embrq02)**
4. **[Inputs (EMBRQ#03)](#4-inputs-embrq03)**
5. **[Outputs (EMBRQ#04)](#5-outputs-embrq04)**
6. **[WiFiManager (EMBRQ#05)](#6-wifimanager-embrq05)**

## 1. Embedded Requirements
One of the given assignments for the minor IoT was to create an Embedde device. This device has to fulfill these 5 embedded requirements (EMBRQ):

| Requirement ID | Requirement                                                                                                                           | MoSCoW | Compliant |
|----------------|---------------------------------------------------------------------------------------------------------------------------------------|--------|-----------|
| EMBRQ#01       | The embedded device acts as a client and sends measured sensor data to the application backend over HTTP or HTTPS.                   | MUST   | YES        |
| EMBRQ#02       | The embedded device also acts as a server and receives status messages from the application backend over HTTP or HTTPS.              | MUST   | YES        |
| EMBRQ#03       | The embedded device contains at least two types of input sensors (e.g., LDR, buttons, joystick, capacitive touch, etc.).             | MUST   | YES        |
| EMBRQ#04       | The embedded device contains at least two types of visual and/or sensory outputs (e.g., LED, LED Matrix, 7-segment display, motor, servo, actuator, LCD-screen, buzzer, etc.). | MUST   | YES        |
| EMBRQ#05       | The embedded device uses the WiFiManager for configuration of SSID and password (PWD) for connecting to the network.                  | MUST   | YES        |

## 2. Accomplishments

### 2.1 HTTP Client (EMBRQ#01)
[Code Documentation](code#221-api-connection-through-wifimanager)

To fulfill the requirement of having the Embedded device serve as an HTTP client a connection with the API was established. The class defined in the Game Console `Connections.cpp` has functionality to `POST`, `PATCH` and `GET` various data. 

Methods Utilized in `Connections.cpp`:

- `fetchPlayers()`: Sends a GET request to retrieve a list of players from the API. This method returns player data that can be used to verify player existence or retrieve player statistics.
- `getSessionById()`: Sends a GET request with a specific session ID to retrieve the session details. The response includes session information, such as the session ID, associated player ID, and any other relevant session data. This method is crucial for polling until a session is associated with a player.
- `getHighscores()`: Sends a GET request to fetch the list of high scores. This method retrieves the top scores across all sessions and players, displaying leaderboard data on the game console's screen.
- `createScore()`: Sends a POST request to submit a new score to the API. This method takes the player’s score and session ID as inputs, creating a score record in the database for tracking gameplay performance.
- `createSession()`: Sends a POST request to start a new session for the game. The API responds with a session ID, which is polled until the game can confirm a valid session setup.
- `endSession()`: Sends a PATCH request to mark a session as ended. This method updates the session status, ensuring no further game actions can be recorded for that session.

createPlayer(): Sends a POST request to add a new player to the database. This method is called when a new player registers for the game, ensuring that the player data is stored for future sessions and scores.

### 2.2 HTTP Server (EMBRQ#02)
[Code Documentation](code#221-api-connection-through-wifimanager)

The requirement is achieved through continuous polling mechanisms for session and player creation.

**Session Creation**:
The device repeatedly invokes createSession() until a valid session ID is returned. This polling mechanism ensures that the game initializes with a unique session for each player.

**Session and Player Binding**:
After obtaining a session ID, the game console polls getSessionById() until the session object contains a player_id. This ensures that the game session only starts when a player has been connected through the frontend form.

Methods Utilized in `Connections.cpp`:

- `createSession()`: Initializes a new game session by sending a POST request to the API. This method is polled until a session ID is retrieved.
- `getSessionById()`: Retrieves session details, checking if a player_id has been linked to the session. Polling continues until this association is confirmed.


### 2.3 Inputs (EMBRQ#03)
To fullfill the requirement of having at least two types of input sensors (e.g. LDR, buttons, joystick, capacitive touch, etc.). I established functionality for various inputs:

- Gyroscope (MPU6050): For the use of player movement controls.
- Joystick: For the use of player movement controls.
- Button: For the use of player trigger/fire controls.

[MPU6050 code](code#23-gyroscope)

[Joystick code](code#24-joystick)

[Button code](code#25-button)


### 2.4 Outputs (EMBRQ#04)
To fullfill the requirement of having at least two types of visual and/or sensory outputs (e.g. LED, LED Matrix, 7-segment display, motor, servo, actuator, LCD-screen, etc.). I established functionality for various outputs:

- Display: For the use of a all game visuals and gameplay.
- RGB LED indicator: For the use of notifying the user and developers of the console state.
- Vibration Motor/Rumble Pack: For the use in the controller for feedback upon firing.

[Display code](code#27-sprite-rendering)

[RGB LED code](code#28-rgb-led)

[Vibration Motor code](code#26-vibration-motor)

### 2.5 WifiManager (EMBRQ#05)
[Code Documentation](code#221-api-connection-through-wifimanager)

To fulfull the requirement of having a connection to wifi through the use of WiFiManager in favor of just using `WiFi.begin()`. The use of the library WiFiManager was added. Through the use of its autoconnect feature the device will now connect automatically to any network that it remembers. If no network could be found instead of the device not functioning at all instead it will open a portal on its own accesspoint that you can join through your phone or computer. On this portal you can then add the accesspoint of your choosing.
