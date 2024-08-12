#ifndef INC_DAC_H_
#define INC_DAC_H_

#include "stdint.h"
#include "main.h"

struct Dac_Handle {
	// configuration
    DAC_HandleTypeDef* hdac;
    uint8_t channel;
};

void Dac_Set(struct Dac_Handle* handle, uint16_t value);

#endif
