<?php

class Database {
    public function __construct(private string $servername, 
                                private string $databaseName, 
                                private string $user, 
                                private string $password) 
    {
        
    }

    public function getConnection(): mysqli 
    {
        $dbConnection = new mysqli($this->servername, $this->user, $this->password, $this->databaseName);

        if ($dbConnection->connect_error) {
            echo json_encode(array("success" => false, "error" => $dbConnection->connect_error));
            exit();
        } else {
            echo "Connected to database";
        }


        $dbConnection->options(MYSQLI_OPT_INT_AND_FLOAT_NATIVE, 1);
        $dbConnection->set_charset("utf8");
    
        return $dbConnection;
    }
}