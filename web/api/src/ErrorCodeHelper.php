<?php
/*
 * Author: Melvin
 * Date: October 14, 2024
 * 
 * An Errorcodehelper class to handle error codes when manually thrown to allow custom json response messages in these cases.
 * 
 * License:
 * This project is licensed under the MIT License - see the LICENSE file for details.
 */
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


    /**
     * Handles HTTP error codes and returns a JSON response.
     *
     * This function sets the HTTP response code, optionally adds a header,
     * and returns a JSON-encoded error message.
     *
     * @param int $code The HTTP response code to set (e.g., 404, 500).
     * @param string $msg The error message to include in the response body. Default is an empty string.
     * @param string $header Optional. A custom header to be sent. Default is null.
     */
    public function handleErrorCode(int $code, ?string $msg = "", ?string $header = ""): void
    {
        http_response_code($code);
        if($header) {
            header($header);
        }
        echo json_encode([
            "code" => $code,
            "message" => $msg
        ]);

        // header("Content-Type: text/html; charset=UTF-8");
        // echo <<<HTML
        //     <html>
        //         <head>
        //             <style>
        //                 body {
        //                     background-color: black;
        //                     margin: 0;
        //                     height: 100vh;
        //                     display: flex;
        //                     justify-content: center;
        //                     align-items: center;
        //                 }

        //                 .container {
        //                     display: flex;
        //                     flex-direction: column;
        //                     align-items: center;
        //                     color: white;
        //                 }
        //             </style>
        //         </head>
        //         <body>
        //             <div class="container">
        //                 <img src='https://http.cat/$code' alt='HTTP Cat'>
        //                 <p>$msg</p>
        //             </div>
        //         </body>
        //     </html>
        // HTML;
    }
}