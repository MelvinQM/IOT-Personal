<?php

class ErrorHandler 
{
    /**
     * Handles uncaught exceptions and returns a JSON-encoded error response.
     *
     * This function is used as the exception handler when registered via `set_exception_handler`.
     * It sets the HTTP response code to 500 and outputs a JSON response containing details of the thrown exception.
     *
     * @param Throwable $exception The caught exception to handle, providing details such as the code, message, file, and the line the error occured.
     */
    public static function handleException(Throwable $exception) : void
    {
        http_response_code(500);
        echo json_encode([
            "code" => $exception->getCode(),
            "message" => $exception->getMessage(),
            "file" => $exception->getFile(),
            "line" => $exception->getLine(),
        ]);
    }

    /**
     * Handles errors and converts them into exceptions.
     *
     * This function is used as the global error handler when registered via `set_error_handler`.
     * It throws an ErrorException based on the provided error details.
     *
     * @param int $errno The error severity.
     * @param string $errstr The error message.
     * @param string $errfile The filename in which the error occurred.
     * @param int $errline The line number where the error occurred.
     *
     * @throws ErrorException Converts the error into an ErrorException.
     */
    public static function handleError(int $errno, string $errstr, string $errfile, int $errline) : bool
    {
        throw new ErrorException($errstr, 0, $errno, $errfile, $errline);
    }
}