<?php

class PlayerGateway 
{
    private mysqli $conn;

    /**
     * Constructor initializes the database connection.
     *
     * @param Database $database An instance of the Database class providing the connection.
     */
    public function __construct(Database $database)
    {
        $this->conn = $database->getConnection();
    }

    /**
     * Executes a SELECT query to fetch all rows from the player table.
     *
     * @return array An array of player records.
     */
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

    /**
     * Executes an INSERT query to add a new player.
     *
     * @param array $data The player data to insert.
     *
     * @return string The ID of the newly created player.
     */
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

    /**
     * Executes a SELECT query to fetch a player based on the provided ID.
     *
     * @param string $id The ID of the player to retrieve.
     *
     * @return array|false An array of player data or false if not found.
     */
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

    /**
     * Executes an UPDATE query to modify a player.
     *
     * @param string $id The ID of the player to update.
     * @param array $data The data to change/update.
     *
     * @return int The number of rows affected by the update.
     */
    public function update(string $id, array $data) : string
    {
        $sql = "UPDATE player SET name = ? WHERE id = ?";

        $stmt = $this->conn->prepare($sql);

        $stmt->bind_param("ss", $data["name"], $id);

        $stmt->execute();

        return $stmt->affected_rows;
    }

    /**
     * Executes a DELETE query to remove a player from the database.
     *
     * @param string $id The ID of the player to delete.
     *
     * @return bool True if a row was deleted, false otherwise.
     */
    public function delete(string $id) : bool
    {
        $sql = "DELETE FROM player WHERE id = ?";

        $stmt = $this->conn->prepare($sql);

        $stmt->bind_param("s", $id);

        $stmt->execute();

        return $stmt->affected_rows;
    }

  }