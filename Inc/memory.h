#ifndef INC_MEMORY_H_
#define INC_MEMORY_H_

#include "stdint.h"
#include "eeprom.h"

struct Memory_Handle {
	// configuration
	struct Eeprom_Handle* eeprom;

	uint8_t byteCount;
	uint8_t shortCount;
	uint8_t intCount;
	uint8_t floatCount;

	uint8_t hash;

	// internal
	uint8_t* buf;
	uint8_t bufSize;

	uint8_t* byteStart;
	uint8_t* shortStart;
	uint8_t* intStart;
	uint8_t* floatStart;
};

void Memory_Init(struct Memory_Handle* handle);
__weak void Memory_Reset(struct Memory_Handle* handle);

uint8_t Memory_ReadByte(struct Memory_Handle* handle ,uint8_t loc);
uint16_t Memory_ReadShort(struct Memory_Handle* handle, uint8_t loc);
uint32_t Memory_ReadInt(struct Memory_Handle* handle, uint8_t loc);
float Memory_ReadFloat(struct Memory_Handle* handle, uint8_t loc);

void Memory_WriteByte(struct Memory_Handle* handle, uint8_t loc, uint8_t val);
void Memory_WriteShort(struct Memory_Handle* handle, uint8_t loc, uint16_t val);
void Memory_WriteInt(struct Memory_Handle* handle, uint8_t loc, uint32_t val);
void Memory_WriteFloat(struct Memory_Handle* handle, uint8_t loc, float val);

#endif
