#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#include "stdint.h"

#define EEPROM_HANDLE hi2c1 //1Mhz max
#define EEPROM_ADDRESS 0xA0

#define EEPROM_PAGE_SIZE  64
#define EEPROM_PAGE_COUNT 512

//wrap page
void Eeprom_Write(uint16_t address, uint8_t *buf, uint16_t len);

//wrap memory
void Eeprom_ReadNext(uint8_t *buf, uint8_t len);

void Eeprom_Read(uint16_t address, uint8_t *buf, uint16_t len);

#endif
