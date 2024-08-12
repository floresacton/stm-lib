#ifndef INC_DAC_H_
#define INC_DAC_H_

#include "stdint.h"

struct Dac_Handle {
    DAC_HandleTypeDef* hdac;
    uint8_t channel;
}

void Dac_Set(Dac_Handle* dac, uint16_t value);

#endif
