#include "memory.h"
#include "stm32g4xx_hal.h"
#include "eeprom.h"
#include "stdlib.h"

static uint8_t mem_buf[MEMORY_SIZE];

void Memory_Init(void) {
	Eeprom_Read(0, mem_buf, MEMORY_SIZE);
	if (Memory_ReadByte(MemHash) != MEMORY_HASH) {
		Memory_WriteByte(MemHash, MEMORY_HASH);
		Memory_Reset();
	}
}

void Memory_Reset(void) {
	//Bytes
	Memory_WriteByte(MemTach1Spokes, 10);
	Memory_WriteByte(MemTach2Spokes, 10);
	Memory_WriteByte(MemTach3Spokes, 10);
	//Shorts
	Memory_WriteShort(MemMinRpm, 20);

	Memory_WriteShort(MemTach1Max, 10000);
	Memory_WriteShort(MemTach2Max, 10000);
	Memory_WriteShort(MemTach3Max, 10000);

	Memory_WriteShort(MemTach1Thresh, 2048);
	Memory_WriteShort(MemTach2Thresh, 2048);
	Memory_WriteShort(MemTach3Thresh, 2048);

	Memory_WriteShort(MemAuxThresh, 1000); //rpm
	//Floats
	Memory_WriteFloat(MemGpsTire, 53.4); //53.4 inches

	Memory_WriteFloat(MemSlipThresh, 10.0); //10.0%
}

uint8_t Memory_ReadByte(uint8_t loc) {
	return mem_buf[loc];
}
uint16_t Memory_ReadShort(uint8_t loc) {
	const uint16_t pos = MEMORY_BYTES + 2 * loc;
	return *((uint16_t*) (mem_buf + pos));
}
float Memory_ReadFloat(uint8_t loc) {
	const uint16_t pos = MEMORY_BYTES + 2 * MEMORY_SHORTS + 4 * loc;
	return *((float*) (mem_buf + pos));
}

void Memory_WriteByte(uint8_t loc, uint8_t val) {
	mem_buf[loc] = val;
	Eeprom_Write(loc, &val, 1);
}
void Memory_WriteShort(uint8_t loc, uint16_t val) {
	const uint16_t pos = MEMORY_BYTES + 2 * loc;
	uint16_t *ptr = (uint16_t*) (mem_buf + pos);
	ptr[0] = val;
	Eeprom_Write(pos, (uint8_t*) &val, 2);
}
void Memory_WriteFloat(uint8_t loc, float val) {
	const uint16_t pos = MEMORY_BYTES + 2 * MEMORY_SHORTS + 4 * loc;
	float *ptr = (float*) (mem_buf + pos);
	ptr[0] = val;
	Eeprom_Write(pos, (uint8_t*) &val, 4);
}
