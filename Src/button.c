#include "button.h"
#include "stdlib.h"
#include "string.h"
#include "main.h"

void Button_Init(struct Button_Handle* handle) {
	handle->pressed = malloc(handle->count);
	handle->lastState = malloc(handle->count);

	memset(handle->pressed, 0, handle->count);
	memset(handle->lastState, 0, handle->count);

	HAL_TIM_Base_Start_IT(handle->htim);
}

void Button_TimHandler(struct Button_Handle* handle) {
	for (uint8_t i = 0; i < handle->count; i++) {
		const uint8_t state = !HAL_GPIO_ReadPin(handle->ports[i], handle->pins[i]);
		if (state && !handle->lastState[i]) {
			handle->pressed[i] = 1;
		}
		handle->lastState[i] = state;
	}
}

uint8_t Button_TimFlag(struct Button_Handle* handle, TIM_HandleTypeDef *htim) {
	return handle->htim == htim;
}
