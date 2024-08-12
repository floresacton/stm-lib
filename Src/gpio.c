#include "gpio.h"
#include "main.h"

void Gpio_Write(struct Gpio_Handle* handle, uint8_t state) {
	HAL_GPIO_WritePin(handle->port, handle->pin, state);
}

uint8_t Gpio_Read(struct Gpio_Handle* handle) {
	return HAL_GPIO_ReadPin(handle->port, handle->pin);
}
