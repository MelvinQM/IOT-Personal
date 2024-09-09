<?php
declare(strict_types= 1);
$servername = getenv("MYSQL_SERVER_NAME"); 
$username = getenv("MYSQL_USER");
$password = getenv("MYSQL_ROOT_PASSWORD");
$database = getenv("MYSQL_DATABASE");
$port = getenv("MYSQL_PORT");


// Load classes from folder src automatically
spl_autoload_register(function ($class){
    require __DIR__ . "/src/$class.php";
});

set_error_handler("ErrorHandler::handleError");
set_exception_handler("ErrorHandler::handleException");
header("Content-type: application/json; charset=UTF-8");

$parts = explode("/", $_SERVER["REQUEST_URI"]);
print_r($parts);

// if($parts[2] != "player") {
//     http_response_code(404);
//     exit;
// }

$db = new Database($servername, $database, $username, $password);
$gateway = new PlayerGateway($db);

$id = $parts[3] ?? null;
$controller = new PlayerController($gateway);
$controller->handleRequest($_SERVER["REQUEST_METHOD"], $id);



