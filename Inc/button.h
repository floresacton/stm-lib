#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "button_conf.h"

#include "stdint.h"
#include "main.h"

void Button_Init(void);

uint8_t Button_Pressed(enum ButtonId button);

void Button_TimHandler(void);
uint8_t Button_TimFlag(TIM_HandleTypeDef *htim);


#endif
