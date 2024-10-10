#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "stdint.h"
#include "main.h"

struct Button_Handle {
	// configuration
    GPIO_TypeDef* port;
    uint16_t pin;

    // internal
    uint8_t lastState;
    uint8_t pressed;
};

void Button_Init(struct Button_Handle* handle);

// 50Hz typical
void Button_Update(struct Button_Handle* handle);

#endif
