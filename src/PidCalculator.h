
#ifndef __PID_CALCULATOR_H__
#define __PID_CALCULATOR_H__

class PidCalculator
{
public:
    PidCalculator(double kp, double ki, double kd);

    double getResult(double error);
    void reset();

    void setGains(double kp, double ki, double kd);

private:
    double getProportional(double error) const;
    double getIntegral(double error, double deltaTime);
    double getDerivative(double error, double deltaTime) const;

    double _kp;
    double _ki;
    double _kd;

    double _integralAccumulation = 0.0;
    double _previousError = 0.0;
    unsigned long _previousTime = 0;
};


#endif
