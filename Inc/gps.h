#ifndef INC_GPS_H_
#define INC_GPS_H_

#include "gps_conf.h"

#include "stdint.h"
#include "main.h"

void Gps_Init(void);
void Gps_Update(void);

uint8_t Gps_UartFlag(UART_HandleTypeDef* huart);
void Gps_UartHandler(uint16_t size);

void Gps_UsbHandler(uint8_t* data, uint32_t len);

uint8_t Gps_ExtFlag(uint16_t pin);
void Gps_ExtHandler(void);

float Gps_Speed(void);
uint8_t Gps_Fix(void);

#endif
