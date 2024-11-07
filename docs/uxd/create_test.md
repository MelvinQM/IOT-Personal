# Create & Test

- **[1. User Testing](#1-basic-concept)**
    - **[1.1 Effectiveness Test](#11-effectiveness-test)**
    - **[1.2 Efficiency Test](#12-efficiency-test)**
    - **[1.3 Satisfaction Test](#13-satisfaction-test)**
    - **[1.4 Test conclusions](#14-test-conclusions)**
- **[2. Manufacturing](#2-manufacturing)**
    - **[2.1 Print details](#21-print-details-slicer-printer)**
    - **[2.2 Prints](#22-prints)**



## 1. User testing

### 1.1 Effectiveness test
#### 1.1.1 Test case

***Hyptohesis***: My assumption is that the user will not encounter any errors and is able to start the game.

***Metrics***: Missclicks, Clicks, Completion rate.

***Criteria***: The test is considered a failure if the user is unable to figure out how to enter data or if the user thinks it is unclear where session information is located.

***Task 1: Enter Session ID and player name and click play***

- *Goal*: Find where to enter a console ID on the homepage and proceed to the console page.
- *Questions*: 
    - Was it clear where to enter the session ID and name?
    - Did you encounter any errors?

**Task 2: Check session details***

- *Goal*: View the session details on screen.
- *Questions*:
    - Are the details easy to read and understand?
    - Did you instantly know what this page shows?

***Task 3: Check the score table***

- *Goal*: View the session details on screen.
- *Questions*:
    - Is the score table easily found?
    - Is it clear what the score info means?

#### 1.1.2 Test results
**Task 1**:

| Participant | Was it clear where to enter the player name? | Did you encounter any errors?                 | Clicks | Missclicks |
|-------------|----------------------------------------------|-----------------------------------------------|--------|------------|
| Lucas       |  Yes                                         | No                                            | 7      | 0          |
| Nick        |  Yes very clear                              | No                                            | 4      | 0          |
| Lars        |  Yes                                         | No                                            | 5      | 0          |
| Simon       |  Yes                                         | No                                            | 6      | 0          |

**Task 2**:

| Participant | Are the details easy to read and understand?                  | Did you instantly know what this page shows? |
|-------------|---------------------------------------------------------------|----------------------------------------------|
| Lucas       | No, text is close together                                    | Yes                                          |
| Nick        | Yes except because of the font the session id is hard to read | Yes it was clear right away                  |
| Lars        | Yes maybe make the glow a bit less strong on the table header | Yes                                          |
| Simon       | Yes                                                           | No, too focused on the game console          |
| Giorgio     | Yes                                                           | Yes                                          |
| Ferdi       | Yes                                                           | Yes                                          |
| Margot      | Yes                                                           | Yes                                          |

**Task 3**:

| Participant | Is the score table easily found? | Is it clear what the score info means?  |
|-------------|----------------------------------|-----------------------------------------|
| Lucas       | Yes                              | Yes                                     |
| Nick        | Yes                              | Yes                                     |
| Lars        | Yes                              | Yes                                     |
| Simon       | Yes                              | Yes                                     |
| Giorgio     | Yes                              | Yes                                     |
| Ferdi       | Yes                              | Yes                                     |
| Margot      | Yes                              | Yes                                     |

### 1.2 Efficiency test
#### 1.2.1 Test case

***Hypothesis***: My assumption is that the game can be started under 3 minutes.

***Metrics***: Time taken, amount of clicks to completion

***Criteria***: The test is considered a failure if the game can not be started within the allocated time or the game encounters a bug causing the game to either not be started within 3 min es or not start at all.

1. *Task 1: Startup the console and view the session id provided*
    - *Goal*: Find where to enter a console ID on the homepage and proceed to the console page.
2. *Task 2: Enter Session ID and player name*
    - *Goal*: Find where to enter a session ID on the homepage.
3. *Task 3: Start playing game*
    - *Goal*: View the console which will now start the game.

#### 1.2.2 Test results

| Participant | Time taken to start game | Clicks to completion |
|-------------|--------------------------|----------------------|
| Lucas       | 21 sec                   | 7                    |
| Nick        | 25 sec                   | 4                    |
| Lars        | 23 sec                   | 5                    |
| Simon       | 26 sec                   | 6                    |
| Giorgio     | 52 sec                   | 7                    |
| Ferdi       | 47 sec                   | 8                    |
| Margot      | 65 sec                   | 8                    |


### 1.3 Satisfaction test
#### 1.3.1 Test case
***Hypothesis***: My assumption is that the Wii Controller will be liked but the breadboard controller will not.

***Criteria***: The test is considered a failure if both the controllers are considered not child friendly and not pleasant to look at.

***Questions***:

  - What is your opinion on the controller design (Both breadboard and wii controller)?
  - Do you have any additional feedback for the look of the controller?

#### 1.3.2 Test results

| Participant | Opinion on controller design (Both breadboard and wii controller)                                                                                                        | Would you say the controller looks right for all ages                                    | Additional Feedback | Notes                                                                        |
|-------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------|---------------------|------------------------------------------------------------------------------|
| Giorgio     | It would be nice if it was a little bit flatter but it was pretty comfortable. Wish the wii controller worked do I could  test it out because it feels great in my hand. | It does but it might be a little too big. The wii controller is perfect for all ages.    |       Less delay. Sounds would be nice.              |                                                                              |
| Ferdi       | Sad that the Wii controller doesn’t work, it does look like a lot of fun. Breadboard worked good and was easy to start with.                                             | Wii controller 100%, the breadboard aswell but could be a bit smaller for smaller hands. |  Fix delay, I would have definetly have the highscore if it wasn’t for the delay.        |                 |
| Margot| It looks great! Looks very proffesional|  The controller looks well suited for all ages if we are talking about the wii controller the breadboard controller might be a bit too big for children|                     | Had trouble distinguishing the game and the website causing some confusions. |

## 1.4 Test conclusions
From all the tests some conclusions can be immediately drawn. The time taken for a game to start was a lot faster than expected. The 20+ range were a lot faster as expected but no person took longer than 70 seconds. This is a good result. Some problems did arise with the breadboard controller the size seems to be a bit too big for children, but since the original plan is still to make the Wii like controller the primary design this is not a big issue. 

The delay in the controller responsiveness was a big factor for most players. Because of this the research to market focussed on looking into better ways of communicating through the controller. The testers all used the UDP method as of the time of their test. After the tests were conclucded a new protocol was introduced called ESP-NOW this had as a result that the delay was eliminated and the delay is now no longer an issue. Because of the result of these tests more attention was given to this so this helped greatly in the end product.

## 2. Manufacturing

### 2.1 Print details (Slicer & Printer)

#### 2.1.1 X1 Carbon Printer
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    The printer used in this project is the Bambu Lab's X1 Carbon. This printer together with the optional AMS system allows for multicolor high speed printing. This printer uses the Bambu studio slicer which will be talked about below.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/x1c.png" alt="x1c" width=75%>
  </div>
</div>

#### 2.1.2 Printing Material
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    The material used is PLA "Bambu Green" from bambulabs. This material is easy to print with and great for prototyping. 
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/pla.png" alt="x1c" width=75%>
  </div>
</div>

#### 2.1.3 Slicer layout
The program used to create the gcode required for the printed is Bambu Studio the program looks like this:
<img src="/../assets/images/bambustudio.png" alt="bambustudio">

#### 2.1.4 Slicer print settings
The bambustudio files can be found in this repo under assets/3d-files/bambustudio/.. These files come with the settings already setup.

The controller was printed using the following settings:



| **Part**                         | **Support Type**          | **Details**                                                                                       |
|----------------------------------|---------------------------|---------------------------------------------------------------------------------------------------|
| **Top**                          | No Support                | Default settings for printer.                                                                     |
| **Batterylid**                   | Tree Support (Manual)     | Support painting function used; only overhanging parts have tree support.                         |
| **Bottom**                       | Tree Support (Automatic)  | Threshold angle: 15°. Uses more filament to ensure controller quality.                            |
| **Trigger**                      | Tree Support (Automatic)  | Threshold angle: 20°.                                                                             |
| **Console Front**                | No Support                | Default settings for printer.                                                                     |
| **Console Back**                 | No Support                | Default settings for printer.                                                                     |
| **Console Banner**               | No Support                | Default settings for printer. (uses multicolor)                                                   |
| **Breadboard Controller Top**    | No Support                | Default settings for printer.                                                                     |
| **Breadboard Controller Bottom** | Tree support (Automatic)  | Threshold angle: 20°. Print on side and use default settings for                                  |


The banner uses multicolor to do this the color for each body in the stl can be assigned:
<img src="/../assets/images/multicolor.png" alt="bambustudiosupport">


With support the sliced file looks like this:
<img src="/../assets/images/bambustudiosupport.png" alt="bambustudiosupport">

### 2.2 Prints

#### 2.2.1 Basic Shape Controller

The first print was mostly to get a feeling of the size of the controller to see if everything would fit the way I expected from inspecting it in the CAD.
<div align="center" style="display: flex; justify-content: space-between;">
  <img src="/../assets/images/first-print.jpg" alt="first-print" width=49%>
  <video src="/../assets/videos/BasicShapePrint.mp4" controls width=49%></video>
</div>
Some adjustments that were quite obvious right away was the thickness of the model. 1mm was quite thin and fragile. Increasing the shell of the model to 2mm makes it a lot more robust. This does take some space away from the components inside the model.

#### 2.2.2 Trigger mechanism

One of the most important mechanics of the controller was the trigger to test this a small print was made. More about the inspiration for this mechanism can be found in [concept & design](concept_design.md#222-trigger-mechanism).
To test this design the trigger was printed with a seperate holder:

<div style="display: flex; justify-content: space-between;">
  <img src="/../assets/images/trigger-testprint.jpg" alt="trigger-testprint" width=49%>
  <video src="/../assets/videos/TriggerTestPrint.mp4" width=49% controls></video>
</div>

#### 2.2.3 Controller
After some iterations the whole controller was printed. The trigger can be inserted into the holder at the top of the controllers inside. Allowing it to move up and down without detaching from the controller. 
<div align="center" style="display: flex; justify-content: space-between;">
  <img src="/../assets/images/currentprint-1.jpg" alt="currentprint-1" width="49%" style="object-fit: contain; height: auto;">
  <img src="/../assets/images/currentprint-2.jpg" alt="currentprint-2" width="49%" style="object-fit: contain; height: auto;">
</div>

<div align="center" style="display: flex; justify-content: space-between;">
  <img src="/../assets/images/currentprint-3.jpg" alt="currentprint-2" width="49%" style="object-fit: contain; height: auto;">
  <video src="/../assets/videos/PrintingAll.mp4" width=49% controls></video>
</div>

To assemble the controller follow the placement of components specified in [concept & design](concept_design.md#228-current-controller-design)

#### 2.2.4 Breadboard Controller
After having issues assembling the motion controllr with all the components properly soldered and wired. An easier design was made for the purpose of testing the project.

<div align="center" style="display: flex; justify-content: space-between;">
  <img src="/../assets/images/breadboard-controller-1.jpg" alt="currentprint-1" width="49%" style="object-fit: contain; height: auto;">
  <img src="/../assets/images/breadboard-controller-2.jpg" alt="currentprint-2" width="49%" style="object-fit: contain; height: auto;">
</div>

<div align="center" style="display: flex; justify-content: space-between;">
  <img src="/../assets/images/breadboard-controller-3.jpg" alt="currentprint-2" width="49%" style="object-fit: contain; height: auto;">
  <video src="/../assets/videos/BreadboardControllerPrint.mp4" width=49% controls></video>
</div>