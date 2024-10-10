#include "button.h"

void Button_Init(struct Button_Handle* handle) {
	handle->pressed = 0;
	handle->lastState = 0;
}

void Button_Update(struct Button_Handle* handle) {
	const uint8_t state = !HAL_GPIO_ReadPin(handle->port, handle->pin);
	if (state && !handle->lastState) {
		handle->pressed = 1;
	}
	handle->lastState = state;
}
