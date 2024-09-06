<?php
$servername = getenv("MYSQL_SERVER_NAME"); 
$username = getenv("MYSQL_USER");
$password = getenv("MYSQL_ROOT_PASSWORD");
$database = getenv("MYSQL_DATABASE");
$port = getenv("MYSQL_PORT");

$dbConnection = new mysqli($servername, $username, $password, $database);

if ($dbConnection->connect_error) {
    echo json_encode(array("success" => false, "error" => $dbConnection->connect_error));
    exit();
} else {
    echo "Connected to database";
}

// Insert data into your database
// $dbConnection->query("INSERT INTO `data` (`humidity`, `temperature`) VALUES (" . $humidity . ", " . $temperature . ")");

$dbConnection->close();
