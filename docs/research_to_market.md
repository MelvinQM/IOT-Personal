# Research to market

- **[1. Introduction](#1-intro)**
- **[2. Research Question](#2-research-question)**
- **[3. Research Method](#3-research-method)**
- **[4. Implementations and Results](#4-implementations-and-results)**
- **[5. Conclusion](#5-conclusion)**
- **[6. Recommendations](#6-recommendations)**
- **[7. References](#7-references)**

## 1. Intro
During my Minor in Internet of Things I was tasked with making an IoT device. There were some "blueprints" that I could choose from. I ended up choosing the game console blueprint. This blueprint involved creating an Embedded device which would serve as the game. This device needed to connect to an API which handled storing data from sensors and possibly from the game itself into a database. This data has to than be shown on a frontend website. This was the bare minimum required for the project. 

One of my first ideas was to make some sort of motion controller. This idea seemed like a fun project as I could easily introduce new games and functionalities to the controller later on. This controller primarily revolves around a trigger/button that could invoke a reaction on screen and a gyroscope to handle the movement of a digital cursor on screen. The basic idea of having a controllers gyroscopic angles being able to control a cursor on screen is a very expandable idea and made for a perfect route to take my project. The game that fits this gameplay the best is Duck Hunt.


## 2. Research question
A question that arose during the development was how to ensure the communication between the controller and the console. This was crucical for the game feel and reliability. The following question arose from this thought:

**What is the best method for establishing efficient and reliable communication between an ESP32 display and an ESP32-S3 controller to enable smooth data transmission for a motion-controlled game?**

Subquestions:

- What are some techniques used in existing controllers?
- What techniques are available for wireless communication between two ESP32 devices?
- How can these techniques be implemented in an Arduino environment?

## 3 Research method
To answer the questions a few research methods will be used:

- Literature Review: Investigated existing motion controllers and communication methods.
- Experimental Testing: Conducted trials with different techniques to determine which was best suited for the project.
- Prototype Development: Developed a prototype for each communication method, documenting successes and challenges.

## 4. Implementations and results
### 4.1 Existing motion controllers on the market.
In hopes to answer the sub question "What are some techniques used in existing controllers?" I looked into some products that already exists.
<div style="display: flex; align-items: center;">
    <div style="flex: 1;">
        <img src="/../assets/images/duckhuntbox.jpg" alt="cursorconcept" style="max-width: 100%;">
    </div>
    <div style="flex: 1;">
        <h4>Duck Hunt Light Gun</h4>
        <p>Duck hunt was a game for the NES which made use of a so called light gun to shoot flying by ducks on screen. The game was released back in April of 1984 in Japan and later in October 1985 in America. Duck hunt's gameplay involved shooting ducks and clay pigeons. The player got 3 attempts per round to get a certain number of hits or get a gameover. </p>
        <p><span style="font-weight: bold;">Technical Details:</span>The game worked by leveraging the CRT tv technology of the time. The gun consists of a trigger and a photodiode(light sensor). When the trigger is pressed the screen will go black for one frame except for the duck. The duck would light up white causing the light sensor "if aimed correctly" to sense the duck and register it as a hit.</p>
        <p style="font-weight: bold;">Keypoints: Screen flicker, Light sensor</p>
    </div>
</div>

<br>
<hr>

<div style="display: flex; align-items: center;">
  <div style="display: flex; flex-direction: column; justify-content: center; align-items: left; width: 50%;">
      <img src="/../assets/images/wii-controller.jpg" alt="wii-controller" style="width: 50%;margin-bottom: 5%;">
      <img src="/../assets/images/wiimotionplus.jpg" alt="wiimotionplus" style="width: 50%;">
  </div>
  <div style="flex: 1;">
    <h4>Wii Motion Controller</h4>
    <p>The wii motion controller is the signature controller for the Nintendo Wii which released worldwide in 2006. The Wii controller was used for motion control games such as Wii Sports and other wii games. It allowed a digital cursor to be shown on screen based on the angle you pointed the controller at a sensor bar. It also allowed for motion controls such as registering movements such as; shaking, swinging and more.</p>
    <p><span style="font-weight: bold;">Technical Details:</span> Using 2 different systems make motion controls possible; the linear accelerometer and infrared sensor. The linear accelerometer measures the acceleration of gravity when tilted it doesnt receive the full force of gravity onto the sensor allowing to measure the tilt of the controller. It does this in 3 axis to sense the orientation of the wii remote. Later in the lifespan of the Wii the wii motion plus was introduced. This was an optional addition that cold be plugged into the wii controller. This device has a gyroscope that accomplishes a similair result as the accelerometer that is more accurate. The position of the controller relative to the screen is done using the infrared sensors. The Wii is fitted with a infrared light source known at the sensor bar. This bar has 5 infrared lights on both sides. Measuring the position of the two sources on the sensor allows the controller to be able to determine the angle the light is coming from. All of this data would then be transfered to the console through the use of Bluetooth. </p>
    <p style="font-weight: bold;">Keypoints: Accelerometer, Gyroscope, Infrared Sensor, Bluetooth</p>
  </div>
</div>


### 4.2 Techniques for wireless communication between two ESP32 devices.
In hopes to answer the sub question "What techniques are available for wireless communication between two ESP32 devices?" I looked into some products that already exists.
#### 4.2.1 Bluetooth (BLE)
To communicate between the controller and display a bluetooth connection is needed. For this project we use BLE (Bluetooth low energy). Beware of using Bluetooth classic as these are not compatible with each other. 

BLE is suited for data transfers that are more bursty and don't require high bandwith. The range of Bluetooth varies on the configuration used. From a few meters to over a kilometer. Using the FEC (Forward Error Correction) the range of a kilometer is made possible. Something to keep in mind is that range and data throughput are not mutually exclusive. For example if you go for a higher range you are reducing the max data throughput.

##### 4.2.1.1 Peripherals and Centrals
A peripheral is the device that sents out "advertisement" data to other devices to discover it. Central is the device that discovers "advertisements" and if the advertisement allows it connects to it.

##### 4.2.1.2 Advertisements and Scanning
When a peripheral sends data called advertisement packets for other devices to discover it. This could lead to discovery or simply just to let the other device read the advertisement data. The central is continously scanning advertisement channels for new advertisement packets from other devices. Some advertisement packets allow connections some are only meant to send out advertisement data.

You can expect to receive the following data from an advertisement packet (Not in all cases):

- Device name
- TX Power level (Transmit power standard BLE: 0dBm)
- Service supported by device
- Appearance ID (Identifies the type of device)

##### 4.2.1.3 Connection
To connect a device to a BLE device a few things need to happen:

- Peripheral starts advertising
- Central scanning for advertisements
- Central needs to send a connection request
- Peripheral responds
- Connection established!

##### 4.2.1.4 Services and Characteristics (Attributes)
How a BLE device organizes and structures the data that it exposes to other devices to discover it. A characteristic represents a piece of information or data that a BLE device wants to expose to other devices. An example of this is sensor data. Another example is a characteristic for allowing another device to control the behaviour of the BLE device.

A service is a grouping of one or more characteristics. Example of this having environmental data like air quality humidity and temperature all represented by a characteristic but grouped into one service called "Environmental Service".



#### 4.2.2 Wifi (UDP & TCP)
Another way of sending data between two ESP32's is by using a wifi connection. Through the use of of wifi many options are available the once looked at were UDP & TCP.

##### 4.2.2.1 UDP
Like all networking protocols UDP is a standaridzed method for transferring data between two devices in a network. UDP is comparatively a lot simpler than most protocols it sends packets (data) directly to the target device without needing a connection. The packets can arrive at a high speed but since there is no connection between the devices you are limited to a one way communication method using UDP. UDP is most used in time sensitive technologies where losing some packets is better than having to wait for the data to arrive. Some common uses for UDP consist of Video streaming, and VoIP (voice over ip) which is a internet based telephone service.

##### 4.2.2.2 TCP
Another way of sending data through a wifi connection is through the use of  TCP or Transmission Control Protocol. TCP together with another protocol namely IP internet protocol is able to send data to a sender while keeping a conneciton between the sender and receiver. The TCP/IP relationship is like sending someone a message that is written on a puzzel through the mail. The puzzle is broken into pieces and each piece then travels through a different route, some of which take longer than others. When the puzzel arrives after traveling through all these routes the packets might be out of order. TCP is then responsible for assembling the puzzle on the other side it will then make sure the order is correct, if there are any missing packets that they get resent and it lets the sender know the puzzle was received. The TCP connection cosists from the moment the first packet is sent to after the final piece is sent.

##### 4.2.2.3 UDP v TCP
The difference between UDP and TCP lies primarily in the handshake the TCP has to do. UDP packets are sent continuously without the need of this. UDP is faster but less reliable because of this. The speed of UDP also has some tradeoffs if a packet is lost in transit it will not be re-sent so for example for messages that are critical to be received this created some risk of losing that data. In the case of the data being crucial the use of TCP would be preferred.

<div align="center">
  <img src="/../assets/images/tcpvudp.png" alt="TCPvUDP" >
</div>

#### 4.2.3 ESP-NOW
##### 4.2.3.1 What is it?
ESP-NOW is a communication protocol based on the data-link layer. This reduces the layers of the OSI model from 5 to only one. This allow for data to be transmitted through through the network, transport, session, presentation, and the application layer. There is also no need for packet headers or unpackers on each layer. All of this allows for a quick response reducing the delay caused by packet loss on busy networks.

<div align="center">
  <img src="/../assets/images/espnow.png" alt="TCPvUDP" >
</div>

##### 4.2.3.2 Limitations

Althought ESP-NOW sounds perfect for the situation at hand it is important to also look at the limitations provided with using this protocol.

- **Limited Range**: The range is stated by Espressif to reach around **220 meters** under ideal conditions. However, the actual range can vary based on various interferences..
- **Interference**: ESP-NOW operates in the **2.4 GHz band**. This can cause it to experience interferences from other wireless devices and Wi-Fi networks.
- **No Message Acknowledgment**: There is no built-in acknowledgment mechanisms for confirming message delivery. If message reliability is essential, custom acknowledgements will have to be implemented.
- **Limited Data Payload**: ESP-NOW is optimized for small data transmissions, with a **maximum payload of around 250 bytes**. For applications that need high-bandwidth data transfer or larger file exchanges, services like **Arduino Cloud** might be better suited.
- **No Network Infrastructure**: ESP-NOW supports **point-to-point** and **point-to-multipoint** communication but lacks the infrastructure for building complex network topologies. If your application requires a multi-device network or Internet connectivity, consider using additional networking solutions alongside ESP-NOW.
- **Security Considerations**: While ESP-NOW offers basic data security and privacy, it is not as secure as protocols like **HTTPS** or **MQTT** with strong encryption. For projects involving sensitive data, custom security measures will need to be developed to guard against data eavesdropping and unauthorized access.
- **Compatibility**: ESP-NOW is primarily designed for **ESP8266** and **ESP32** microcontrollers. While it can be used with other ESP32-based devices, compatibility with non-ESP platforms may vary.

- What are some strategies for ensuring consistent connectivity in environments with potential interference?

### 4.3 Implementing techniques in an Arduino environment
In hopes to answer the sub question "How can these techniques be implemented in an Arduino environment?" I looked into some products that already exists.
#### 4.3.1 Bluetooth
To implement a bluetooth connection on the project first off a library to manage all the bluetooth connection was used. The library that can be used for this is is the BLE library that's in the arduino core for esp32 devices. This library allows for both client and server functionality. A bluetooth server is established on the console which a bluetooth client can connect to. This client would be in this case the controller. The controller then sends data through a characteristic allowing for data transmission.

This method seemed to work well at first but quickly issues arose when trying to use it together with a Wifi connectin. The console's screen refused to turn on when both bluetooth and wifi were running at the same time. A workaround should exist allowing for the antenna used to be shared between wifi and bluetooth but further research is required to get this functioning. The code used for this implementation can be found in `embedded/ESP32-Controller/Deprecated` for the client code and `embedded/ESP32-Display-Board/Deprecated` for the server code.

#### 4.3.2 UDP
The method used currently is the UDP method. The client code for this can be found in `embedded/ESP32-Controller/include/udp_connection.h` and `embedded/ESP32-Controller/src/udp_connection.cpp`. The server code can be found in `embedded/ESP32-Display-Board/include/connections.h` and `embedded/ESP32-Display-Board/src/connections.cpp`. The UDP method can be implemented through the use of the arduino core `Wifi.h` header and the `WiFiUdp.h` header. The console established a SoftAP which is an accesspoint with a static ip allowing for the controller to be able to connect to it without having to change any settings. The connection is able to be succesfully established the console will listen for UDP packets using. This listener listens in a fixed rate continuously. 

The controller upon connecting to the SoftAP will start sending packets containing the controller data to the console. This works decently well with some delay. A big problem that does arrise is that when sending a message such as a button click this message can get lost in the high traffic of the joystick and gyroscope data which needs to be sent at a high frequency.

#### 4.3.3 ESP-NOW


## 5. Conclusion


## 6. Reccomendations


## 7. References
1. Simon Whistler. *How the Gun on the Original Duck Hunt Worked*. Channel: Today I Found Out, Year. [Link](https://www.youtube.com/watch?v=cu83tZIAzlA&t=72s&ab_channel=TodayIFoundOut).
2. TheChiptide. *How did the Wii Remote Actually Work?*. Channel: TheChipTide. [Link](https://www.youtube.com/watch?v=WZUibjOXMqI&ab_channel=TheChiptide).
3. Wikipedia contributors. *Duck Hunt*. Wikipedia, [Link](https://en.wikipedia.org/wiki/Duck_Hunt).
4. Wikipedia contributors. *Wii controller*. Wikipedia, [Link](https://en.wikipedia.org/wiki/Wii_Remote).
5. Cloudflare. *What is UDP?* [Link](https://www.cloudflare.com/learning/ddos/glossary/user-datagram-protocol-udp/)
6. Cloudflare. *What is TCP/IP?* [Link](https://www.cloudflare.com/learning/ddos/glossary/tcp-ip/)
7. NovelBits. *Master BLE Basics in Just 10 Minutes: The Ultimate Guide!* [Link](https://www.youtube.com/watch?v=JSQhRyTKnW4&ab_channel=NovelBits)
8. Espressif. *ESP-NOW* [Link](https://www.espressif.com/en/solutions/low-power-solutions/esp-now#:~:text=ESP%2DNOW%20is%20a%20wireless,ESP32%2DC%20series%20of%20SoCs.)
9. Arduino. *Device to Device Communication with ESP-NOW* [Link](https://docs.arduino.cc/tutorials/nano-esp32/esp-now/)
10. Espressif. *arduino-esp32*. GitHub [Link](https://github.com/espressif/arduino-esp32/tree/master/libraries/BLE)