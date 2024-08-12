#include "memory.h"
#include "eeprom.h"
#include "stm32g4xx_hal.h"
#include "stdlib.h"

void Memory_Init(struct Memory_Handle* handle) {
	handle->bufSize = 1 + handle->byteCount + 2 * handle->shortCount + 4 * (handle->intCount + handle->floatCount);
	handle->buf = malloc(handle->bufSize);

	handle->byteStart = handle->buf + 1;
	handle->shortStart = handle->byteStart + handle->byteCount;
	handle->intStart = handle->shortStart + 2 * handle->shortCount;
	handle->floatStart = handle->intStart + 4 * handle->intCount;

	Eeprom_Read(handle->eeprom, 0, handle->buf, handle->bufSize);
	if (Eeprom_ReadByte(handle->eeprom, 0) != handle->hash) {
		Eeprom_WriteByte(handle->eeprom, 0, handle->hash);
		Memory_Reset(handle);
	}
}

__weak void Memory_Reset(struct Memory_Handle* handle) {
}

uint8_t Memory_ReadByte(struct Memory_Handle* handle, uint8_t loc) {
	return handle->byteStart[loc];
}
uint16_t Memory_ReadShort(struct Memory_Handle* handle, uint8_t loc) {
	return ((uint16_t*)handle->shortStart)[loc];
}
uint32_t Memory_ReadInt(struct Memory_Handle* handle, uint8_t loc) {
	return ((uint32_t*)handle->intStart)[loc];
}
float Memory_ReadFloat(struct Memory_Handle* handle, uint8_t loc) {
	return ((float*)handle->floatStart)[loc];
}

void Memory_WriteByte(struct Memory_Handle* handle, uint8_t loc, uint8_t val) {
	uint8_t* pos = handle->byteStart + loc;
	*pos = val;
	Eeprom_Write(handle->eeprom, pos-handle->buf, &val, 1);
}
void Memory_WriteShort(struct Memory_Handle* handle, uint8_t loc, uint16_t val) {
	uint16_t* pos = (uint16_t*)handle->shortStart + loc;
	*pos = val;
	Eeprom_Write(handle->eeprom, (uint8_t*)pos-handle->buf, (uint8_t*)&val, 2);
}
void Memory_WriteInt(struct Memory_Handle* handle, uint8_t loc, uint32_t val) {
	uint32_t* pos = (uint32_t*)handle->intStart + loc;
	*pos = val;
	Eeprom_Write(handle->eeprom, (uint8_t*)pos-handle->buf, (uint8_t*)&val, 2);
}
void Memory_WriteFloat(struct Memory_Handle* handle, uint8_t loc, float val) {
	float* pos = (float*)handle->floatStart + loc;
	*pos = val;
	Eeprom_Write(handle->eeprom, (uint8_t*)pos-handle->buf, (uint8_t*)&val, 2);
}
