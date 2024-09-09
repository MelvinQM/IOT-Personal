<?php
declare(strict_types= 1);
$servername = getenv("MYSQL_SERVER_NAME"); 
$username = getenv("MYSQL_USER");
$password = getenv("MYSQL_ROOT_PASSWORD");
$database = getenv("MYSQL_DATABASE");
$port = getenv("MYSQL_PORT");


// Load classes from folder src
spl_autoload_register(function ($class){
    require __DIR__ . "/src/$class.php";
});

header("Content-type: application/json; charset=UTF-8");

$parts = explode("/", $_SERVER["REQUEST_URI"]);

//TODO: Add check if table name doesnt exist in db return 404

$id = $parts[3] ?? null;


$db = new Database($servername, $database, $username, $password);
$db->getConnection();

$controller = new RequestController();
$controller->handleRequest($_SERVER["REQUEST_METHOD"], $id);



