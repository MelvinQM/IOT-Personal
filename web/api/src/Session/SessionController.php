<?php

class SessionController {
    public function __construct(private SessionGateway $gateway) {}

    /**
     * Handles HTTP requests for either a single session or a collection of session based on the provided ID.
     *
     * If an ID is provided, it routes the request to handle a single session resource; otherwise,
     * it handles requests for a collection of session resources.
     *
     * @param string $method The HTTP request method.
     * @param string|null $id The ID of the session. Null for collection requests.
     */
    public function handleRequest(string $method, ?string $id) : void
    {
        if($id) {
            // Single resource
            $this->handleSessionRequest($method, $id);
        } else {
            // Collection of resources
            $this->handleSessionCollectionRequest($method, $id);
        }
    }

    /**
     * Handles requests for a single session.
     *
     * This function processes requests for a specific session, identified by the ID.
     * It supports GET, PATCH, and DELETE methods, responding with appropriate data or errors.
     *
     * @param string $method The HTTP request method.
     * @param string|null $id The ID of the session.
     */
    public function handleSessionRequest(string $method, ?string $id): void 
    {
        $product = $this->gateway->get($id);
        if(!$product) {
            ErrorCodeHelper::getInstance()->handleErrorCode(404, "Session not found");
        }
        switch($method) {
            case "GET":
                echo json_encode($product);
                break;
            case "PATCH":
                ErrorCodeHelper::getInstance()->handleErrorCode(501, "PATCH not implemented");
                // $data = json_decode(file_get_contents('php://input'), true);
                // if (json_last_error() !== JSON_ERROR_NONE) {
                //     ErrorCodeHelper::getInstance()->handleErrorCode(400,'Invalid JSON format');
                // }
                // $errors = $this->getValidationErrors($data, false);
                // if(!empty($errors)) {
                //     ErrorCodeHelper::getInstance()->handleErrorCode(422, json_encode(["errors" => $errors]));
                //     break;
                // }
                // $rows = $this->gateway->update($id, $data);

                // echo json_encode([
                //     "message" => "Session updated",
                //     "rows" => $rows
                // ]);
                // break;
            case "DELETE":
                $rows = $this->gateway->delete($id);

                echo json_encode([
                    "message" => "Session deleted",
                    "rows" => $rows
                ]);
                break;
            default:
                ErrorCodeHelper::getInstance()->handleErrorCode(405, "Method not allowed","Allow: GET, PATCH, DELETE");
                break;

        }
    }
    
    /**
     * Handles requests for a collection of session resources.
     *
     * This function processes requests for a collection of sessions, supporting GET and POST methods.
     * It responds with the list of sessions or creates a new session based on the provided data.
     *
     * @param string $method The HTTP request method.
     * @param string|null $id The ID of the session.
     */
    public function handleSessionCollectionRequest(string $method, ?string $id): void 
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
                    "message" => "Session created",
                    "id" => $id
                ]);
                break;
            default:
                ErrorCodeHelper::getInstance()->handleErrorCode(405, "Method not allowed", "Allow: GET, POST");
                break;

        }
    }

    /**
     * Validates session data for required fields.
     *
     * This function checks the provided data for validation errors, such as missing required fields
     *
     * @param array $data The session data to validate.
     * @param bool $isNew Whether the validation is for a new session or an existing session.
     *
     * @return array Returns an array of validation errors.
     */
    private function getValidationErrors(array $data, bool $isNew = true) : array
    {
        $errors = [];
        if($isNew && empty($data["difficulty_id"])) 
        {
            $errors[] = "difficulty_id is required";
        }

        return $errors;
    }
}