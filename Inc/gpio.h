#ifndef INC_LPS22HH_H_
#define INC_LPS22HH_H_

#include "main.h"

struct Gpio_Handle {
	// configuration
    GPIO_TypeDef* port;
    uint16_t pin;
};

void Gpio_Write(struct Gpio_Handle* handle, uint8_t state);
uint8_t Gpio_Read(struct Gpio_Handle* handle);

#endif
