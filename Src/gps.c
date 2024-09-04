#include "gps.h"
#include "stdlib.h"
#include "string.h"
#include "main.h"
#include "nmea.h"
#include "usbd_cdc_if.h"

static void gps_start_dma(struct Gps_Handle* handle) {
	HAL_UARTEx_ReceiveToIdle_DMA(handle->huart, handle->rxBuf, handle->rxBufSize);
	__HAL_DMA_DISABLE_IT(handle->hdma, DMA_IT_HT);
}

void Gps_Init(struct Gps_Handle* handle) {
	handle->rxBuf = malloc(handle->rxBufSize);
	handle->readBuf = malloc(handle->rxBufSize);

	handle->txBuf = malloc(handle->txBufSize);

	gps_start_dma(handle);
}

uint8_t Gps_UartFlag(struct Gps_Handle* handle, UART_HandleTypeDef* huart) {
	return handle->huart == huart;
}

void Gps_UartHandler(struct Gps_Handle* handle, uint16_t len) {
	memcpy(handle->readBuf, handle->rxBuf, len);
	gps_start_dma(handle);
}

void Gps_Transmit(struct Gps_Handle* handle, uint8_t* data, uint16_t len) {
	memcpy(handle->txBuf, data, len);
	HAL_UART_Transmit_DMA(handle->huart, handle->txBuf, len);
}
