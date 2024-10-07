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

    /**
     * Get the controller based on the provided API route.
     *
     * @param string $route The received API route
     * @return object The controller corresponding to the given API route.
     * 
     * @output 501 If the functionality for the requested route is not implemented.
     * @output 404 If an invalid route is requested.
     */
    public function getController($route): object
    {
        $db = new Database();
        switch ($route) {
            case "player":
                $gateway = new PlayerGateway($db);
                return new PlayerController($gateway);
            case "score":
                $gateway = new ScoreGateway($db);
                return new ScoreController($gateway);
            case "session":
                $gateway = new SessionGateway($db);
                return new SessionController($gateway);
            case "difficulty":
                $gateway = new DifficultyGateway($db);
                return new DifficultyController($gateway);
            default:
                ErrorCodeHelper::getInstance()->handleErrorCode(404, "Invalid route requested");
                exit;
        }
    }
}