
#include "Mpu6050.h"


Mpu6050::Mpu6050(int const sda, int const scl)
    : _mpu(Wire)
    , _timer(0)
    , _gyroBias(0)
    , _accOffset(0)
{
    Wire.begin(sda, scl);
}

void Mpu6050::setUp()
{
    byte const status = _mpu.begin();
    delay(250);
    if (status != 0)
    {
        Serial.println("MPU6050 init failed!");
        delay(1000);
    }
}

double Mpu6050::getRoll()
{
    _mpu.update();
    static double roll = 0.0f;

    roll = complementaryFilter(roll);
    _timer = millis();

    return roll + _errorOffset;             // Change with the calibrated values from calibrate()
}

double Mpu6050::complementaryFilter(double const lastAngle)
{
    double constexpr alpha = 0.93;
    double const dt = (millis() - _timer) / 1000.0;
    double const correctedGyro = _mpu.getGyroY() - _gyroBias;

    return alpha * (lastAngle + correctedGyro * dt) + (1 - alpha) * (_mpu.getAccAngleY() - _accOffset);
}

void Mpu6050::calibrate()
{
    double gyroCalibrationRate = 0.0;
    double accCalibrationRate = 0.0;
    int constexpr samples = 500;

    for (int i = 0; i <= samples; i++)
    {
        _mpu.update();
        gyroCalibrationRate += _mpu.getGyroY();
        accCalibrationRate += _mpu.getAccAngleY();
        delay(1);
    }

    _gyroBias = gyroCalibrationRate / samples;
    _accOffset = accCalibrationRate / samples;
}
