<?php

class RouteHandler {
    private static $instances = [];
    public static function getInstance(): RouteHandler
    {
        $cls = static::class;
        if (!isset(self::$instances[$cls])) {
            self::$instances[$cls] = new static();
        }

        return self::$instances[$cls];
    }

    public function getAllRoutes(): array
    {
        return ["player", "scores", "difficulty", "session"];
    }

    public function getController($route): object
    {
        $db = new Database();
        switch ($route) {
            case "player":
                $gateway = new PlayerGateway($db);
                return new PlayerController($gateway);
            case "scores":
                ErrorCodeHelper::getInstance()->handleErrorCode(501, "Scores functionality not implemented yet");
                exit;
            case "session":
                ErrorCodeHelper::getInstance()->handleErrorCode(501, "Session functionality not implemented yet");
                exit;
            case "difficulty":
                ErrorCodeHelper::getInstance()->handleErrorCode(501, "Difficulty functionality not implemented yet");
                exit;
            default:
                ErrorCodeHelper::getInstance()->handleErrorCode(404, "Invalid route requested");
                exit;
        }
    }
}