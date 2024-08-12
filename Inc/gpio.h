#ifndef INC_LPS22HH_H_
#define INC_LPS22HH_H_

#include "main.h"

struct Gpio_Handle {
    GPIO_TypeDef* port;
    uint16_t pin;
};

void Gpio_Write(Gpio_Handle* gpio, uint8_t state);
uint8_t Gpio_Read(Gpio_Handle* gpio);

#endif