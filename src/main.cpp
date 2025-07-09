
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
    { in1, in2, in3, in4, enableA, enableB },
    sda, scl
);

void setup()
{
    Serial.begin(115200);
    robot.setUp();
}

void loop()
{
    robot.run();
}
