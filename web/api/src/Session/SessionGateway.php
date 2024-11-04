<?php
/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: A gateway class managing the sql queries made to the Session table.
 * License: This project is licensed under the MIT License.
 */
class SessionGateway 
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
     * Executes a SELECT query to fetch all rows from the session table.
     *
     * @return array An array of session records.
     */
    public function getAll(): array
    {
        $sql = "SELECT * FROM session";
        
        $stmt = $this->conn->query($sql);
    
        $data = [];
        
        while ($row = $stmt->fetch_assoc()) {
            $data[] = $row;
        }
    
        return $data;
    }

    /**
     * Executes an INSERT query to add a new session.
     *
     * @param array $data array of all session colomn data (completed, start_time, end_time, player_id, difficulty_id)
     *
     * @return int The ID of the newly created session.
     */
    public function create(array $data) : int
    {
        $sql = "INSERT INTO session (completed, start_time, end_time, player_id, difficulty_id) VALUES (?, ?, ?, ?, ?)";

        $stmt = $this->conn->prepare($sql);

        $completed = isset($data['completed']) ? $data['completed'] : null;            // Boolean default value 0
        $start_time = isset($data['start_time']) ? $data['start_time'] : null;          // DATETIME
        $end_time = isset($data['end_time']) ? $data['end_time'] : null;                // DATETIME
        $player_id = isset($data['player_id']) ? $data['player_id'] : null;             // int
        $difficulty_id = isset($data['difficulty_id']) ? $data['difficulty_id'] : 1;    // int
        
        // Bind parameters: "b" for boolean, "s" for string (DATETIME), and "i" for ints
        $stmt->bind_param("issis", $completed, $start_time, $end_time, $player_id, $difficulty_id);

        $stmt->execute();

        $insertedId = $this->conn->insert_id;

        $stmt->close();

        return $insertedId;
    }

    /**
     * Executes a SELECT query to fetch a session based on the provided ID.
     *
     * @param string $id The ID of the session to retrieve.
     *
     * @return array|false An array of session data or false if not found.
     */
    public function get(string $id) : array | false
    {
        $sql = "SELECT * FROM session WHERE id = ?";

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
     * Executes an UPDATE query to modify a session.
     *
     * @param string $id The ID of the session to update.
     * @param array $data The data to change/update.
     *
     * @return int The number of rows affected by the update.
     */
    public function update(string $id, array $data) : int
    {
        // Check if player_id is being updated
        $currentSessionData = $this->get($id);

        // If session is completed can't be updated
        if ($currentSessionData["completed"]) {
            ErrorCodeHelper::getInstance()->handleErrorCode(400,"Can't update a completed session");
        }
        
        //Prevent updating value when value is null
        $sql = "UPDATE session SET 
                    difficulty_id = COALESCE(?, difficulty_id), 
                    use_gyro = COALESCE(?, use_gyro), 
                    player_id = COALESCE(?, player_id), 
                    completed = COALESCE(?, completed), 
                    start_time = COALESCE(?, start_time), 
                    end_time = COALESCE(?, end_time) 
                WHERE id = ?";
    
        $stmt = $this->conn->prepare($sql);
    
        // Use null coalescing to set default values or null
        $completed = isset($data['completed']) ? $data['completed'] : null; // Keep null if not set
        $start_time = isset($data['start_time']) ? $data['start_time'] : null; // Keep null if not set
        $end_time = isset($data['end_time']) ? $data['end_time'] : null; // Keep null if not set
        $player_id = isset($data['player_id']) ? $data['player_id'] : null; // Keep null if not set
        $difficulty_id = isset($data['difficulty_id']) ? $data['difficulty_id'] : null; // Default to 1 if not set
        $use_gyro = isset($data['use_gyro']) ? $data['use_gyro'] : null; // Default to 0 if not set
    
        $stmt->bind_param("iisissi", $difficulty_id, $use_gyro, $player_id, $completed, $start_time, $end_time, $id);
    
        // Execute the statement
        $stmt->execute();
    
        // Return the number of affected rows
        return $stmt->affected_rows;
    }
    
    

    /**
     * Executes a DELETE query to remove a session from the database.
     *
     * @param string $id The ID of the session to delete.
     *
     * @return int The number of rows affected by the update.
     */
    public function delete(string $id) : int
    {
        $sql = "DELETE FROM session WHERE id = ?";

        $stmt = $this->conn->prepare($sql);

        $stmt->bind_param("s", $id);

        $stmt->execute();

        return $stmt->affected_rows;
    }

  }