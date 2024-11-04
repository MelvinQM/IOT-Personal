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
    - **[2.2 Backend](#22-backend)**
        - **[2.2.1 API Code Structure](#221-api-code-structure)**
        - **[2.2.2 API entrypoint](#222-api-entrypoint)**
        - **[2.2.3 Controllers & Gateways](#222-controllers-gateways)**

## 1. Project Structure

### 1.1 Code conventions
## 1.1.1 PHP Code Conventions

- **File Naming**: Use `snake_case` for file names.
- **Class Names**: Use `CamelCase`.
- **Method Names**: Use `camelCase`.
- **Variable Names**: Use `camelCase`.
- **Constants**: Use `UPPER_SNAKE_CASE`.
- **Comments**: Use `//` for single-line comments and `/** ... */` for multi-line comments.
- **Array Syntax**: Prefer `[]` over `array()` for array declarations.

## 1.1.2 HTML Code Conventions

- **File Naming**: Use `kebab-case` for file names.
- **Element Names**: Use lowercase for element names.
- **Attributes**: Use lowercase and hyphen-separated names (e.g., `data-attribute`).
- **Doctype**: Always declare `<!DOCTYPE html>` at the beginning of the document.
- **Comments**: Use `<!-- Comment -->` for comments.

## 1.1.3 CSS Code Conventions

- **File Naming**: Use `kebab-case` for file names.
- **Selectors**: Use lowercase and hyphen-separated names for class and ID selectors (e.g., `.my-class`, `#my-id`).
- **Indentation**: Use 2 spaces for indentation.
- **Properties**: Use lowercase for property names and hyphen-separated format (e.g., `background-color`).
- **Values**: Use lowercase for color names and units (e.g., `px`, `em`, `%`).
- **Organization**: Group related styles together (e.g., layout, typography, colors).
- **Comments**: Use `/* Comment */` for comments.

## 1.1.4 JavaScript Code Conventions

- **File Naming**: Use `kebab-case` for file names.
- **Variable Names**: Use `camelCase` for variable names.
- **Function Names**: Use `camelCase` for function names.
- **Class Names**: Use `CamelCase` for class names.
- **Line Length**: Limit lines to 80-100 characters.
- **Semicolons**: Always use semicolons at the end of statements.
- **Comments**: Use `//` for single-line comments and `/* ... */` for multi-line comments.

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

**index.html**:

The `index.html` file serves as the main interface for the Hoot Pursuit game, providing the player with the ability to enter necessary information to start a game session. It includes the following primary sections:

- **Page Setup**: Sets up the page metadata, including title, favicon, Bootstrap initialization and linking to the custom css file `/css/index.css` Links to a custom CSS file for additional styling.
- **Input Form**:  Shows session details (Session ID, Player, Difficulty, Control method, Start/End time) and game state.
- **Session details**: Displays session details when a game session is in progress. Contains a table that dynamically shows session details (Session ID, Player, Difficulty, Control method, Start/End time) and the game's current status. There is also a table present to show scores provides a dynamic view of the player's scores, allowing real-time score updates.
- **Script**: Links to `index.js` for frontend JavaScript logic handling events, such as form submission, element toggling, and API calls.

**admin.html**:

The `admin.html` file is the main interface for viewing all database data in Hoot Pursuit, providing an organized view of players, highscores, sessions, difficulties, and scores. Key sections include:

- **Page Setup**: Sets up page metadata, title, Bootstrap styling, and links to custom CSS (/css/admin.css) for additional styling.
- **Navbar**: A top navigation bar with links to the "Home" and "Dashboard" pages for easy navigation.
- **Data Tables**: On the admin page a table is present for all the database tables and endpoints present. `(Tables: Player, Score, Session and Difficulty, Actions: Highscores)`
- **Scripts**: Links to admin.js for frontend JavaScript that handles data fetching, UI updates, and interactions with the server.


#### 2.1.2 CSS

**index.css**: 

The `index.css` file defines the main styles for the Hoot Pursuit game interface, creating a retro aesthetic and managing layout, colors, fonts, and animations. Key style definitions include:

- **Font**: "ArcadeClassic" is assigned.
- **Background**: Applies a pixelated background image (`web/assets/background.png`) covering the entire window for a classic arcade look.
- **Custom containers**: A custom container is declared which has a semi transparent black background.
- **Custom button**: Customizes button styles, removing borders and setting hover behavior with a dark background and white color for emphasis.
- **Tables**: Customizes tables with auto-scroll for long lists, thin white scrollbars, and constrained height for better layout.
- **Duck animation**: An animation for the movement of a duck sprite on the webend is also defined. This allows for some movement on screen to interest the user.

**admin.css**: 

The `admin.css` file styles the admin interface, focusing on a dark theme with a retro touch for consistency with the retro game look and feel.

- **Font**: "ArcadeClassic" is assigned.
- **Background**: Applies a black background with a subtle gradient effect for some interesting visuals.
- **Tables**: Customizes tables with auto-scroll for long lists, thin white scrollbars, and constrained height for better layout.
- **Additional styling**: Adds varioous stylign to enhance the user experience `ex: a hover underline to navbar links for visual feedback`.


#### 2.1.3 Javascript
The javascript logic is defined per page `index.js` for index.html and `admin.js` for `admin.html`.

**ApiService**: To allow for communication with the API a const ApiService is defined in both javascript files which has functions to make specific calls to the API. 
*Example code only*:
```js
async getData() {
    return fetch('/api/data')
        .then((response) => response.json())
        .then((data) => {
            return data;
        })
        .catch((error) => {
            console.error("Error:", error);
            return null;
        });
},
```
**Index Page specific**:

- **Helper functions**: Besides the connection the API a number of helper functions are defined to support the index page logic.
    - `getDifficultyName(difficultyId)`: converts a numerical difficulty ID into a difficulty name.
    - `redirectToAdmin()`: Redirects the user to the admin page.
    - `toggleDivs()`: Toggles the visibility of the different screens in the app (e.g., input screen, playing screen, and score screen).
    - `getCurrentDateTime()`: Returns the current date and time in a YYYY-MM-DD HH:MM:SS format.

- **OpenPlayingScreen()**: Initializes the playing screen when a session begins. It performs the following tasks:
    - **Toggle View**: calls toggleDivs() to switch the screen to the playing view.
    - **Data Fetch**: Retrieves session details by calling ApiService.fetchSessionData(sessionId), which returns data related to the session’s configuration and status.
    - **Data Insertion into HTML Elements**: Retrieves elements by their IDs and updates their textContent based on the fetched data.
    - **Score and Session Fetching**: Initiates a recurring interval to call ApiService.fetchScoreBySessionId(sessionId) and ApiService.fetchSessionData(sessionId), updating and displaying the session's scores and session details in table elements.


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