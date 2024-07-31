#ifndef INC_DAC_H_
#define INC_DAC_H_

#include "stdint.h"
#include "main.h"

#define DAC_COUNT 3

struct Dac {
	DAC_HandleTypeDef *hdac;
	uint32_t chan;
};

enum DacId {
	Dac1,
	Dac2,
	Dac3,
};

void Dac_Set(enum DacId dac, uint16_t value);

#endif
