# Create & Test

## 1. User testing


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

#### 2.1.2 Slicer layout
The program used to create the gcode required for the printed is Bambu Studio the program looks like this:
<img src="/../assets/images/bambustudio.png" alt="bambustudio">

#### 2.1.3 Slicer print settings
The bambustudio files can be found in this repo under assets/3d-files/.. These files come with the settings already setup.

The controller was printed using the following settings:

- **Top**:
    - No Support - Default settings for printer.
- **Batterylid**:
    - Tree support **manual** - Using the `support painting` function only the overhanging parts were drawn with tree support.
- **Bottom** (Print facing up to avoid using as much support):
    - Tree support **automatic** (Threshold angle 15) this uses a bit more filament than most likely optimal, but ensures the quality of the controller.

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

One of the most important mechanics opf the controller was of course the trigger to test this a small print was made. More about the inspiration for this mechanism can be found in [concept & design](concept_design.md#222-trigger-mechanism).
To test this design the trigger was printed with a seperate holder:

<div   style="display: flex; justify-content: space-between;">
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

<!-- <div style="display: flex; align-items: center;">
  <div style="flex: 1;">

  </div>
  <div style="flex: 1; text-align: right;">
    <img src="" alt="" width=75%>
  </div>
</div> -->