/*
 * Author: Melvin Moes
 * Date: November 6, 2024
 * Description: An implementation of the Gyroscope header which handles the initialization, data
 * collecting, and processing of gyroscope data from the MPU6050 sensor.
 * License: This project is licensed under the MIT License.
 */

#include "Gyroscope.h"

volatile bool mpuInterrupt = false;  
void IRAM_ATTR dmpDataReady() {
    mpuInterrupt = true;
}

void Gyroscope::init() 
{
    // Initialize I2C
    Wire.begin();
    Wire.setClock(400000);

    // Initialize device
    Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();
    pinMode(GYRO_INTERRUPT_PIN, INPUT);

    // Verify connection
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

    // Load and configure the DMP
    Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();

    // Supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXAccelOffset(-2232.00000);
    mpu.setYAccelOffset(2079.00000);
    mpu.setZAccelOffset(1558.00000);
    mpu.setXGyroOffset(78.00000);
    mpu.setYGyroOffset(1.00000);
    mpu.setZGyroOffset(19.00000);

    if (devStatus == 0) {
        // Calibration Time: generate offsets and calibrate our MPU6050
        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
        mpu.PrintActiveOffsets();

        // Turn on the DMP
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        // Enable Arduino interrupt detection
        Serial.print(F("Enabling interrupt detection (Arduino external interrupt "));
        Serial.print(digitalPinToInterrupt(GYRO_INTERRUPT_PIN));
        Serial.println(F(")..."));
        attachInterrupt(digitalPinToInterrupt(GYRO_INTERRUPT_PIN), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;

        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }
}

void Gyroscope::loop()
{
    if (!dmpReady) return;
    
    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
        #ifdef OUTPUT_READABLE_QUATERNION
            // Display quaternion values in easy matrix form: w x y z
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            Serial.print("quat\t");
            Serial.print(q.w);
            Serial.print("\t");
            Serial.print(q.x);
            Serial.print("\t");
            Serial.print(q.y);
            Serial.print("\t");
            Serial.println(q.z);
        #endif

        #ifdef OUTPUT_READABLE_EULER
            // Display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetEuler(euler, &q);
            Serial.print("euler\t");
            Serial.print(euler[0] * 180/M_PI);
            Serial.print("\t");
            Serial.print(euler[1] * 180/M_PI);
            Serial.print("\t");
            Serial.println(euler[2] * 180/M_PI);
        #endif

        #ifdef OUTPUT_READABLE_YAWPITCHROLL
            // Display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            // Serial.print("ypr\t");
            // Serial.print(ypr[0] * 180/M_PI);
            // Serial.print("\t");
            // Serial.print(ypr[1] * 180/M_PI);
            // Serial.print("\t");
            // Serial.println(ypr[2] * 180/M_PI);
        #endif

        #ifdef OUTPUT_READABLE_REALACCEL
            // Display real acceleration, adjusted to remove gravity
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetAccel(&aa, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
            Serial.print("areal\t");
            Serial.print(aaReal.x);
            Serial.print("\t");
            Serial.print(aaReal.y);
            Serial.print("\t");
            Serial.println(aaReal.z);
        #endif

        #ifdef OUTPUT_READABLE_WORLDACCEL
            // Display initial world-frame acceleration
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetAccel(&aa, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
            mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
            Serial.print("aworld\t");
            Serial.print(aaWorld.x);
            Serial.print("\t");
            Serial.print(aaWorld.y);
            Serial.print("\t");
            Serial.println(aaWorld.z);
        #endif
    }
}

GyroData Gyroscope::getXY() 
{    
    // Calculate offsets
    float offsetX = ypr[2] * sensitivity;
    float offsetY = ypr[0] * sensitivity;

    // Center cursor coordinate and then apply offset
    float screenX = (screenWidth / 2) - offsetX;
    float screenY = (screenHeight / 2) + offsetY;
    
    // Clamp value between 0 and width/height
    screenX = clamp(screenX, 0.0f, 320.0f);
    screenY = clamp(screenY, 0.0f, 240.0f);

    return {static_cast<int>(screenX), static_cast<int>(screenY)};;
}