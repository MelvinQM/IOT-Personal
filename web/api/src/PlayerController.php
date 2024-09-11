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
                    ErrorCodeHelper::getInstance()->handleErrorCode(422, "");
                    echo json_encode(["errors" => $errors]);
                    break;
                }
                $id = $this->gateway->create($data);

                echo json_encode([
                    "message" => "Product created",
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

    private function getValidationErrors(array $data) : array
    {
        $errors = [];
        if(empty($data["name"])) 
        {
            $errors[] = "Name is required";
        }

        return $errors;
    }
}