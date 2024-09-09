<?php

class RequestController {
    public function handleRequest(string $method, ?string $id) : void
    {
        if($id) {
            // Single resource
            $this->handleResourceRequest($method, $id);
        } else {
            // Collection of resources
            $this->handleCollectionRequest($method, $id);
        }
    }

    public function handleResourceRequest(string $method, ?string $id): void 
    {

    }
    
    public function handleCollectionRequest(string $method, ?string $id): void 
    {
        switch($method) {
            case "GET":
                echo json_encode(["id" => 123]);
                break;
        }
    }
}