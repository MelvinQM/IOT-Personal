<?php
/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: A gateway class managing the sql queries made to the Player table.
 * License: This project is licensed under the MIT License.
 */
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
     * Additionally an option add filters is possible for this table
     *
     * @return array An array of player records.
     */
    public function getAll(?array $filters): array
    {
        $sql = "SELECT * FROM player";
        
        // If there are filters add them to the sql statement
        if (!empty($filters)) {
            $conditions = [];
            foreach ($filters as $key => $value) {
                $conditions[] = "$key = ?";
            }
            $sql .= " WHERE " . implode(" AND ", $conditions);
        }
    
        $stmt = $this->conn->prepare($sql);
    
        if (!empty($filters)) {
            $types = str_repeat('s', count($filters)); // Assuming all filters are strings, adjust accordingly
            $values = array_values($filters);
            $stmt->bind_param($types, ...$values); // Bind the values safely
        }
    
        $stmt->execute();
        $result = $stmt->get_result();
        
        $data = [];
        
        while ($row = $result->fetch_assoc()) {
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