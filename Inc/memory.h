#ifndef INC_MEMORY_H_
#define INC_MEMORY_H_

#include "memory_conf.h"

#include "stdint.h"

#define MEMORY_SIZE MEMORY_BYTES+2*MEMORY_SHORTS+4*MEMORY_INTS+4*MEMORY_FLOATS

enum MemoryType {
	MemByte,
	MemShort,
	MemInt,
	MemFloat,
};

#define T(name, reset) Mem##name,
enum MemoryByteId {
	MemDummyByte,
	MemHash,
	MEMORY_BYTE_LIST
};
enum MemoryShortId {
	MemDummyShort,
	MEMORY_SHORT_LIST
};
enum MemoryIntId {
	MemDummyInt,
	MEMORY_INT_LIST
};
enum MemoryFloatId {
	MemDummyFloat,
	MEMORY_FLOAT_LIST
};
#undef T

void Memory_Init(void);
void Memory_Reset(void);

uint8_t Memory_ReadByte(enum MemoryByteId loc);
uint16_t Memory_ReadShort(enum MemoryShortId loc);
uint32_t Memory_ReadInt(enum MemoryIntId loc);
float Memory_ReadFloat(enum MemoryFloatId loc);

void Memory_WriteByte(enum MemoryByteId loc, uint8_t val);
void Memory_WriteShort(enum MemoryShortId loc, uint16_t val);
void Memory_WriteInt(enum MemoryIntId loc, uint32_t val);
void Memory_WriteFloat(enum MemoryFloatId loc, float val);

#endif
