# Learning journal

Your learning journal can be seen as a diary of your learning process. It is a place where you can reflect on your learning, and where you can keep track of your progress. It is also a place where you can keep track of your questions, and where you can write down your answers to those questions.

So for example when you receive feedback on your project, you can write down the feedback and your reflection on it in your learning journal. You can also write down what you have learned from the feedback, and how you will apply it in your project.

<br>

## Week 1

Monday I was unfortunately not able to attend the lesson. In my own time I spent some time looking through all the online files about the lectures I also asked a few fellow students about the information i missed. 

I started the course setting up all seperate parts of the project and seeing if they would run. I installed all necessary programs and setup the template project. After this I started working on an ERD for a Database design.

<br>

<div align="center">
  <img src="/assets/ERD.drawio.png" alt="ERD">
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
  <img src="/assets/EER.png" alt="EER">
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

### REST API
I worked on creating the first version of my API. I worked on this through a [tutorial](https://www.youtube.com/watch?v=X51KOJKrofU&ab_channel=DaveHollingworth) this tutorial taught me to make a simple rest API capable of performing CRUD operations with a single table. This doesn't allow for full communication with my database as of yet. It's a great start however, as it allows control over atleast the player table which is sufficient for now for testing purposes.

Additionally I added a custom http error code display using the http.cat API
<div align="center">
  <img src="/assets/errorcodedisplay.png" alt="errorcodedisplay">
</div>

<br>

### Frontend 
To visualise the data I worked on my frontend a bit. I added tailwindcss as i've already worked with bootstrap a lot and wanted to learn a bit more about tailwind.
<div align="center">
  <img src="/assets/frontend.png" alt="frontendexample">
</div>

I ended up improving the frontend by adding a scrollable table body allowing the page to not extend endlessly with the size of the tabe. Also cell border dividers were added to improve the readability.

<br>

### Feedback

**🌐 Application Code.**

**Reviewer: Lucas Hilgevoord**

**Feedback:** Please add a summary in your php code above your functions. The rest looks good! Nice to see the comments in your functions it self.

**Takeaway:** TODO:

<br>

### Start of embedded device
After having a basic API up and running the start of the embedded device was next. The goal was to have a simple embedded device with a button that can trigger some API calls to test the connection between the different elements.

Result:

<div align="center">
  <img src="/assets/basicembeddeddevice.jpg" alt="basicembeddeddevice">
</div>

<br>

<div align="center">
  <img src="/assets/frontend.png" alt="frontendexample">
</div>

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