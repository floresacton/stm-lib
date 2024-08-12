#ifndef INC_TACH_H_
#define INC_TACH_H_

#include "stdint.h"
#include "main.h"

struct Tach_Handle {
    TIM_HandleTypeDef* htimCount; // 50kHz typ
    TIM_HandleTypeDef* htimCalc; // 50Hz typ
};

void Tach_Init(Tach_Handle* tach);

uint8_t Tach_TimFlagCalc(Tach_Handle* tach, TIM_HandleTypeDef* htim);
void Tach_TimHandlerCalc(Tach_Handle* tach);

uint8_t Tach_TimFlagRef(Tach_Handle* tach, TIM_HandleTypeDef* htim);
void Tach_TimHandlerRef(Tach_Handle* tach);

void Tach_Trigger(Tach_Handle* tach);

uint16_t Tach_Rpm(Tach_Handle* tach);

#endif
