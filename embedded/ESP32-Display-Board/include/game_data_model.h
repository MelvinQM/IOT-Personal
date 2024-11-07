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
    /**
     * @typedef {Object} GyroData
     * @property {int} x - The X-axis value from the gyroscope.
     * @property {int} y - The Y-axis value from the gyroscope.
     */
    struct GyroData {
        int x;
        int y;
    };

    /**
     * @typedef {Object} JoystickData
     * @property {float} x - The X-axis value from the joystick.
     * @property {float} y - The Y-axis value from the joystick.
     */
    struct JoystickData {
        float x;
        float y;
    };

    JoystickData jData;
    GyroData gData;
    bool triggerPressed;
    bool joystickClicked;

public:
    /**
     * Returns the single instance of the GameDataModel class.
     * Implements the singleton pattern to ensure only one instance exists.
     * @returns {GameDataModel} The instance of GameDataModel.
     */
    static GameDataModel& getInstance() {
        static GameDataModel instance;
        return instance;
    }

    /**
     * Gets the X-axis value of the joystick.
     * @returns {float} The X-axis value of the joystick.
     */
    float getJoystickX()
    {
        return jData.x;
    }

    /**
     * Gets the Y-axis value of the joystick.
     * @returns {float} The Y-axis value of the joystick.
     */
    float getJoystickY()
    {
        return jData.y;
    }

    /**
     * Gets the X-axis value of the gyroscope.
     * @returns {float} The X-axis value of the gyroscope.
     */
    float getGyroX()
    {
        return gData.x;
    }

    /**
     * Gets the Y-axis value of the gyroscope.
     * @returns {float} The Y-axis value of the gyroscope.
     */
    float getGyroY()
    {
        return gData.y;
    }

    /**
     * Checks if the trigger button is pressed.
     * @returns {boolean} True if the trigger is pressed, false otherwise.
     */
    bool getTriggerPressed()
    {
        return triggerPressed;  ///< Return the state of the trigger button
    }

    /**
     * Checks if the joystick button is clicked.
     * @returns {boolean} True if the joystick is clicked, false otherwise.
     */
    bool getJoystickClicked()
    {
        return joystickClicked;  ///< Return the state of the joystick button
    }

    /**
     * Sets the joystick data.
     * @param {JoystickData} jData - The new joystick data to set.
     */
    void setJoystickData(JoystickData jData)
    {
        this->jData = jData;  ///< Set the joystick data
    }

    /**
     * Sets the gyroscope data.
     * @param {GyroData} gData - The new gyroscope data to set.
     */
    void setGyroData(GyroData gData)
    {
        this->gData = gData;  ///< Set the gyroscope data
    }

    /**
     * Sets the trigger button state.
     * @param {boolean} triggerPressed - The new state of the trigger button.
     */
    void setTriggerPressed(bool triggerPressed)
    {
        this->triggerPressed = triggerPressed;  ///< Set the state of the trigger button
    }

    /**
     * Sets the joystick button state.
     * @param {boolean} joystickClicked - The new state of the joystick button.
     */
    void setJoystickClicked(bool joystickClicked)
    {
        this->joystickClicked = joystickClicked;  ///< Set the state of the joystick button
    }
};

#endif
