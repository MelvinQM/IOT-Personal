<?php

class PlayerController {
    public function __construct(private PlayerGateway $gateway) 
    {
        
    }
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

    public function handlePlayerRequest(string $method, ?string $id): void 
    {
        $product = $this->gateway->get($id);
        if(!$product) {
            ErrorCodeHelper::getInstance()->handleErrorCode(404, "", "Player not found");
        }
        switch($method) {
            case "GET":
                echo json_encode($product);
                break;
            case "PATCH":
                $data = $_GET;
                $errors = $this->getValidationErrors($data, false);
                if(!empty($errors)) {
                    ErrorCodeHelper::getInstance()->handleErrorCode(422, "", json_encode(["errors" => $errors]));
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
                ErrorCodeHelper::getInstance()->handleErrorCode(405, "Allow: GET, PATCH");
                break;

        }
    }
    
    public function handlePlayerCollectionRequest(string $method, ?string $id): void 
    {
        switch($method) {
            case "GET":
                echo json_encode($this->gateway->getAll());
                break;
            case "POST":
                $data = $_GET;
                $errors = $this->getValidationErrors($data);
                if(!empty($errors)) {
                    ErrorCodeHelper::getInstance()->handleErrorCode(422, "", json_encode(["errors" => $errors]));
                    break;
                }
                $id = $this->gateway->create($data);

                echo json_encode([
                    "message" => "Player created",
                    "id" => $id
                ]);
                break;
            // case "DELETE":
            //     echo "DELETE";
            //     break;
            // case "UPDATE":
            //     echo "UPDATE";
            //     break;
            default:
                ErrorCodeHelper::getInstance()->handleErrorCode(405, "Allow: GET, POST");
                break;

        }
    }

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