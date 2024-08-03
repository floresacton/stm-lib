#ifndef INC_AT24C_H_
#define INC_AT24C_H_

#include "at24c_conf.h"

#include "stdint.h"

//wrap page
void At24c_Write(uint16_t address, uint8_t *buf, uint16_t len);

//wrap memory
void At24c_ReadNext(uint8_t *buf, uint8_t len);

void At24c_Read(uint16_t address, uint8_t *buf, uint16_t len);

#endif
