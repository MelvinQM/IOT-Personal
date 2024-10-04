<?php
declare(strict_types= 1);

// Load classes from folder src automatically
spl_autoload_register(function ($class){
    require __DIR__ . "/src/$class.php";
});

set_error_handler("ErrorHandler::handleError");
set_exception_handler("ErrorHandler::handleException");
header("Content-type: application/json; charset=UTF-8");

$uri = parse_url($_SERVER["REQUEST_URI"], PHP_URL_PATH);
$parts = explode("/", trim($uri, "/"));
// print_r($parts);

$controller = RouteHandler::getInstance()->getController(strtolower($parts[1]));

$id = $parts[2] ?? null;
$controller->handleRequest($_SERVER["REQUEST_METHOD"], $id);



