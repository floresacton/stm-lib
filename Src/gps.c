#include "gps.h"
#include "memory.h"
#include "stdio.h"
#include "string.h"
#include "main.h"
#include "display.h"
#include "usbd_cdc_if.h"

extern UART_HandleTypeDef GPS_HANDLE;
extern DMA_HandleTypeDef GPS_DMA_HANDLE;

static uint8_t gps_rx_buf[GPS_RX_BUF_SIZE] = {0};
static uint8_t gps_tx_buf[GPS_TX_BUF_SIZE] = {0};

static uint8_t gps_read_buf[GPS_RX_BUF_SIZE] = {0};
static volatile uint8_t gps_flag = 0;

static uint8_t gps_fix = 0;
static float gps_speed = 0;//kph
static uint16_t gps_rpm = 0;

static uint8_t last_fix = 0;

void Gps_Init(void) {
	HAL_UARTEx_ReceiveToIdle_DMA(&GPS_HANDLE, gps_rx_buf, GPS_RX_BUF_SIZE);
	__HAL_DMA_DISABLE_IT(&GPS_DMA_HANDLE, DMA_IT_HT);
}

void gps_read_data(void) {
	return;
	char* ptr = (char*)gps_read_buf;
	uint8_t cnt = 0;
	while (cnt < 2) {
		if (*ptr == '$') {
			cnt++;
		}
		ptr++;
	}
	if (*(ptr+2) != 'V') {
		return;
	}
	cnt = 0;
	while (cnt < 7) {
		if (*ptr == ',') {
			cnt++;
		}
		ptr++;
	}
	if (*(ptr+1) == ',') {
		gps_fix = 0;
		return;
	}
	char* ptr_end = ptr;
	while (*ptr_end != ',') {
		ptr_end++;
	}
	*ptr_end = '\0';
	sscanf(ptr, "%f", &gps_speed);
	float speed_temp = gps_speed;
	//convert kph to mph
	gps_speed*=0.621371;
	//convert mph to kph
	//convert from inches to mm too
	gps_rpm = (uint16_t)((float)(1e6/60.0)*speed_temp*0.0393701/(float)Memory_ReadFloat(MemGpsTire));
	gps_fix = 1;
}

void Gps_Update(void) {
	if (gps_flag) {
		gps_flag = 0;
		gps_read_data();
		if (gps_fix != last_fix) {
			last_fix = gps_fix;
			Display_UpdateGPS(gps_fix);
		}
	}
}

uint8_t Gps_UartFlag(UART_HandleTypeDef* huart) {
	return huart == &GPS_HANDLE;
}

void Gps_UartHandler(uint16_t size) {
	gps_flag = 1;
	memcpy(gps_read_buf, gps_rx_buf, GPS_RX_BUF_SIZE);
	CDC_Transmit_FS(gps_read_buf, size);
	HAL_UARTEx_ReceiveToIdle_DMA(&GPS_HANDLE, gps_rx_buf, GPS_RX_BUF_SIZE);
	__HAL_DMA_DISABLE_IT(&GPS_DMA_HANDLE, DMA_IT_HT);
}

void Gps_UsbHandler(uint8_t* data, uint32_t len) {
	memcpy(gps_tx_buf, data, len);
	HAL_UART_Transmit_DMA(&GPS_HANDLE, gps_tx_buf, len);
}

uint8_t Gps_ExtFlag(uint16_t pin) {
	return pin == GPS_INT_PIN;
}

void Gps_ExtHandler(void) {

}

float Gps_Speed(void) {
	return gps_speed;
}

uint8_t Gps_Fix(void) {
	return gps_fix;
}
