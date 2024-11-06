<?php
/*
 * Author: Melvin Moes
 * Date: October 23, 2024
 * Description:A controller managing the connection to the Actions table of a database. This controller needs a gateway to handle it's sql calls.
 * License: This project is licensed under the MIT License.
 */
class ActionsController {
    public function __construct(private ActionsGateway $gateway) {}


    public function handleRequest(string $method, ?string $action, ?array $filters = []) : void
    {
        if($action == null) {
            ErrorCodeHelper::getInstance()->handleErrorCode(405, "No Action Specified");
            exit;
        }

        switch($method)
        {
            case "GET":
                $this->handleActionGetRequest($action, $filters);
                break;
            default:
                ErrorCodeHelper::getInstance()->handleErrorCode(405, "Method not allowed","Allow: GET");
                break;


        }
    }

    public function handleActionGetRequest(string $action, ?array $filters = []): void    
    {
        switch(strtolower($action))
        {
            case "gethighscores":
                $product = $this->gateway->getHighscores($filters);
                echo json_encode($product);
                break;
            default:
                ErrorCodeHelper::getInstance()->handleErrorCode(405, "Action doesn't exist",);
                break;
        }
    }
}