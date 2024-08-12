#include "tach.h"
#include "stdlib.h"
#include "main.h"

void Tach_Init(struct Tach_Handle* handle) {
	handle->rpm = malloc(handle->channelCount * 2);

	handle->count = malloc(handle->channelCount * 4);
	handle->countAccum = malloc(handle->channelCount * 4);
	handle->passes = malloc(handle->channelCount * 4);

	handle->checkpointAccum = malloc(handle->channelCount * 4);
	handle->checkpointPasses = malloc(handle->channelCount * 4);
}

uint8_t Tach_TimFlagCalc(struct Tach_Handle* handle, TIM_HandleTypeDef* htim) {
	return handle->htimCalc == htim;
}
void Tach_TimHandlerCalc(struct Tach_Handle* handle) {
	for (uint8_t i = 0; i < handle->channelCount; i++) {
		if (handle->checkpointPasses[i]) {
			handle->rpm[i] = (float)handle->freqRef*60.0*(float)handle->checkpointPasses[i]/((float)handle->checkpointAccum[i]*(float)handle->spokes[i]);
			handle->countAccum[i] = 0;
			handle->checkpointAccum[i] = 0;
		}else if(handle->passes[i]){
			handle->rpm[i] = (float)handle->freqRef*60.0*(float)handle->passes[i]/((float)handle->countAccum[i]*(float)handle->spokes[i]);
			handle->countAccum[i] = 0;
			handle->checkpointAccum[i] = 0;
		}else {
			const uint16_t new_rpm = (float)handle->freqRef*60.0/((float)handle->spokes[i]*(float)handle->count[i]);
			if (new_rpm < handle->rpm[i]) {
				handle->rpm[i] = new_rpm;
			}
		}

		handle->passes[i] = 0;
		handle->checkpointPasses[i] = 0;
	}
}

uint8_t Tach_TimFlagCount(struct Tach_Handle* handle, TIM_HandleTypeDef* htim) {
	return handle->htimCount == htim;
}
void Tach_TimHandlerCount(struct Tach_Handle* handle) {
	for (uint8_t i = 0; i < handle->channelCount; i++) {
		handle->count[i]++;
	}
}

void Tach_Trigger(struct Tach_Handle* handle, uint8_t chan) {
	if (handle->count[chan] >= 60.0*(float)handle->freqRef/(handle->spokes[chan]*handle->maxRpm[chan])) {
		handle->passes[chan]++;
		handle->countAccum[chan] += handle->count[chan];
		if (handle->passes[chan] % handle->spokes[chan] == 0) {
			handle->checkpointPasses[chan] = handle->passes[chan];
			handle->checkpointAccum[chan] = handle->countAccum[chan];
		}
		handle->count[chan] = 0;
	}
}

uint16_t Tach_Rpm(struct Tach_Handle* handle, uint8_t chan) {
	return handle->rpm[chan];
}
