#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "stdint.h"
#include "platform.h"

struct Button_Handle {
	// configuration
    TIM_HandleTypeDef* htim; // 50Hz typical

    GPIO_TypeDef** ports;
    uint16_t* pins;

    uint8_t count;

    // internal
    uint8_t* lastState;
    uint8_t* pressed;
};

void Button_Init(struct Button_Handle* handle);

void Button_TimHandler(struct Button_Handle* handle);
uint8_t Button_TimFlag(struct Button_Handle* handle, TIM_HandleTypeDef *htim);

#endif
