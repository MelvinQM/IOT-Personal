# Technical Documentation

## 1. Introduction
The goal of the webapplication for the Hoot Shooter project was to create a retro 'feel' website. The website had as purpose to be the the controller for the game console. The website will have a button allowing to start the game, also through the use of the web portal various game settings will be able to be changed and selected. During gameplay the website will show various usefull information such as the current game session settings and the scores acquired during the session. Besides the website for the user a simple website that shows varous tables filled with data retrieved from the API will also be present. This will allow a direct monitor for the database containing the session and game data. 

To allow for all the communications required with the database an API will also have to be developed to allow for the connectivity through a safe intermediate preventing security risks.


## 2. Technologies Used

### 2.1 Code editor
---
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    Visual studio code was my code editor for the development of the web application. I chose VScode as it's a lightweight multi purpose code editor allowing for an easy workflow between front and backend development. VScode also has a enormous library of extensions which allowed for coding language specific syntax highlighting and intellisense. All of this greatly improves the workflow efficiency and effectiveness.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/vscode.jpeg" alt="vscode">
  </div>
</div>


### 2.2 Frontend
---
The frontend is built with HTML, CSS, and JavaScript to keep the application lightweight and easy to maintain. This approach was chosen for simplicity and to avoid the overhead of complex frameworks, as the requirements for interactivity and styling are straightforward.
<br>
<div style="display: flex; align-items: center; gap: 10px; ">
    <img src="/../assets/images/html.png" alt="html" style=" max-width: 33%;" />
    <img src="/../assets/images/css.png" alt="css" style="height: 300px; max-width: 33%;" />
    <img src="/../assets/images/javascript.png" alt="javascript" style="max-width: 33%;" />
</div>
<br>




#### 2.2.1 Bootstrap
For the styling Bootstrap was used. Bootstrap is a styling component library allowing for quick good looking html elements without much need to write CSS. This allows for a quick work flow promoting producitivity a great deal. 


### 2.3 Backend
---
#### 2.3.1 PHP
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    The backend is developed using PHP, a widely-used scripting language suited for server-side logic. PHP was chosen due to its compatibility with a variety of servers and ease of integration with relational databases, as well as its efficient handling of RESTful API requests.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/php.png" alt="php">
  </div>
</div>

### 2.4 Database
#### 2.4.1 MariaDB
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    The database is a **mariadb** based SQL database. MariaDB is an open-source relational database management system (RDBMS) that is a fork of MySQL. The database can be viewed, monitored and maintained through the use of MySQLWorkbech. More about this can be found on the [Database](/web/database#21-mysqlworkbench) page.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/mariadb.jpg" alt="mariadb">
  </div>
</div>

### 2.5 Deployment
---
#### 2.5.1 Docker
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    The application is containerized using Docker, ensuring that the environment remains consistent across development, testing, and production. This simplifies dependency management and makes the deployment process more robust and repeatable.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/docker.png" alt="docker">
  </div>
</div>
<br>

#### 2.5.2 Nginx
<div style="display: flex; align-items: center;">
  <div style="flex: 1;">
    Nginx, a high-performance web server and reverse proxy. Nginx is efficienct in handling HTTP requests, its lightweight footprint, and its strong support for concurrent connections allows it to efficiently handle the web server.
  </div>
  <div style="flex: 1; text-align: right;">
    <img src="/../assets/images/nginx.png" alt="nginx">
  </div>
</div>

#### 2.5.3 Testing
To make sure the deployment process was properly tested for use on multiple devices. I've deployed the project on multiple desktops to ensure the project is able to setup without any glaring issues. Tests were also done to ensure the efficiency and effectiveness of the web application. These can be seen in the [Create & Test](../uxd/create_test.md) page.


## 3. Design Decisions

### 3.1 Frontend Structure
#### 3.1.1 Index Page
The frontend is structured with an index page that displays a form for users to initiate the game. Upon submission, the form triggers the game start process, allowing users to interact directly with the game environment.
<img src="/../assets/images/indexpage.png" alt="indexpage">

#### 3.1.2 Admin Page
An admin page is included to provide a view of the backend data in a structured format. This page displays tables populated with data retrieved from the API endpoints, allowing developers or system maintainers to manage or review game data effectively. This keeps player interactions and administrative separate, ensuring a more concise user experience and improved maintainability.
<img src="/../assets/images/adminpage.png" alt="adminpage">

### 3.2 Backend Structure
#### 3.2.1 API Routing
The backend directs requests to `/api/`, with `api.php` serving as the main entry point. Incoming requests are routed to specific controllers based on URL parameters. For instance, requests to `/api/player/` are routed to the player controller, which handles player-related operations. This allows for an easy to understanding routing pattern for the endpoints.

#### 3.2.1 Controller and Gateway Structure
Each controller has a corresponding gateway class that contains the direct CRUD (Create, Read, Update, Delete) functions with SQL statements. These gateway classes isolate database interactions, allowing controllers to focus on handling the logic and responses. This separation of roles improves code  readability, and maintainability.
