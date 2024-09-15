#include "gyroscope.h"
#include "Wire.h"

MPU6050 accelgyro;

Gyroscope::Gyroscope() 
{

}

Gyroscope::~Gyroscope() 
{

}

void Gyroscope::Init() 
{
    Serial.println("----[Initializing Gyroscope]----");
    Wire.begin();
    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    // use the code below to change accel/gyro offset values
    Serial.println("Updating internal sensor offsets...");
    Serial.println( 
        String(accelgyro.getXAccelOffset()) + "\t" +        // -76
        String(accelgyro.getYAccelOffset()) + "\t" +        // -2359
        String(accelgyro.getZAccelOffset()) + "\t" +        // 1688
        String(accelgyro.getXGyroOffset()) + "\t" +         // 0
        String(accelgyro.getYGyroOffset()) + "\t" +         // 0
        String(accelgyro.getZGyroOffset())                  // 0
    );              

    CalibrateGyro();
    accelgyro.setXGyroOffset(91.00000);
    accelgyro.setYGyroOffset(-5.00000);
    accelgyro.setZGyroOffset(10.00000);
    accelgyro.setZAccelOffset(1574.00000);

    Serial.println( 
        String(accelgyro.getXAccelOffset()) + "\t" +        // -76
        String(accelgyro.getYAccelOffset()) + "\t" +        // -2359
        String(accelgyro.getZAccelOffset()) + "\t" +        // 1688
        String(accelgyro.getXGyroOffset()) + "\t" +         // 0
        String(accelgyro.getYGyroOffset()) + "\t" +         // 0
        String(accelgyro.getZGyroOffset())                  // 0
    );           
}

struct MyData {
  byte X;
  byte Y;
  byte Z;
};

MyData data;
void Gyroscope::Loop()
{
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    // data.X = map(gx, -17000, 17000, 0, 255 ); // X axis data
    // data.Y = map(gy, -17000, 17000, 0, 255); 
    // data.Z = map(gz, -17000, 17000, 0, 255);  // Y axis data
    delay(500);
    
    // these methods (and a few others) are also available
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);

    #ifdef OUTPUT_READABLE_ACCELGYRO
        // display tab-separated accel/gyro x/y/z values
        Serial.print("a/g:\t");
        // Serial.print(ax); Serial.print("\t");
        // Serial.print(ay); Serial.print("\t");
        // Serial.print(az); Serial.print("\t");
        Serial.print(gx); Serial.print("\t");
        Serial.print(gy); Serial.print("\t");
        Serial.println(gz);
        // Serial.print("Axis X = ");
        // Serial.print(data.X);
        // Serial.print("  ");
        // Serial.print("Axis Y = ");
        // Serial.print(data.Y);
        // Serial.print("  ");
        // Serial.print("Axis Z  = ");
        // Serial.println(data.Z);
    #endif

    #ifdef OUTPUT_BINARY_ACCELGYRO
        Serial.write((uint8_t)(ax >> 8)); Serial.write((uint8_t)(ax & 0xFF));
        Serial.write((uint8_t)(ay >> 8)); Serial.write((uint8_t)(ay & 0xFF));
        Serial.write((uint8_t)(az >> 8)); Serial.write((uint8_t)(az & 0xFF));
        Serial.write((uint8_t)(gx >> 8)); Serial.write((uint8_t)(gx & 0xFF));
        Serial.write((uint8_t)(gy >> 8)); Serial.write((uint8_t)(gy & 0xFF));
        Serial.write((uint8_t)(gz >> 8)); Serial.write((uint8_t)(gz & 0xFF));
    #endif
}

void Gyroscope::CalibrateGyro()
{
    accelgyro.CalibrateAccel(6);
    accelgyro.CalibrateGyro(6);
    Serial.println("\nat 600 Readings");
    accelgyro.PrintActiveOffsets();
    Serial.println();
    accelgyro.CalibrateAccel(1);
    accelgyro.CalibrateGyro(1);
    Serial.println("700 Total Readings");
    accelgyro.PrintActiveOffsets();
    Serial.println();
    accelgyro.CalibrateAccel(1);
    accelgyro.CalibrateGyro(1);
    Serial.println("800 Total Readings");
    accelgyro.PrintActiveOffsets();
    Serial.println();
    accelgyro.CalibrateAccel(1);
    accelgyro.CalibrateGyro(1);
    Serial.println("900 Total Readings");
    accelgyro.PrintActiveOffsets();
    Serial.println();    
    accelgyro.CalibrateAccel(1);
    accelgyro.CalibrateGyro(1);
    Serial.println("1000 Total Readings");
    accelgyro.PrintActiveOffsets();
    Serial.println("\n\n Any of the above offsets will work nice \n\n Lets proof the PID tuning using another method:"); 
}