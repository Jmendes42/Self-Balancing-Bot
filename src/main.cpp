
#include "Robot.h"
#include "BluetoothSerial.h"


int constexpr scl = 22;
int constexpr sda = 21;

int constexpr in1 = 18;
int constexpr in2 = 5;
int constexpr in3 = 17;
int constexpr in4 = 16;
int constexpr enableA = 19;
int constexpr enableB = 4;

int constexpr encoderA = 34;
int constexpr encoderB = 35;
int constexpr encoderC = 27;
int constexpr encoderD = 12;

Robot robot(
    {in1, in2, enableA, encoderA, encoderB},
    {in3, in4, enableB, encoderC, encoderD},
    sda, scl
);

BluetoothSerial SerialBT;

void setup()
{
    Serial.begin(115200);
    robot.setUp();
}

// void printValues(float const error, double const proportional, double const integral, double const derivative, double const sum, int const pwm)
// {
//     Serial.print("error: ");
//     Serial.println(error);
//
//     Serial.print("proportional: ");
//     Serial.println(proportional);
//
//     Serial.print("integral: ");
//     Serial.println(integral);
//
//     Serial.print("derivative: ");
//     Serial.println(derivative);
//
//     Serial.print("sum: ");
//     Serial.println(sum);
//
//     Serial.print("pwm: ");
//     Serial.println(pwm);
//     Serial.println("-------------------------");
// }

void loop()
{
    robot.run();
}
