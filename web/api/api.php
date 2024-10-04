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
print_r($parts);


if(!in_array(strtolower($parts[1]), RouteHandler::getInstance()->getAllRoutes())) {
    http_response_code(404);
    exit;
}

$db = new Database();
$gateway = new PlayerGateway($db);

$id = $parts[2] ?? null;
$controller = new PlayerController($gateway);
$controller->handleRequest($_SERVER["REQUEST_METHOD"], $id);



