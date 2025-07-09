
#include "Robot.h"


void IRAM_ATTR Robot::imuReadIsr()
{
    imuUpdateFlag = true;
}

volatile bool Robot::imuUpdateFlag = false;

Robot::Robot(MotorsDriver::MotorPins const& pins, int sda, int scl)
    : _motors(pins)
    , _imu(sda, scl)
    , _pidBalance(0.0, 0.0, 0.0)
{
}

void Robot::setUp()
{
    _bluetooth.serialSetup();
    _motors.setUp();
    _imu.setUp();
    setTimerIsr();
}

void Robot::run()
{
    if (_bluetooth.serialAvailable())
    {
        readFromBluetooth();
    }
    if (imuUpdateFlag)
    {
        imuUpdateFlag = false;
        balance();
        Serial.println(_imu.getRoll());
    }
}

void Robot::balance()
{
    double const roll = _imu.getRoll();
    double const output =  _pidBalance.getResult(roll);

    if (abs(roll) > 0.5)
    {
        int const velocity = static_cast<int>(abs(output));
        if (_imu.getRoll() > 0)
        {
            moveForward(velocity);
        }
        else
        {
            moveBackward(velocity);
        }
    }
    else
    {
        stop();
    }
}

void Robot::moveForward(int const velocity)
{
    _motors.moveForward(velocity);
}

void Robot::moveBackward(int const velocity)
{
    _motors.moveBackward(velocity);
}

void Robot::stop()
{
    _motors.stop();
}

void Robot::readFromBluetooth()
{
    String const message = _bluetooth.getString();
    if (message.startsWith("PID"))
    {
        int const kpIndex = message.indexOf("kp = ");
        int const kiIndex = message.indexOf("ki = ");
        int const kdIndex = message.indexOf("kd = ");
        if (kpIndex != -1 && kiIndex != -1 && kdIndex != -1)
        {
            String const kp = message.substring(kpIndex + 5, kiIndex - 1);
            String const ki = message.substring(kiIndex + 5, kdIndex - 1);
            String const kd = message.substring(kdIndex + 5);

            _pidBalance.setGains(kp.toDouble(), ki.toDouble(), kd.toDouble());
        }
    }
}

void Robot::setTimerIsr()
{
    hw_timer_t* timer0Cfg = nullptr;
    timer0Cfg = timerBegin(0, 80, true);
    timerAttachInterrupt(timer0Cfg, &imuReadIsr, true);
    timerAlarmWrite(timer0Cfg, 5000, true);
    timerAlarmEnable(timer0Cfg);
}
