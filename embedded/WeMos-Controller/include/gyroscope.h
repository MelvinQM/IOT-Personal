#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include "utilities.h"
#include "MPU6050.h"

class Gyroscope {
    public:
        Gyroscope();
        ~Gyroscope();
        void Init();
        void Loop();
        void CalibrateGyro();
    private:
        //MPU6050 accelgyro(0x69); // <-- use for AD0 high
        //MPU6050 accelgyro(0x68, &Wire1); // <-- use for AD0 low, but 2nd Wire (TWI/I2C) object

        int16_t ax, ay, az;
        int16_t gx, gy, gz;

        // uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
        // list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
        // not so easy to parse, and slow(er) over UART.
        #define OUTPUT_READABLE_ACCELGYRO

        // uncomment "OUTPUT_BINARY_ACCELGYRO" to send all 6 axes of data as 16-bit
        // binary, one right after the other. This is very fast (as fast as possible
        // without compression or data loss), and easy to parse, but impossible to read
        // for a human.
        //#define OUTPUT_BINARY_ACCELGYRO


        #define LED_PIN LED_BUILTIN
        bool blinkState = false;
};

#endif