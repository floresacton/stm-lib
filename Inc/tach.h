#ifndef INC_TACH_H_
#define INC_TACH_H_

#include "stdint.h"
#include "main.h"

struct Tach_Handle {
    // configuration
    uint32_t countFreq; // freq of Tach_Count

    uint8_t spokes;
    uint16_t maxRpm;

    // internal
    uint16_t rpm;

    uint32_t count;
    uint32_t countAccum;
    uint32_t passes;

    uint32_t checkpointAccum;
    uint32_t checkpointPasses;
};

void Tach_Init(struct Tach_Handle* handle);

// 50Hz typical
void Tach_Update(struct Tach_Handle* handle);

// 50kHz typical
void Tach_Count(struct Tach_Handle* handle);

void Tach_Trigger(struct Tach_Handle* handle);

#endif
