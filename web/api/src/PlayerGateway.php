<?php

class PlayerGateway 
{
    private mysqli $conn;

    public function __construct(Database $database)
    {
        $this->conn = $database->getConnection();
    }

    public function getAll(): array
    {
        $sql = "SELECT * FROM player";
        
        $stmt = $this->conn->query($sql);
    
        $data = [];
        
        while ($row = $stmt->fetch_assoc()) {
            $data[] = $row;
        }
    
        return $data;
    }

    public function create(array $data) : string
    {
        $sql = "INSERT INTO player (name) VALUES (?)";

        $stmt = $this->conn->prepare($sql);

        $stmt->bind_param("s", $data["name"]);

        $stmt->execute();

        $insertedId = $this->conn->insert_id;

        $stmt->close();

        return $insertedId;
    }
  }