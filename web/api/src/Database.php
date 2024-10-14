<?php
/*
 * Author: Melvin
 * Date: October 14, 2024
 * 
 * A database class handling the connection to the database using environment variabels to establish a connection.
 * 
 * License:
 * This project is licensed under the MIT License - see the LICENSE file for details.
 */
class Database {
    public function __construct() {}

    /**
     * Establishes a MySQL database connection using mysqli.
     *
     * This function creates a new `mysqli` object and attempts to connect to the database 
     * using the provided server name, user credentials, and database name.
     *
     * @return mysqli Returns an established mysqli database connection.
     */
    public function getConnection(): mysqli 
    {
        $servername = getenv("MYSQL_SERVER_NAME"); 
        $username = getenv("MYSQL_USER");
        $password = getenv("MYSQL_ROOT_PASSWORD");
        $database = getenv("MYSQL_DATABASE");
        $port = getenv("MYSQL_PORT");
        
        $dbConnection = new mysqli($servername, $username, $password, $database);

        if ($dbConnection->connect_error) {
            echo json_encode(array("success" => false, "error" => $dbConnection->connect_error));
            exit();
        }

        //Sets the connection options for integer and float types.
        $dbConnection->options(MYSQLI_OPT_INT_AND_FLOAT_NATIVE, 1);
        $dbConnection->set_charset("utf8");
    
        return $dbConnection;
    }
}