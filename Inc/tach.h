#ifndef INC_TACH_H_
#define INC_TACH_H_

#include "stdint.h"
#include "main.h"

struct Tach_Handle {
	// configuration
    TIM_HandleTypeDef* htimCount; // 50kHz typical
    TIM_HandleTypeDef* htimCalc; // 50Hz typical

    uint32_t freqRef; // 50000 typical

    uint8_t* spokes;
    uint16_t* maxRpm;
    uint8_t channelCount;

    // internal
    uint16_t* rpm;

    uint32_t* count;
    uint32_t* countAccum;
    uint32_t* passes;

    uint32_t* checkpointAccum;
    uint32_t* checkpointPasses;
};

void Tach_Init(struct Tach_Handle* handle);

uint8_t Tach_TimFlagCalc(struct Tach_Handle* handle, TIM_HandleTypeDef* htim);
void Tach_TimHandlerCalc(struct Tach_Handle* handle);

uint8_t Tach_TimFlagRef(struct Tach_Handle* handle, TIM_HandleTypeDef* htim);
void Tach_TimHandlerRef(struct Tach_Handle* handle);

void Tach_Trigger(struct Tach_Handle* handle, uint8_t chan);

uint16_t Tach_Rpm(struct Tach_Handle* handle, uint8_t chan);

#endif
