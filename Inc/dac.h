#ifndef INC_DAC_H_
#define INC_DAC_H_

#include "dac_conf.h"

#include "stdint.h"

void Dac_Set(enum DacId dac, uint16_t value);

#endif
