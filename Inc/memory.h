#ifndef INC_MEMORY_H_
#define INC_MEMORY_H_

#include "stdint.h"

#define MEMORY_BYTES 4
#define MEMORY_SHORTS 8
#define MEMORY_FLOATS 2
#define MEMORY_SIZE MEMORY_BYTES+2*MEMORY_SHORTS+4*MEMORY_FLOATS

//Change to reset memory on upload
#define MEMORY_HASH 18

enum MemoryType {
	MemByte,
	MemShort,
	MemFloat,
};

enum MemoryByteId {
	MemHash,

	//pulses per revolution
	MemTach1Spokes,
	MemTach2Spokes,
	MemTach3Spokes,
};
enum MemoryShortId {
	//min front wheel rpm
	MemMinRpm,

	MemAuxThresh,//rpm

	//max rpms for ignoring higher
	MemTach1Max,
	MemTach2Max,
	MemTach3Max,

	//all out of 4096
	MemTach1Thresh,
	MemTach2Thresh,
	MemTach3Thresh,
};
enum MemoryFloatId {
	MemGpsTire,//inches

	MemSlipThresh,//percent
};

void Memory_Init(void);
void Memory_Reset(void);

uint8_t Memory_ReadByte(enum MemoryByteId loc);
uint16_t Memory_ReadShort(enum MemoryShortId loc);
float Memory_ReadFloat(enum MemoryFloatId loc);

void Memory_WriteByte(enum MemoryByteId loc, uint8_t val);
void Memory_WriteShort(enum MemoryShortId loc, uint16_t val);
void Memory_WriteFloat(enum MemoryFloatId loc, float val);

#endif
