#ifndef INC_TACH_H_
#define INC_TACH_H_

#include "tach_conf.h"

#include "stdint.h"
#include "main.h"

void Tach_Init(void);

uint8_t Tach_TimFlagCalc(TIM_HandleTypeDef* htim);
void Tach_TimHandlerCalc(void);

uint8_t Tach_TimFlagRef(TIM_HandleTypeDef* htim);
void Tach_TimHandlerRef(void);

void Tach_Trigger(enum TachId tach);

uint16_t Tach_Rpm(enum TachId chan);

#endif
