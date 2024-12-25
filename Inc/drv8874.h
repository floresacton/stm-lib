#ifndef INC_DRV8874_H_
#define INC_DRV8874_H_

#include "main.h"

struct Drv8874_Handle {
    // configuration
    TIM_HandleTypeDef* aTim;
    uint32_t aChan;

    TIM_HandleTypeDef* bTim;
    uint32_t bChan;

    TIM_HandleTypeDef* cTim;
    uint32_t cChan;

    uint8_t dir;
    uint8_t max;
};

void Drv8874_Init(struct Drv8874_Handle* handle);

void Drv8874_SetCurrent(struct Drv8874_Handle* handle, uint8_t current);
void Drv8874_SetVoltage(struct Drv8874_Handle* handle, float voltage);

#endif
