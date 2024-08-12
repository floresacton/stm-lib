#ifndef INC_GPS_H_
#define INC_GPS_H_

#include "stdint.h"
#include "main.h"
#include "nmea.h"

struct Gps_Handle {
	// configuration
    UART_HandleTypeDef* huart;
    DMA_HandleTypeDef* hdma;
    
    uint16_t intPin;

    uint16_t rxBufSize; // 1000 typical
    uint16_t txBufSize; // 1000 typical

    uint8_t usbTransmit;
    uint8_t usbReceive;

    // internal
    uint8_t* rxBuf;
    uint8_t* txBuf;

    uint8_t* readBuf;
    uint8_t* usbBuf;

    struct Nmea_Handle* nmea;
};

void Gps_Init(struct Gps_Handle* handle);

uint8_t Gps_UartFlag(struct Gps_Handle* handle, UART_HandleTypeDef* huart);
void Gps_UartHandler(struct Gps_Handle* handle, uint16_t size);

void Gps_UsbHandler(struct Gps_Handle* handle, uint8_t* data, uint16_t len);

uint8_t Gps_ExtFlag(struct Gps_Handle* handle, uint16_t pin);
void Gps_ExtHandler(struct Gps_Handle* handle);

#endif
