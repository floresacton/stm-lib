#ifndef INC_AT24C_H_
#define INC_AT24C_H_

#include "stdint.h"
#include "main.h"

struct Eeprom_Handle {
	// configuration
    I2C_HandleTypeDef* hi2c;
    uint8_t address;

    uint8_t pageSize;
    uint16_t pageCount;
};

void Eeprom_Read(struct Eeprom_Handle* handle, uint16_t address, uint8_t *buf, uint16_t len);
uint8_t Eeprom_ReadByte(struct Eeprom_Handle* handle, uint16_t address);

//wrap page
void Eeprom_Write(struct Eeprom_Handle* handle, uint16_t address, uint8_t *buf, uint16_t len);
void Eeprom_WriteByte(struct Eeprom_Handle* handle, uint16_t address, uint8_t val);

//wrap memory
void Eeprom_ReadNext(struct Eeprom_Handle* handle, uint8_t *buf, uint8_t len);


#endif
