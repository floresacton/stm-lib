#include "drv8876.h"

static int8_t motor_clamp(float val, uint8_t max) {
	if (val < 0) {
		return 0;
	}
	if (val > max) {
		return max;
	}
	return val;
}

void Drv8876_Init(struct Drv8876_Handle* handle) {
    HAL_TIM_PWM_Start(handle->aTim, handle->aChan);
    HAL_TIM_PWM_Start(handle->bTim, handle->bChan);
    HAL_TIM_PWM_Start(handle->cTim, handle->cChan);

    __HAL_TIM_SET_COMPARE(handle->aTim, handle->aChan, 0);
    __HAL_TIM_SET_COMPARE(handle->bTim, handle->bChan, 0);
    __HAL_TIM_SET_COMPARE(handle->cTim, handle->cChan, 0);
}

void Drv8876_SetCurrent(struct Drv8876_Handle* handle, uint8_t current) {
	__HAL_TIM_SET_COMPARE(handle->cTim, handle->cChan, current);
}

void Drv8876_SetVoltage(struct Drv8876_Handle* handle, float voltage) {
    const uint8_t max = handle->max;
	if (handle->dir) {
		voltage = -voltage;
	}
	__HAL_TIM_SET_COMPARE(handle->aTim, handle->aChan, motor_clamp(voltage, max));
	__HAL_TIM_SET_COMPARE(handle->bTim, handle->bChan, motor_clamp(-voltage, max));
}