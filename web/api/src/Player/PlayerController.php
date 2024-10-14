<?php
/*
 * Author: Melvin
 * Date: October 14, 2024
 * Description: A controller managing the connection to the Player table of a database. This controller needs a gateway to handle it's sql calls.
 * License: This project is licensed under the MIT License.
 */
class PlayerController {
    public function __construct(private PlayerGateway $gateway) {}

    /**
     * Handles HTTP requests for either a single player or a collection of players based on the provided ID.
     *
     * If an ID is provided, it routes the request to handle a single player resource; otherwise,
     * it handles requests for a collection of player resources.
     *
     * @param string $method The HTTP request method.
     * @param string|null $id The ID of the player. Null for collection requests.
     */
    public function handleRequest(string $method, ?string $id) : void
    {
        if($id) {
            // Single resource
            $this->handlePlayerRequest($method, $id);
        } else {
            // Collection of resources
            $this->handlePlayerCollectionRequest($method, $id);
        }
    }

    /**
     * Handles requests for a single player.
     *
     * This function processes requests for a specific player, identified by the ID.
     * It supports GET, PATCH, and DELETE methods, responding with appropriate data or errors.
     *
     * @param string $method The HTTP request method.
     * @param string|null $id The ID of the player.
     */
    public function handlePlayerRequest(string $method, ?string $id): void 
    {
        $product = $this->gateway->get($id);
        if(!$product) {
            ErrorCodeHelper::getInstance()->handleErrorCode(404, "Player not found");
        }
        switch($method) {
            case "GET":
                echo json_encode($product);
                break;
            case "PATCH":
                $data = json_decode(file_get_contents('php://input'), true);
                if (json_last_error() !== JSON_ERROR_NONE) {
                    ErrorCodeHelper::getInstance()->handleErrorCode(400,'Invalid JSON format');
                }
                $errors = $this->getValidationErrors($data, false);
                if(!empty($errors)) {
                    ErrorCodeHelper::getInstance()->handleErrorCode(422, json_encode(["errors" => $errors]));
                    break;
                }
                $rows = $this->gateway->update($id, $data);

                echo json_encode([
                    "message" => "Player updated",
                    "rows" => $rows
                ]);
                break;
            case "DELETE":
                $rows = $this->gateway->delete($id);

                echo json_encode([
                    "message" => "Player deleted",
                    "rows" => $rows
                ]);
                break;
            default:
                ErrorCodeHelper::getInstance()->handleErrorCode(405, "Method not allowed","Allow: GET, PATCH, DELETE");
                break;

        }
    }
    
    /**
     * Handles requests for a collection of player resources.
     *
     * This function processes requests for a collection of players, supporting GET and POST methods.
     * It responds with the list of players or creates a new player based on the provided data.
     *
     * @param string $method The HTTP request method.
     * @param string|null $id The ID of the player.
     */
    public function handlePlayerCollectionRequest(string $method, ?string $id): void 
    {
        switch($method) {
            case "GET":
                echo json_encode($this->gateway->getAll());
                break;
            case "POST":
                $data = json_decode(file_get_contents('php://input'), true);
                if (json_last_error() !== JSON_ERROR_NONE) {
                    ErrorCodeHelper::getInstance()->handleErrorCode(400,'Invalid JSON format');
                }
                $errors = $this->getValidationErrors($data);
                if(!empty($errors)) {
                    ErrorCodeHelper::getInstance()->handleErrorCode(422, json_encode(["errors" => $errors]));
                    break;
                }
                $id = $this->gateway->create($data);

                echo json_encode([
                    "message" => "Player created",
                    "id" => $id
                ]);
                break;
            default:
                ErrorCodeHelper::getInstance()->handleErrorCode(405, "Method not allowed", "Allow: GET, POST");
                break;

        }
    }

    /**
     * Validates player data for required fields.
     *
     * This function checks the provided data for validation errors, such as missing required fields
     *
     * @param array $data The player data to validate.
     * @param bool $isNew Whether the validation is for a new player or an existing player.
     *
     * @return array Returns an array of validation errors.
     */
    private function getValidationErrors(array $data, bool $isNew = true) : array
    {
        $errors = [];
        if($isNew && empty($data["name"])) 
        {
            $errors[] = "Name is required";
        }

        return $errors;
    }
}