<?php
/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: A controller managing the connection to the Score table of a database. This controller needs a gateway to handle it's sql calls.
 * License: This project is licensed under the MIT License.
 */
class ScoreController {
    public function __construct(private ScoreGateway $gateway) {}

    /**
     * Handles HTTP requests for either a single score or a collection of score based on the provided ID.
     *
     * If an ID is provided, it routes the request to handle a single score resource; otherwise,
     * it handles requests for a collection of score resources.
     *
     * @param string $method The HTTP request method.
     * @param string|null $id The ID of the score. Null for collection requests.
     */
    public function handleRequest(string $method, ?string $id, ?array $filters = []) : void
    {
        if($id) {
            // Single resource
            $this->handleScoreRequest($method, $id);
        } else {
            // Collection of resources
            $this->handleScoreCollectionRequest($method, $filters);
        }
    }

    /**
     * Handles requests for a single score.
     *
     * This function processes requests for a specific score, identified by the ID.
     * It supports GET, PATCH, and DELETE methods, responding with appropriate data or errors.
     *
     * @param string $method The HTTP request method.
     * @param string|null $id The ID of the score.
     */
    public function handleScoreRequest(string $method, ?string $id): void 
    {
        $product = $this->gateway->get($id);
        if(!$product) {
            ErrorCodeHelper::getInstance()->handleErrorCode(404, "Score not found");
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
                    "message" => "Score updated",
                    "rows" => $rows
                ]);
                break;
            case "DELETE":
                $rows = $this->gateway->delete($id);

                echo json_encode([
                    "message" => "Score deleted",
                    "rows" => $rows
                ]);
                break;
            default:
                ErrorCodeHelper::getInstance()->handleErrorCode(405, "Method not allowed","Allow: GET, PATCH, DELETE");
                break;

        }
    }
    
    /**
     * Handles requests for a collection of score resources.
     *
     * This function processes requests for a collection of scores, supporting GET and POST methods.
     * It responds with the list of score or creates a new score based on the provided data.
     *
     * @param string $method The HTTP request method.
     * @param string|null $id The ID of the score.
     */
    public function handleScoreCollectionRequest(string $method, ?array $filters): void 
    {
        switch($method) {
            case "GET":
                echo json_encode($this->gateway->getAll($filters));
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
                    "message" => "Score created",
                    "id" => $id
                ]);
                break;
            default:
                ErrorCodeHelper::getInstance()->handleErrorCode(405, "Method not allowed", "Allow: GET, POST");
                break;

        }
    }

    /**
     * Validates score data for required fields.
     *
     * This function checks the provided data for validation errors, such as missing required fields
     *
     * @param array $data The score data to validate.
     * @param bool $isNew Whether the validation is for a new score or an existing score.
     *
     * @return array Returns an array of validation errors.
     */
    private function getValidationErrors(array $data, bool $isNew = true) : array
    {
        $errors = [];
        if($isNew && (!isset($data["score"]) || $data["score"] === null)) 
        {
            $errors[] = "score is required";
        }

        if($isNew && empty($data["session_id"]))
        {
            $errors[] = "session_id is required";
        }

        return $errors;
    }
}