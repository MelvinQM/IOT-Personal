<?php
$servername = "mariadb";
$username = "root";
$password = "7YKyE8R2AhKzswfN";
$database = "iot_moesmq";
$port = 3306;

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
