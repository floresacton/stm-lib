#include "gps.h"
#include "string.h"
#include "main.h"
#include "nmea.h"
#include "usbd_cdc_if.h"

inline void gps_start_dma(struct Gps_Handle* handle) {
	HAL_UARTEx_ReceiveToIdle_DMA(handle->huart, handle->rxBuf, handle->rxBufSize);
	__HAL_DMA_DISABLE_IT(handle->hdma, DMA_IT_HT);
}

void Gps_Init(struct Gps_Handle* handle) {
	handle->rxBuf = malloc(handle->rxBufSize);
	handle->readBuf = malloc(handle->rxBufSize);
	handle->usbBuf = malloc(handle->rxBufSize);

	handle->txBuf = malloc(handle->txBufSize);

	handle->nmea = malloc(sizeof (struct Nmea_Handle));

	Nmea_Init(handle->nmea);

	gps_start_dma(handle);
}

uint8_t Gps_UartFlag(struct Gps_Handle* handle, UART_HandleTypeDef* huart) {
	return handle->huart == huart;
}

void Gps_UartHandler(struct Gps_Handle* handle, uint16_t size) {
	memcpy(handle->readBuf, handle->rxBuf, size);
	Nmea_Parse(handle->nmea, (char*)handle->readBuf);

	if (handle->usbTransmit) {
		memcpy(handle->usbBuf, handle->rxBuf, size);
		CDC_Transmit_FS(handle->usbBuf, size);
	}

	memset(handle->rxBuf, 0, handle->rxBufSize);
	gps_start_dma(handle);
}

void Gps_UsbHandler(struct Gps_Handle* handle, uint8_t* data, uint16_t len) {
	if (handle->usbReceive) {
		memcpy(handle->txBuf, data, len);
		HAL_UART_Transmit_DMA(handle->huart, handle->txBuf, len);
	}
}

uint8_t Gps_ExtFlag(struct Gps_Handle* handle, uint16_t pin) {
	return handle->intPin == pin;
}

void Gps_ExtHandler(struct Gps_Handle* handle) {
	Nmea_Timepulse(handle->nmea);
}
