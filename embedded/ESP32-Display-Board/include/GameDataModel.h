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

    float GetJoystickX()
    {
        return jData.x;
    }

    float GetJoystickY()
    {
        return jData.y;
    }

    float GetGyroX()
    {
        return gData.x;
    }

    float GetGyroY()
    {
        return gData.y;
    }

    bool GetTriggerPress()
    {
        return buttonPressed;
    }

    bool GetJoystickClicked()
    {
        return joystickClicked;
    }

    void SetJoystickData(JoystickData jData)
    {
        this->jData = jData;
    }

    void SetGyroData(GyroData jData)
    {
        this->gData = gData;
    }

    void SetTriggerPressed(bool buttonPressed)
    {
        this->buttonPressed = buttonPressed;
    }

    void SetJoystickClicked(bool joystickClicked)
    {
        this->joystickClicked = joystickClicked;
    }
};

#endif
