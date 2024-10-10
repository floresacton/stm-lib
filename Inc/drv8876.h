#ifndef INC_DRV8876_H_
#define INC_DRV8876_H_

#include "main.h"

struct Drv8876_Handle {
    // configuration
    TIM_HandleTypeDef* aTim;
    uint32_t aChan;

    TIM_HandleTypeDef* bTim;
    uint32_t bChan;

    TIM_HandleTypeDef* cTim;
    uint32_t cChan;

    uint8_t max;
};

void Drv8876_Init(struct Drv8876_Handle* handle);

void Drv8876_SetCurrent(struct Drv8876_Handle* handle, uint8_t current);
void Drv8876_SetVoltage(struct Drv8876_Handle* handle, float voltage);

#endif