#include "dac.h"
#include "main.h"
#include "memory.h"

extern DAC_HandleTypeDef hdac1;
extern DAC_HandleTypeDef hdac3;

struct Dac dacs[DAC_COUNT] = {{.hdac = &hdac1, .chan = DAC_CHANNEL_2},
		{.hdac = &hdac1, .chan = DAC_CHANNEL_1},
		{.hdac = &hdac3, .chan = DAC_CHANNEL_1}};

void Dac_Set(enum DacId dac, uint16_t value) {
	HAL_DAC_SetValue(dacs[dac].hdac, dacs[dac].chan, DAC_ALIGN_12B_R, value);
}
