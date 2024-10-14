<?php
/*
 * Author: Melvin
 * Date: October 14, 2024
 * Description: A gateway class managing the sql queries made to the Difficulty table.
 * License: This project is licensed under the MIT License.
 */
class DifficultyGateway 
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
     * Executes a SELECT query to fetch all rows from the difficulty table.
     *
     * @return array An array of difficulty records.
     */
    public function getAll(): array
    {
        $sql = "SELECT * FROM difficulty";
        
        $stmt = $this->conn->query($sql);
    
        $data = [];
        
        while ($row = $stmt->fetch_assoc()) {
            $data[] = $row;
        }
    
        return $data;
    }

    /**
     * Executes a SELECT query to fetch a difficulty based on the provided ID.
     *
     * @param string $id The ID of the difficulty to retrieve.
     *
     * @return array|false An array of difficulty data or false if not found.
     */
    public function get(string $id) : array | false
    {
        $sql = "SELECT * FROM difficulty WHERE id = ?";

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

  }