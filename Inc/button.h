#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "stdint.h"
#include "main.h"
#include "gpio.h"

struct Button_Handle {
	// configuration
    TIM_HandleTypeDef* htim; // 50Hz typical

    struct Gpio_Handle* buttonPins;
    uint8_t buttonCount;

    // internal
    uint8_t* lastState;
    uint8_t* pressed;
};

void Button_Init(struct Button_Handle* handle);

uint8_t Button_GetPressed(struct Button_Handle* handle, uint8_t button);

void Button_TimHandler(struct Button_Handle* handle);
uint8_t Button_TimFlag(struct Button_Handle* handle, TIM_HandleTypeDef *htim);

#endif
