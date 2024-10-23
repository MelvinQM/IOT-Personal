<?php
/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: A gateway class managing the sql queries made to the Score table.
 * License: This project is licensed under the MIT License.
 */
class ScoreGateway 
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
     * Executes a SELECT query to fetch all rows from the score table.
     *
     * @return array An array of score records.
     */
    public function getAll(?array $filters): array
    {
        $sql = "SELECT * FROM score";
        
        // Add condition if filter exists
        if (isset($filters["session_id"])) {
            $sql .= " WHERE session_id = ?";
        }
    

        $stmt = $this->conn->prepare($sql);
    
        // Bind the session_id if it exists
        if (isset($filters["session_id"])) {
            $stmt->bind_param("i", $filters["session_id"]);
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
     * Executes an INSERT query to add a new score.
     *
     * @param array $data The score and session_id to insert.
     *
     * @return string The ID of the newly created score.
     */
    public function create(array $data) : string
    {
        $sql = "INSERT INTO score (session_id, score) VALUES (?, ?)";

        $stmt = $this->conn->prepare($sql);

        $stmt->bind_param("ss", $data["session_id"], $data["score"]);

        $stmt->execute();

        $insertedId = $this->conn->insert_id;

        $stmt->close();

        return $insertedId;
    }

    /**
     * Executes a SELECT query to fetch a score based on the provided ID.
     *
     * @param string $id The ID of the score to retrieve.
     *
     * @return array|false An array of score data or false if not found.
     */
    public function get(string $id) : array | false
    {
        $sql = "SELECT * FROM score WHERE id = ?";

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
        $sql = "UPDATE score SET score = ? WHERE id = ?";

        $stmt = $this->conn->prepare($sql);

        $stmt->bind_param("ss", $data["score"], $id);

        $stmt->execute();

        return $stmt->affected_rows;
    }

    /**
     * Executes a DELETE query to remove a score from the database.
     *
     * @param string $id The ID of the score to delete.
     *
     * @return int The number of rows affected by the update.
     */
    public function delete(string $id) : bool
    {
        $sql = "DELETE FROM score WHERE id = ?";

        $stmt = $this->conn->prepare($sql);

        $stmt->bind_param("s", $id);

        $stmt->execute();

        return $stmt->affected_rows;
    }

  }