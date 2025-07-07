
#include "Motor.h"

#include <Arduino.h>
#include <esp32-hal-gpio.h>



Motor::Motor(MotorPins const& pins)
    : _pins(pins)
{
}

void Motor::setUp()
{
    pinMode(_pins.encoderA, INPUT);
    pinMode(_pins.encoderB, INPUT);
    attachInterruptArg(digitalPinToInterrupt(_pins.encoderA), encoderFeedbackIsr, this, RISING);

    pinMode(_pins.in1, OUTPUT);
    pinMode(_pins.in2, OUTPUT);
    pinMode(_pins.enable, OUTPUT);
}

void Motor::setDirection(Direction const direction) const
{
    if (direction == Direction::Front)
    {
        digitalWrite(_pins.in1, HIGH);
        digitalWrite(_pins.in2, LOW);
    }
    else
    {
        digitalWrite(_pins.in1, LOW);
        digitalWrite(_pins.in2, HIGH);
    }
}

void Motor::move(int const velocity) const
{
    int absoluteValue = abs(velocity);
    absoluteValue += _velocityOffset;
    absoluteValue = constrain(absoluteValue, 0, 255);

    Serial.print("Absolute value: ");
    Serial.println(absoluteValue);

    analogWrite(_pins.enable, absoluteValue);
}

void Motor::stop() const
{
    analogWrite(_pins.enable, 0);
}

void IRAM_ATTR Motor::encoderFeedbackIsr(void* motor)
{
    auto* instance = static_cast<Motor*>(motor);
    instance->handleEncoder();
}

void Motor::handleEncoder()
{
    bool const readA = digitalRead(_pins.encoderA);
    bool const readB = digitalRead(_pins.encoderB);

    _pulseCount += readA == readB ? 1 : -1;
}
