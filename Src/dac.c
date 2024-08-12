#include "dac.h"
#include "main.h"

void Dac_Set(struct Dac_Handle* handle, uint16_t value) {
	HAL_DAC_SetValue(handle->hdac, handle->channel, DAC_ALIGN_12B_R, value);
}
