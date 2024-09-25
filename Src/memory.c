#include "memory.h"
#include "eeprom.h"
#include "stdlib.h"
#include "platform.h"

void Memory_Init(struct Memory_Handle* handle) {
	for (uint8_t i = 0; i < handle->count; i++) {
		struct Memory_Variable* var = handle->vars[i];
		var->address = 4 * (i + 1);

		float value = var->max;
		int8_t digit = -1;
		while (value >= 1) {
			value /= 10.0f;
			digit++;
		}
		var->maxDigit = digit;
	}

	float hash;
	Eeprom_Read(handle->eeprom, 0, (uint8_t*)&hash, 4);
	if (hash != handle->hash) {
		Eeprom_Write(handle->eeprom, 0, (uint8_t*)&hash, 4);
		Memory_Reset(handle);
	}else{
		for (uint8_t i = 0; i < handle->count; i++) {
			struct Memory_Variable* var = handle->vars[i];
			Eeprom_Read(handle->eeprom, var->address, (uint8_t*)&var->value, 4);
		}
	}
}

void Memory_Reset(struct Memory_Handle* handle) {
	for (uint8_t i = 0; i < handle->count; i++) {
		struct Memory_Variable* var = handle->vars[i];
		Eeprom_Write(handle->eeprom, var->address, (uint8_t*)&var->reset, 4);
		var->value = var->reset;
	}
}

void Memory_Save(struct Memory_Handle* handle, struct Memory_Variable* var) {
	Eeprom_Write(handle->eeprom, var->address, (uint8_t*)&var->reset, 4);
}

void Memory_Print(struct Memory_Variable* var, char* buf) {
	// TODO
}
