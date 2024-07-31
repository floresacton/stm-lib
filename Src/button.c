#include <button.h>
#include "main.h"

extern TIM_HandleTypeDef BUTTON_HANDLE;

static GPIO_TypeDef *ports[BUTTON_COUNT] = { BTN1_GPIO_Port, BTN2_GPIO_Port,
		BTN3_GPIO_Port, BTN4_GPIO_Port };
static uint16_t pins[BUTTON_COUNT] = { BTN1_Pin, BTN2_Pin, BTN3_Pin, BTN4_Pin };

static uint8_t lastState[BUTTON_COUNT];
static uint8_t pressed[BUTTON_COUNT];

void Button_Init(void) {
	HAL_TIM_Base_Start_IT(&BUTTON_HANDLE);
}

uint8_t Button_Pressed(enum ButtonId button) {
	const uint8_t val = pressed[button];
	pressed[button] = 0;
	return val;
}

void Button_TimHandler(void) {
	for (uint8_t i = 0; i < BUTTON_COUNT; i++) {
		uint8_t state = !HAL_GPIO_ReadPin(ports[i], pins[i]);
		if (state && !lastState[i]) {
			pressed[i] = 1;
		}
		lastState[i] = state;
	}
}

uint8_t Button_TimFlag(TIM_HandleTypeDef *htim) {
	return htim == &BUTTON_HANDLE;
}
