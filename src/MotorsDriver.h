
#ifndef __MOTORS_DRIVER_H__
#define __MOTORS_DRIVER_H__

#include <cstdint>
#include <esp_attr.h>


class MotorsDriver
{
public:
    struct MotorPins { int in1; int in2; int in3; int in4; int enableA; int enableB; };

    MotorsDriver(MotorPins const& pins);

    void setUp() const;

    void moveForward(int velocity) const;
    void moveBackward(int velocity) const;
    void stop() const;

private:
    void setDirection(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4) const;
    void move(int velocity) const;
    MotorPins _pins;

    int const _velocityOffset = 100;
};



#endif
