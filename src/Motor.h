
#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <cstdint>
#include <esp_attr.h>


class Motor
{
public:
    enum class Direction {Front , Back};
    struct MotorPins { int in1; int in2; int enable; int encoderA; int encoderB; };

    Motor (MotorPins const& pins);

    void setUp();

    void setDirection(Direction direction) const;
    void move(int velocity) const;
    void stop() const;

    static void IRAM_ATTR encoderFeedbackIsr(void* motor);
    void handleEncoder();

private:
    MotorPins _pins;

    volatile int32_t _pulseCount = 0;
    int const _velocityOffset = 100;
};



#endif
