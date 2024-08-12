#ifndef INC_AT24C_H_
#define INC_AT24C_H_

// #define AT24C_HANDLE hi2c1
// #define AT24C_ADDRESS 0xA0

// #define AT24C_PAGE_SIZE  64
// #define AT24C_PAGE_COUNT 512

#include "stdint.h"
#include "main.h"

struct Eeprom_Handle {
    I2C_HandleTypeDef hi2c;
    uint8_t address;

    uint8_t pageSize;
    uint16_t pageCount;
};

//wrap page
void Eeprom_Write(Eeprom_Handle* eeprom, uint16_t address, uint8_t *buf, uint16_t len);

//wrap memory
void Eeprom_ReadNext(Eeprom_Handle* eeprom, uint8_t *buf, uint8_t len);

void Eeprom_Read(Eeprom_Handle* eeprom, uint16_t address, uint8_t *buf, uint16_t len);

#endif
