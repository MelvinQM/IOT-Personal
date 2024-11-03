# Web Code

## Contents
- **[1. Project Structure](#1-project-structure)**
    - **[1.1 Code conventions](#11-code-conventions)**
    - **[1.2 File structure](#12-file-structure)**
- **[2. Code](#2-code)**
    - **[2.1 Frontend](#21-frontend)**
        - **[2.1.1 HTML](#211-html)**
        - **[2.1.2 CSS](#212-css)**
        - **[2.1.3 Javascript](#213-javascript)**
    - **[2.2 Backend](#21-backend)**
        - **[2.2.1 API Code Structure](#221-api-code-structure)**
        - **[2.2.2 API entrypoint](#222-api-entrypoint)**
        - **[2.2.3 Controllers & Gateways](#222-controllers-gateways)**

## 1. Project Structure


### 1.1 Code conventions
These conventions consist of most importantly but not exclusively:

- Classes are written in `Camelcase`.
- Functions and variable names are written using `camelCase`.

### 1.2 File structure
The project’s codebase is contained within the `web/` folder, which houses both frontend and backend components.

**Frontend Structure**:

- `web/`: HTML files are stored directly in the root of the web folder.
- `web/css`: Contains all CSS files for styling the application.
- `web/js`: Holds JavaScript files responsible for interactivity and functionality.

**Backend Structure**:

- `web/api`: Contains all API-related code.
- `web/api/`: The main entry point for the API is located here.
- `web/api/src`: Includes all supporting classes used by the API to handle functionality, keeping backend code organized and modular.


## 2. Code
The code for the website is divided between the frontend and backend code. The frontend consists of 2 HTML pages with each a seperate css and js file. The backend consists of an entry point found in `web/api/api.php` and all used classes found in `web/api/src`.

### 2.1 Frontend

#### 2.1.1 HTML

#### 2.1.2 CSS

#### 2.1.3 Javascript


### 2.2 Backend
#### 2.2.1 API Code Structure
The code of the API is divided between a few elements.

- The API entry point `api.php`
- A controller which handles api requests
- A gateway which handles the SQL statements to be run.

#### 2.2.2 API entrypoint
The entrypoint of the API serves as the start of every request. An autoloader is defined to allow for the connection between the main api.php file and all other files that are all sorted in their own respective folders. 

An error and exception handler is also defined to allow for json responses incases of errors. In the entry point it is also defined that the api returns json formatted responses
```php
<?php
header("Content-type: application/json; charset=UTF-8");
set_error_handler("ErrorHandler::handleError");
set_exception_handler("ErrorHandler::handleException");
```

Every API request made first goes through `api.php`. The request is routed to the appropriate controller based on the URL path, `ex: GET api/player is sent to PlayerController`. The controller needed is determined by using the getController() function found in the `src/RouteHandler.php` 
```php
<?php
$controller = RouteHandler::getInstance()->getController(strtolower($parts[1]));
```
class. By looking at the first part of the url being the name of the controller. The controller is defined and the corresponding gateway is assigned to this controller see example below:
```php
<?php
case "player":
    $gateway = new PlayerGateway($db);
    return new PlayerController($gateway);
```
Finally the handleRequest() of the controller is called to handle the api request made. If filters are specified in the URL these are also then passed to the controller.


#### 2.2.2 Controllers & Gateways
The API's connection to the database is handled through the use of controllers and gateways. 

- A controller acts as an intermediary between the HTTP requests and the data stored in the database. A controller determines appropriate action based on the request method. 
- A gateway serves as the direct interface between the application and the database, handling all SQL interactions. It provides a set of CRUD (Create, Read, Update, Delete) methods that enable database operations. Considerations were also made to ensure SQL injection wouldn't be possible by using PHP's `stmt` functionality to prepare params.

The controller determines the appropriate action by first seeing if an ID has been given `ex: api/player/1` in this case the request is about a single resource and not a collection. The request is either sent to the handleRequest() function or the handleCollection() function.
```php
<?php
if($id) {
    $this->handlePlayerRequest($method, $id);
} else {
    $this->handlePlayerCollectionRequest($method, $filters);
}
```
In both of these functions a switch statement is defined to determine which method is invoked. The corresponding gateway function is then called to perform a CRUD method. In the cases of POST and PATCH methods the data is retrieved from the body of the api request to be used in the gateway function. For some collection requests the option is given to use a filter. An example of this is is fetching a player by their name: `ex: GET api/player/?name={name}`