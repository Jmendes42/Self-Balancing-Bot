
#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "Bluetooth.h"
#include "MotorsDriver.h"
#include "Mpu6050.h"
#include "PidCalculator.h"

class Robot
{
public:
    Robot(MotorsDriver::MotorPins const& pins, int sda, int scl);

    void setUp();
    void run();

    static void IRAM_ATTR imuReadIsr();
    static volatile bool imuUpdateFlag;

private:
    void balance();
    void moveForward(int velocity);
    void moveBackward(int velocity);
    void stop();

    void readFromBluetooth();
    void setTimerIsr();

    Bluetooth _bluetooth;
    MotorsDriver _motors;
    Mpu6050 _imu;
    PidCalculator _pidBalance;
};


#endif
