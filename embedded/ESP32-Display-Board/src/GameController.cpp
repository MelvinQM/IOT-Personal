#include "GameController.h"

/**
 * DONT FORGET TO CHANGE THE USER_SETUP.H IN THE TFT_eSPI lib inside .pio/libdeps
 */
GameController::GameController() 
{
    Serial.begin(BAUD_RATE);
}
GameController::~GameController()
{
    // Delete the tasks on game exit to free up resources
    // if (BluetoothTaskHandle != NULL) vTaskDelete(BluetoothTaskHandle);
    if (ConnTaskHandle != NULL) vTaskDelete(ConnTaskHandle);
}

void GameController::Init()
{
    xTaskCreatePinnedToCore(
        ConnectionsTask,
        CONN_TASK_NAME,
        CONN_TASK_STACK_SIZE,
        &conn,
        CONN_TASK_PRIORITY,
        &ConnTaskHandle,
        CONN_TASK_CORE
    );
    vTaskDelay(TIMEOUT_DELAY / portTICK_PERIOD_MS);

    Serial.print("Init: Executing on core ");
    Serial.println(xPortGetCoreID());


    sRender.InitializeDisplay(SCREEN_ROTATION, true, TFT_BLACK);
    sRender.SetAxisData(&conn.gyroData, &conn.joystickData);
}

void GameController::Loop()
{
    switch(state)
    {
        case Intro:
            // Intro screen
            ShowIntro();
            break;
        case Playing:
            // Gameplay
            Play();
            break;
        case EndGame:
            // Fill in name
            End();
            break;
        case ShowingHighScores:
            // Show highscores from database
            ShowHighScores();
            break;
        case Restart:
            // Restart? Button
            Restarting();
            break;
        default:
            Serial.println("State Error Unrecognized state: " + state);
            break;    
    }
    vTaskDelay(TIMEOUT_DELAY / portTICK_PERIOD_MS);
}

void GameController::ShowIntro()
{
    Serial.println("------Showing Intro Sequence------");
    state = Playing;
}

void GameController::Play()
{
    Serial.println("------Start Gameplay------");
    
    //TODO: Add settings received from session
    sRender.GameLoop(EASY, true);

    // If game ended setState to End
    state = EndGame;
}

void GameController::End()
{
    Serial.println("------Ending Game------");
}
void GameController::ShowHighScores()
{
    Serial.println("------Showing Highscores------");
}
void GameController::Restarting()
{
    Serial.println("------Restart Sequence------");
}