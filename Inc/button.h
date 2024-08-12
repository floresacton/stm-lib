#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "stdint.h"
#include "main.h"
#include "gpio.h"

struct Button_Handle {
    TIM_HandleTypeDef* htim; // 50Hz typ

    Gpio_Handle* buttonPins;
    uint8_t buttonCount;
};

void Button_Init(Button_Handle* button);

uint8_t Button_Pressed(Button_Handle* button, uint8_t button);

void Button_TimHandler(Button_Handle* button);
uint8_t Button_TimFlag(Button_Handle* button, TIM_HandleTypeDef *htim);


#endif
