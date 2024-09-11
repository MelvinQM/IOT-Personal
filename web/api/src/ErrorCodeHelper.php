<?php

class ErrorCodeHelper {
    private static $instances = [];
    public static function getInstance(): ErrorCodeHelper
    {
        $cls = static::class;
        if (!isset(self::$instances[$cls])) {
            self::$instances[$cls] = new static();
        }

        return self::$instances[$cls];
    }

    public function handleErrorCode(int $code, ?string $msg): void
    {
        http_response_code($code);
        header("Content-Type: text/html; charset=UTF-8");
        if($msg) {
            header($msg);
        }
        echo "
        <html>
            <head>
                <style>
                    body {
                        background-color: black;
                        margin: 0;
                        height: 100vh;
                        display: flex;
                        justify-content: center;
                        align-items: center;
                    }
                </style>
            </head>
            <body>
                <img src='https://http.cat/$code'>
            </body>
        </html>";
    }
}