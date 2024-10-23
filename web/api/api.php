<?php
/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: An api entrance file. "explodes" a url to correctly pass the api request to the correct controller class and handle the request accordingly or return a json error.
 * License: This project is licensed under the MIT License.
 */

declare(strict_types= 1);

spl_autoload_register(function ($class) {
    // Replace namespace separators with directory separators
    $classPath = str_replace('\\', DIRECTORY_SEPARATOR, $class);

    // Define the directories to search
    $directories = [
        __DIR__ . '/src/',
        __DIR__ . '/src/player/',
        __DIR__ . '/src/score/',
        __DIR__ . '/src/session/',
        __DIR__ . '/src/difficulty/',
        __DIR__ . '/src/actions/'
    ];

    // Search for the file in the specified directories
    foreach ($directories as $directory) {
        $file = $directory . "{$classPath}.php";
        if (file_exists($file)) {
            require $file;
            break;
        }
    }
});


set_error_handler("ErrorHandler::handleError");
set_exception_handler("ErrorHandler::handleException");
header("Content-type: application/json; charset=UTF-8");

$uri = parse_url($_SERVER["REQUEST_URI"], PHP_URL_PATH);
$parts = explode("/", trim($uri, "/"));
//print_r($parts);


$controller = RouteHandler::getInstance()->getController(strtolower($parts[1]));

// This can be eiter an id incase of CRUD operations or a functionname incase its an action
$arg = $parts[2] ?? null;

// Get query parameters (filters)
$filters = $_GET;

if($filters)
{
    $controller->handleRequest($_SERVER["REQUEST_METHOD"], $arg, $filters);
} else {
    $controller->handleRequest($_SERVER["REQUEST_METHOD"], $arg);
}
