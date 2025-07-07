
#include "PidCalculator.h"

#include <Arduino.h>


PidCalculator::PidCalculator(double const kp, double const ki, double const kd)
    : _kp(kp)
    , _ki(ki)
    , _kd(kd)
{
}

double PidCalculator::getResult(double const error)
{
    unsigned long const currentTime = millis();
    double const deltaTime = (currentTime - _previousTime) / 1000.0;
    _previousTime = currentTime;

    double const proportional = getProportional(error);
    double const integral = getIntegral(error, deltaTime);
    double const derivative = getDerivative(error, deltaTime);

    _previousError = error;

    return proportional + integral + derivative;
}

void PidCalculator::reset()
{
    _integralAccumulation = 0.0;
    _previousError = 0.0;
    _previousTime = 0;
}

void PidCalculator::setGains(double const kp, double const ki, double const kd)
{
    _kp = kp;
    _ki = ki;
    _kd = kd;
}

double PidCalculator::getProportional(double const error) const
{
    return error * _kp;
}

double PidCalculator::getIntegral(double const error, double const deltaTime)
{
    _integralAccumulation += error * deltaTime;
    _integralAccumulation = constrain(_integralAccumulation, -300.0, 300.0);

    return _ki * _integralAccumulation;
}

double PidCalculator::getDerivative(double const error, double const deltaTime) const
{
    double const derivative = (error - _previousError) / deltaTime;
    return _kd * derivative;
}
