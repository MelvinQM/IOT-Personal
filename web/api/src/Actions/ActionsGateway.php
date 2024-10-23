<?php
/*
 * Author: Melvin Moes
 * Date: October 23, 2024
 * Description: 
 * License: This project is licensed under the MIT License.
 */
class ActionsGateway 
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


    public function getHighscores(?array $filters): array
    {
        // SQL query to join Score, Session, and Player tables
        $sql = "SELECT Score.score, Player.name 
                FROM Score
                INNER JOIN Session ON Score.session_id = Session.id
                INNER JOIN Player ON Session.player_id = Player.id
                ORDER BY Score.score DESC";
        
        // Check if 'count' filter is present and add LIMIT clause
        if (isset($filters["count"])) {
            $sql .= " LIMIT ?";
        }

        // Prepare the statement
        $stmt = $this->conn->prepare($sql);
        
        // If 'count' filter is provided, bind the parameter
        if (isset($filters["count"])) {
            $stmt->bind_param("i", $filters["count"]);
        }
        
        // Execute the statement
        $stmt->execute();
        
        // Fetch the results
        $result = $stmt->get_result();
        $data = [];

        // Fetch each row and store it in the data array
        while ($row = $result->fetch_assoc()) {
            $data[] = $row;
        }
        
        // Return the highscores with player names as an array
        return $data;
    }

    


}