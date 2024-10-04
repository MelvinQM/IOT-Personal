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
}