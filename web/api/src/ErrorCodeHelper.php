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

    public function handleErrorCode(int $code, ?string $header = "", ?string $msg = ""): void
    {
        http_response_code($code);
        header("Content-Type: text/html; charset=UTF-8");
        if($header) {
            header($header);
        }
        echo <<<HTML
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

                        .container {
                            display: flex;
                            flex-direction: column;
                            align-items: center;
                            color: white; /* Ensure text is visible on black background */
                        }
                    </style>
                </head>
                <body>
                    <div class="container">
                        <img src='https://http.cat/$code' alt='HTTP Cat'>
                        <p>$msg</p>
                    </div>
                </body>
            </html>
        HTML;
    }
}