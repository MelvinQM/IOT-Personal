<?php

class Database {
    public function __construct(
        private string $servername, 
        private string $databaseName, 
        private string $user, 
        private string $password) {}

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
        $dbConnection = new mysqli($this->servername, $this->user, $this->password, $this->databaseName);

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