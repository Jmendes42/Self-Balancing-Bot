
#include "MotorsDriver.h"

#include <Arduino.h>
#include <esp32-hal-gpio.h>



MotorsDriver::MotorsDriver(MotorPins const& pins)
    : _pins(pins)
{
}

void MotorsDriver::setUp() const
{
    pinMode(_pins.in1, OUTPUT);
    pinMode(_pins.in2, OUTPUT);
    pinMode(_pins.in3, OUTPUT);
    pinMode(_pins.in4, OUTPUT);
    pinMode(_pins.enableA, OUTPUT);
    pinMode(_pins.enableB, OUTPUT);
}

void MotorsDriver::moveForward(int const velocity) const
{
    setDirection(HIGH, LOW, HIGH, LOW);
    move(velocity);
}

void MotorsDriver::moveBackward(int const velocity) const
{
    setDirection(LOW, HIGH, LOW, HIGH);
    move(velocity);
}

void MotorsDriver::stop() const
{
    analogWrite(_pins.enableA, 0);
}

void MotorsDriver::setDirection(uint8_t const in1, uint8_t const in2, uint8_t const in3, uint8_t const in4) const
{
    digitalWrite(_pins.in1, in1);
    digitalWrite(_pins.in2, in2);
    digitalWrite(_pins.in3, in3);
    digitalWrite(_pins.in4, in4);
}

void MotorsDriver::move(int const velocity) const
{
    int absoluteValue = abs(velocity);
    absoluteValue += _velocityOffset;
    absoluteValue = constrain(absoluteValue, 0, 255);

    analogWrite(_pins.enableA, absoluteValue);
}
