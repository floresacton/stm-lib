#ifndef INC_MEMORY_H_
#define INC_MEMORY_H_


// #define MEMORY_BYTES  4 //including MemHash
// #define MEMORY_SHORTS 8
// #define MEMORY_INTS   0
// #define MEMORY_FLOATS 2

// #define MEMORY_SIZE MEMORY_BYTES+2*MEMORY_SHORTS+4*MEMORY_INTS+4*MEMORY_FLOATS

// //Change to reset memory on upload
// #define MEMORY_HASH 19

// //T(name, default value) -> enum Mem+name
// #define MEMORY_BYTE_LIST T(Tach1Spokes, 10) T(Tach2Spokes, 10) T(Tach3Spokes, 10)
// #define MEMORY_SHORT_LIST T(MinRpm, 20) T(AuxThresh, 1000) T(Tach1Max, 10000) T(Tach2Max, 10000) T(Tach3Max, 10000)\
// T(Tach1Thresh, 2048) T(Tach2Thresh, 2048) T(Tach3Thresh, 2048)
// #define MEMORY_INT_LIST
// #define MEMORY_FLOAT_LIST T(GpsTire, 53.4) T(SlipThresh, 10.0)

#include "stdint.h"
#include "eeprom.h"

enum Memory_Type {
	MemByte,
	MemShort,
	MemInt,
	MemFloat,
};

struct Memory_Handle {
	Eeprom_Handle* eeprom;

	uint8_t byteCount;
	uint8_t shortCount;
	uint8_t intCount;
	uint8_t floatCount;

	uint8_t hash;
};

// #define T(name, reset) Mem##name,
// enum MemoryByteId {
// 	MemDummyByte,
// 	MemHash,
// 	MEMORY_BYTE_LIST
// };
// enum MemoryShortId {
// 	MemDummyShort,
// 	MEMORY_SHORT_LIST
// };
// enum MemoryIntId {
// 	MemDummyInt,
// 	MEMORY_INT_LIST
// };
// enum MemoryFloatId {
// 	MemDummyFloat,
// 	MEMORY_FLOAT_LIST
// };
// #undef T

void Memory_Init(Memory_Handle* mem);
void Memory_Reset(Memory_Handle* mem);

uint8_t Memory_ReadByte(Memory_Handle* mem ,uint8_t loc);
uint16_t Memory_ReadShort(Memory_Handle* mem, uint8_t loc);
uint32_t Memory_ReadInt(Memory_Handle* mem, uint8_t loc);
float Memory_ReadFloat(Memory_Handle* mem, uint8_t loc);

void Memory_WriteByte(Memory_Handle* mem, uint8_t loc, uint8_t val);
void Memory_WriteShort(Memory_Handle* mem, uint8_t loc, uint16_t val);
void Memory_WriteInt(Memory_Handle* mem, uint8_t loc, uint32_t val);
void Memory_WriteFloat(Memory_Handle* mem, uint8_t loc, float val);

#endif
