/*
 * Author: Melvin Moes
 * Date: October 14, 2024
 * Description: This header defines the Gyroscope class, which manages communication with the MPU6050 sensor. 
 * The class provides methods for initializing the sensor, reading gyroscope data, and calibrating the gyro. It also handles 
 * the calculation of yaw, pitch, and roll values.
 * License: This project is licensed under the MIT License.
 */

#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include "utilities.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"


class Gyroscope {
    public:
        void Init();
        void Loop();
        void CalibrateGyro();
        GyroData GetXYZ();
    private:
        MPU6050 mpu;
        /**
         * Uncomment "OUTPUT_READABLE_QUATERNION" if you want to see the actual 
         * quaternion components in a [w, x, y, z] format (not best for parsing 
         * on a remote host such as Processing or something though)
         */
        //#define OUTPUT_READABLE_QUATERNION

        /** 
         * Uncomment "OUTPUT_READABLE_EULER" if you want to see Euler angles
         * (in degrees) calculated from the quaternions coming from the FIFO. 
         * Note that Euler angles suffer from gimbal lock (for more info, see
         * http://en.wikipedia.org/wiki/Gimbal_lock)
         */
        //#define OUTPUT_READABLE_EULER

        /** 
         * Uncomment "OUTPUT_READABLE_YAWPITCHROLL" if you want to see the yaw/
         * pitch/roll angles (in degrees) calculated from the quaternions coming
         * from the FIFO. Note this also requires gravity vector calculations.
         * Also note that yaw/pitch/roll angles suffer from gimbal lock (for
         * more info, see: http://en.wikipedia.org/wiki/Gimbal_lock)
         */
        #define OUTPUT_READABLE_YAWPITCHROLL

        /** 
         * Uncomment "OUTPUT_READABLE_REALACCEL" if you want to see acceleration
         * components with gravity removed. This acceleration reference frame is
         * not compensated for orientation, so +X is always +X according to the
         * sensor, just without the effects of gravity. If you want acceleration
         * compensated for orientation, use OUTPUT_READABLE_WORLDACCEL instead.
         */
        //#define OUTPUT_READABLE_REALACCEL

        /** 
         * Uncomment "OUTPUT_READABLE_WORLDACCEL" if you want to see acceleration
         * components with gravity removed and adjusted for the world frame of 
         * reference (yaw is relative to initial orientation, since no magnetometer
         * is present in this case). Could be quite handy in some cases.
         */
        //#define OUTPUT_READABLE_WORLDACCEL

        // MPU control/status vars
        bool dmpReady = false;  // set true if DMP init was successful
        uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
        uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
        uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
        uint16_t fifoCount;     // count of all bytes currently in FIFO
        uint8_t fifoBuffer[64]; // FIFO storage buffer

        // orientation/motion vars
        Quaternion q;           // [w, x, y, z]         quaternion container
        VectorInt16 aa;         // [x, y, z]            accel sensor measurements
        VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
        VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
        VectorFloat gravity;    // [x, y, z]            gravity vector
        float euler[3];         // [psi, theta, phi]    Euler angle container
        float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

        static float clamp(float value, float min, float max) {
            if (value < min) return min;   // If value is less than min, return min
            if (value > max) return max;   // If value is greater than max, return max
            return value;                  // Otherwise, return the original value
        }
};
#endif