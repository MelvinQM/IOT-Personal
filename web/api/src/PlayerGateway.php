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

    public function get(string $id) : array | false
    {
        $sql = "SELECT * FROM player WHERE id = ?";

        $stmt = $this->conn->prepare($sql);

        $stmt->bind_param("s", $id);

        $stmt->execute();

        $result = $stmt->get_result();

        if ($result === false) {
            return false;
        }
    
        $data = $result->fetch_assoc();
        
        return $data !== null ? $data : false;
    }

    public function update(string $id, array $data) : string
    {
        $sql = "UPDATE player SET name = ? WHERE id = ?";

        $stmt = $this->conn->prepare($sql);

        $stmt->bind_param("ss", $data["name"], $id);

        $stmt->execute();

        return $stmt->affected_rows;
    }

  }