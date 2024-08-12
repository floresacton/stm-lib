#ifndef INC_GPS_H_
#define INC_GPS_H_

#include "stdint.h"
#include "main.h"
#include "gpio.h"

// #define GPS_HANDLE huart3
// #define GPS_DMA_HANDLE hdma_usart3_rx
// #define GPS_INT_PIN PPS_Pin

// #define GPS_RX_BUF_SIZE 1000
// #define GPS_TX_BUF_SIZE 1000

struct Gps_Handle {
    UART_HandleTypeDef* huart;
    DMA_HandleTypeDef* hdma;
    
    Gpio_Handle* intPin;

    uint16_t rxBufSize;
    uint16_t txBufSize;

    uint8_t usb_transmit;
    uint8_t usb_receive;
};

void Gps_Init(Gps_Handle* gps);

uint8_t Gps_UartFlag(Gps_Handle* gps, UART_HandleTypeDef* huart);
void Gps_UartHandler(Gps_Handle* gps, uint16_t size);

void Gps_UsbHandler(Gps_Handle* gps, uint8_t* data, uint32_t len);

uint8_t Gps_ExtFlag(Gps_Handle* gps, uint16_t pin);
void Gps_ExtHandler(Gps_Handle* gps, void);

void Gps_SetUsbTransmit(Gps_Handle* gps, uint8_t mode);
void Gps_SetUsbReceive(Gps_Handle* gps, uint8_t mode);

#endif
