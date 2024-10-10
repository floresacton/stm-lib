#include "tach.h"

void Tach_Init(struct Tach_Handle* handle) {
	handle->rpm = 0;

	handle->count = 0;
	handle->countAccum = 0;
	handle->passes = 0;

	handle->checkpointAccum = 0;
	handle->checkpointPasses = 0;
}

void Tach_Update(struct Tach_Handle* handle) {
	if (handle->checkpointPasses) {
		handle->rpm = (float)handle->countFreq*60.0*(float)handle->checkpointPasses/((float)handle->checkpointAccum*(float)handle->spokes);
		handle->countAccum = 0;
		handle->checkpointAccum = 0;
	}else if(handle->passes){
		handle->rpm = (float)handle->countFreq*60.0*(float)handle->passes/((float)handle->countAccum*(float)handle->spokes);
		handle->countAccum = 0;
		handle->checkpointAccum = 0;
	}else {
		const uint16_t new_rpm = (float)handle->countFreq*60.0/((float)handle->spokes*(float)handle->count);
		if (new_rpm < handle->rpm) {
			handle->rpm = new_rpm;
		}
	}

	handle->passes = 0;
	handle->checkpointPasses = 0;
}

void Tach_Count(struct Tach_Handle* handle) {
	handle->count++;
}

void Tach_Trigger(struct Tach_Handle* handle) {
	if (handle->count >= 60.0*(float)handle->countFreq/(handle->spokes*handle->maxRpm)) {
		handle->passes++;
		handle->countAccum += handle->count;
		if (handle->passes % handle->spokes == 0) {
			handle->checkpointPasses = handle->passes;
			handle->checkpointAccum = handle->countAccum;
		}
		handle->count = 0;
	}
}
