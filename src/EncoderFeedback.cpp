
#include "EncoderFeedback.h"

#include <Arduino.h>

EncoderFeedback::EncoderFeedback(int const encoderA, int const encoderB)
    : _encoderA(encoderA)
    , _encoderB(encoderB)
{
}

void EncoderFeedback::setup()
{
    attachInterruptArg(digitalPinToInterrupt(_encoderA), encoderFeedbackIsr, this, RISING);
}

int32_t EncoderFeedback::getPulseCount() const
{
    return _pulseCount;
}

void EncoderFeedback::resetPulseCount()
{
    _pulseCount = 0;
}

void IRAM_ATTR EncoderFeedback::encoderFeedbackIsr(void* motor)
{
    auto* instance = static_cast<EncoderFeedback*>(motor);
    instance->handleEncoder();
}

void EncoderFeedback::handleEncoder()
{
    bool const readA = digitalRead(_encoderA);
    bool const readB = digitalRead(_encoderB);

    _pulseCount += readA == readB ? 1 : -1;
}
