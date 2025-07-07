
#ifndef __ROBOT_H__
#define __ROBOT_H__

#include "Bluetooth.h"
#include "Motor.h"
#include "Mpu6050.h"
#include "PidCalculator.h"

class Robot
{
public:
    Robot(Motor::MotorPins const& pinsA, Motor::MotorPins const& pinsB, int sda, int scl);

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
    Motor _motorA;
    Motor _motorB;
    Mpu6050 _imu;
    PidCalculator _pidBalance;
};


#endif
