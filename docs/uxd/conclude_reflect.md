# Conclude & Reflect

## 1. Product Evaluation Report

### 1.1 **Usability Assessment**

- **Product Usability**: The product is functional for the intended use, meeting most of the selected requirements defined in [Product Requirements](../concept_design#12-product-requirements). The controller and console work as expected, with reliable data transmission between the controller and the console. The interface is intuitive, allowing players to quickly engage with the game, with minimal setup needed. These results were gathered through the use of [User Tests](../create_test#1-user-testing)
- **Aesthetic and Durability Assessment**: The product appears well-designed and durable, showing potential for extended use without significant wear. The controller has a comfortable design with sufficient feedback from buttons and joystick, and the console offers clear visuals. Design considerations were made for user experience, with attention to aesthetics and robustness. The materials used for the housing are solid, though further testing on impact resistance is recommended.

### 1.2 **Visual Documentation**

**Controller**:

<div align="center">
    <img src="/../assets/images/game-controller-1.jpg" alt="game-controller-1" width="49%">
    <img src="/../assets/images/game-controller-2.jpg" alt="game-controller-2" width="49%">
</div>

<div align="center">
    <img src="/../assets/images/game-controller-3.jpg" alt="game-controller-3" width="49%">
    <img src="/../assets/images/game-controller-4.jpg" alt="game-controller-4" width="49%">
</div>

**Controller Breadboard Variant**:
<div align="center">
    <img src="/../assets/images/breadboard-controller-conclude-1.jpg" alt="breadboard-controller-conclude-1" width="49%" >
    <img src="/../assets/images/breadboard-controller-conclude-2.jpg" alt="breadboard-controller-conclude-2" width="49%" >
</div>


**Console**:

<div align="center">
    <img src="/../assets/images/game-console-1.jpg" alt="game-console-1" width="49%" >
    <img src="/../assets/images/game-console-2.jpg" alt="game-console-2" width="49%" >
</div>

**Gameplay**:

<div align="center">
    <video src="/../assets/videos/gameplay.mp4" controls alt="game-console-1">
</div>

### 1.3 **Requirements Reflection and Recommendations**
The following requirements were thought of at the start of the designing process:

1. Users must be able to set up the game console with clear, step-by-step instructions.
2. The controller design must be non-violent and visually appealing to a broad demographic.
3. The wireless controller should be easy to hold for both children and adults.
4. The controller must maintain a stable connection to the display.

All requirements were met some of these were tested through the use of [User Tests](../create_test#1-user-testing). WHile the connectivity requirement was researched through the [research to market](/../research_to_market) and experimentation. 

The only requirement which was met but also not met is "The wireless controller should be easy to hold for both children and adults.". The reason this requirement is hard to gauge is because the Wii like Controller was designed to be for this purpose but the final breadboard controller that is used at this moment was not designed with this in mind.

### 1.4 **Failure Documentation**
There were a ton of failures that were not documented but here are some that could be documented with visuals:

**Motion Controller Housing**:

**Objective**: Initial design used walls that were 1mm thick, which proved too fragile. Increasing the thickness to 2mm provided better durability.

**Issue**: The thin walls of the housing were not durable enough, leading to it feeling quite fragile.

**Solution Attempt**: The housing was redesigned with 2mm-thick walls for added strength. The layout of the internal components was adjusted to distribute stress more evenly.

**Future Approach**: If future 3D print design considerations will be done before hand on the outside wall.

**Visuals**: 
<div align="center">
    <img src="/../assets/images/first-print.jpg" alt="basic-shape" width="49%" >          
</div>
  

**Trigger mechanism**:

**Objective**: Initial print of the trigger had the T-Shape joint printed using 0.2 mm layer height.

**Issue**: This print had a T-Shape where the cylinder meant to hold onto the holder was not round causing it to be hard to work with.

**Solution Attempt**: The layer height was changed to 0.1 mm allowing for a more detailed circle.

**Future Approach**: For future prints the layer height will be in consideration before printing to prevent such mistakes.

**Visuals**: 
<div align="center">
    <img src="/../assets/images/trigger-testprint.jpg" alt="basic-shape" width="49%" >          
</div>

**Battery Lid Clip**:

**Objective**: The objective was to print a batterylid which would be able to push into the controller and have a small clip bend to fit the lid into place. 

**Issue**: The clip used was too weak and would break if the lid was attempted to be put into the controller, also the railings on the lid which would fit into 2 slots on the controller did not fit.

**Solution Attempt**: The slots on the controller were enlarged a lot since they were only used for placement and not as a push fit. And the battery clip was made thicker and was made to curve less allowing it to be more resistent to snapping when bending.

**Future Approach**: For future prints research should be done to see if there is a better 3D print filament to use for a situation where the material needs to bend slightly as PLA was kind of hard to work with. The battery lid now does work but you cannot open it easily with your finger nail like you would a tv controller. By using a flathead screwdriver it is easy removed but this kind of defeats the purpose.

**Visuals**: 
<div align="center">
    <img src="/../assets/images/currentprint-2.jpg" alt="batterylid" width="49%" >          
</div>
  

**Controller Assembly**:

**Objective**: The final design of the controller was done. It was now time to solder all components together and fit them in the controller.

**Issue**: Due to the lack of flexibiliy in the available wires this became quite a problem. Although carefull considerations was done to allow for enough room for components and still have room for wires. The room left for the wires was not nearly enough. 

**Solution Attempt**: Attempts were made to print the controller bigger but it quickly seemed like this wouldn't be so easy as some components were height dependent  and some components like the button didn't have enough room even with a higher lid. The final solution was to remake the whole controller and make a new one. This is where the Breadboard controller comes in. 

**Future Approach**: Although the breadboard controller fullfills the requirements of being a controller for the game. It is not the design that was preferable both based on size and looks. If more time presents itself a PCB would make a great addition as there is plenty of room to add this in the controller. This would also simplify some mechanics such as the button mechanism. A button could soldered to the bottom of the pcb instead of having to make a mechanism to hover the bottom above the trigger.

**Visuals**: 
<div align="center">
    <img src="/../assets/images/failed-soldering.jpg" alt="basic-shape" width="49%" >          
</div>

  

## 2. Conclusion
The development of the game console and controller has mostly met the set goals, providing an easy-to-use, reliable system. User tests confirmed the product works well with minimal setup. However, the breadboard controller, while functional, is not optimal in terms of ergonomics and cosmetic design. Future work in getting the original Wii like design working with the use of a PCB is preferred over using the breadboard controller.

Some challenges, such as issues with the housing, trigger mechanism, and battery lid clip, were addressed through design changes. These lessons will help improve future versions.

Overall, the work on this project was very informative and usefull.