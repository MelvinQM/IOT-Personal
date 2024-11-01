/*
 * Author: Melvin Moes
 * Date: October 18, 2024
 * Description: This class, GameDataModel, implements a singleton pattern to store game data.
 * It captures joystick and gyroscope data along with button states from the controller. The class provides
 * getter and setter methods to access and update these values.
 * License: This project is licensed under the MIT License.
 */

#ifndef GAME_DATA_MODEL_H
#define GAME_DATA_MODEL_H

class GameDataModel
{
private:

    // Defining data structures
    struct GyroData {
        int x;
        int y;
    };

    struct JoystickData {
        float x;
        float y;
    };

    JoystickData jData;
    GyroData gData;
    bool buttonPressed;
    bool joystickClicked;

public:
    static GameDataModel& getInstance() {
        static GameDataModel instance;
        return instance;
    }

    float getJoystickX()
    {
        return jData.x;
    }

    float getJoystickY()
    {
        return jData.y;
    }

    float getGyroX()
    {
        return gData.x;
    }

    float getGyroY()
    {
        return gData.y;
    }

    bool getTriggerPress()
    {
        return buttonPressed;
    }

    bool getJoystickClicked()
    {
        return joystickClicked;
    }

    void setJoystickData(JoystickData jData)
    {
        this->jData = jData;
    }

    void setGyroData(GyroData gData)
    {
        this->gData = gData;
    }

    void setTriggerPressed(bool buttonPressed)
    {
        this->buttonPressed = buttonPressed;
    }

    void setJoystickClicked(bool joystickClicked)
    {
        this->joystickClicked = joystickClicked;
    }
};

#endif
