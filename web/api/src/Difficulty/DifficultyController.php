<?php
/*
 * Author: Melvin
 * Date: October 14, 2024
 * Description:A controller managing the connection to the Difficulty table of a database. This controller needs a gateway to handle it's sql calls.
 * License: This project is licensed under the MIT License.
 */
class DifficultyController {
    public function __construct(private DifficultyGateway $gateway) {}

    /**
     * Handles HTTP requests for either a single difficulty or a collection of difficulty based on the provided ID.
     *
     * If an ID is provided, it routes the request to handle a single difficulty resource; otherwise,
     * it handles requests for a collection of difficulty resources.
     *
     * @param string $method The HTTP request method.
     * @param string|null $id The ID of the difficulty. Null for collection requests.
     */
    public function handleRequest(string $method, ?string $id) : void
    {
        if($id) {
            // Single resource
            $this->handleDifficultyRequest($method, $id);
        } else {
            // Collection of resources
            $this->handleDifficultyCollectionRequest($method, $id);
        }
    }

    /**
     * Handles requests for a single difficulty.
     *
     * This function processes requests for a specific difficulty, identified by the ID.
     * It supports GET, PATCH, and DELETE methods, responding with appropriate data or errors.
     *
     * @param string $method The HTTP request method.
     * @param string|null $id The ID of the difficulty.
     */
    public function handleDifficultyRequest(string $method, ?string $id): void 
    {
        $product = $this->gateway->get($id);
        if(!$product) {
            ErrorCodeHelper::getInstance()->handleErrorCode(404, "Difficulty not found");
        }
        switch($method) {
            case "GET":
                echo json_encode($product);
                break;
            default:
                ErrorCodeHelper::getInstance()->handleErrorCode(405, "Method not allowed","Allow: GET");
                break;

        }
    }
    
    /**
     * Handles requests for a collection of difficulties resources.
     *
     * This function processes requests for a collection of difficulty, supporting the GET method.
     * It responds with the list of difficulties.
     *
     * @param string $method The HTTP request method.
     * @param string|null $id The ID of the difficulty.
     */
    public function handleDifficultyCollectionRequest(string $method, ?string $id): void 
    {
        switch($method) {
            case "GET":
                echo json_encode($this->gateway->getAll());
                break;
            default:
                ErrorCodeHelper::getInstance()->handleErrorCode(405, "Method not allowed", "Allow: GET");
                break;

        }
    }

}