#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "stdint.h"
#include "main.h"

#define BUTTON_COUNT 4

#define BUTTON_HANDLE htim3 //50hz

#include "inttypes.h"

enum ButtonId {
	ButtonUp,
	ButtonDown,
	ButtonEnter,
	ButtonBack,
};

void Button_Init(void);

uint8_t Button_Pressed(enum ButtonId button);

void Button_TimHandler(void);
uint8_t Button_TimFlag(TIM_HandleTypeDef *htim);


#endif
