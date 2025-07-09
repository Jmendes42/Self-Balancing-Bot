
#ifndef __ENCODER_FEEDBACK_H__
#define __ENCODER_FEEDBACK_H__

#include <esp_attr.h>
#include <cstdint>


class EncoderFeedback
{
public:
    EncoderFeedback(int encoderA, int encoderB);

    void setup();

    static void IRAM_ATTR encoderFeedbackIsr(void* motor);
    void handleEncoder();

private:
    volatile int32_t _pulseCount = 0;

    int _encoderA;
    int _encoderB;
};


#endif
