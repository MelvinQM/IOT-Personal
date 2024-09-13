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
    // -76	-2359	1688	0	0	0
    Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
    Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
    Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
    Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
    Serial.print("\n");
    // accelgyro.setXGyroOffset(220);
    // accelgyro.setYGyroOffset(76);
    // accelgyro.setZGyroOffset(-85);
    Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
    Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
    Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
    Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
    Serial.print("\n");

    // configure Arduino LED pin for output
    pinMode(LED_PIN, OUTPUT);
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
    data.X = map(gx, -17000, 17000, 0, 255 ); // X axis data
    data.Y = map(gy, -17000, 17000, 0, 255); 
    data.Z = map(gz, -17000, 17000, 0, 255);  // Y axis data
    delay(500);

    // these methods (and a few others) are also available
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);

    #ifdef OUTPUT_READABLE_ACCELGYRO
        // display tab-separated accel/gyro x/y/z values
        // Serial.print("a/g:\t");
        // Serial.print(ax); Serial.print("\t");
        // Serial.print(ay); Serial.print("\t");
        // Serial.print(az); Serial.print("\t");
        // Serial.print(gx); Serial.print("\t");
        // Serial.print(gy); Serial.print("\t");
        // Serial.println(gz);
        Serial.print("Axis X = ");
        Serial.print(data.X);
        Serial.print("  ");
        Serial.print("Axis Y = ");
        Serial.print(data.Y);
        Serial.print("  ");
        Serial.print("Axis Z  = ");
        Serial.println(data.Z);
    #endif

    #ifdef OUTPUT_BINARY_ACCELGYRO
        Serial.write((uint8_t)(ax >> 8)); Serial.write((uint8_t)(ax & 0xFF));
        Serial.write((uint8_t)(ay >> 8)); Serial.write((uint8_t)(ay & 0xFF));
        Serial.write((uint8_t)(az >> 8)); Serial.write((uint8_t)(az & 0xFF));
        Serial.write((uint8_t)(gx >> 8)); Serial.write((uint8_t)(gx & 0xFF));
        Serial.write((uint8_t)(gy >> 8)); Serial.write((uint8_t)(gy & 0xFF));
        Serial.write((uint8_t)(gz >> 8)); Serial.write((uint8_t)(gz & 0xFF));
    #endif

    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
}