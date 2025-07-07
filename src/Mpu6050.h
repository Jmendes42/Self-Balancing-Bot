
#ifndef __MPU_6050_H__
#define __MPU_6050_H__

#include <MPU6050_light.h>
#include <Wire.h>


class Mpu6050
{
public:
    Mpu6050(int sda, int scl);

    void setUp();
    double getRoll();

private:
    double complementaryFilter(double lastAngle);
    void calibrate();

    MPU6050 _mpu;
    u_long _timer;

    double _gyroBias;
    double _accOffset;

    double constexpr _errorOffset = 1.15;
};


#endif
