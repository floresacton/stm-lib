#include "memory.h"
#include "eeprom.h"
#include "stdlib.h"

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
    HAL_Delay(10);
    if (hash != handle->hash) {
        Eeprom_Write(handle->eeprom, 0, (uint8_t*)&handle->hash, 4);
        HAL_Delay(10);
        Memory_Reset(handle);
    }else{
        float buf[handle->count];
        Eeprom_Read(handle->eeprom, 4, (uint8_t*)buf, handle->count*4);
        HAL_Delay(100);
        for (uint8_t i = 0; i < handle->count; i++) {
            handle->vars[i]->value = buf[i];
        }
    }
}

void Memory_Reset(struct Memory_Handle* handle) {
    for (uint8_t i = 0; i < handle->count; i++) {
        struct Memory_Variable* var = handle->vars[i];
        Eeprom_Write(handle->eeprom, var->address, (uint8_t*)&var->reset, 4);
        HAL_Delay(10);
        var->value = var->reset;
    }
}

void Memory_Save(struct Memory_Handle* handle, struct Memory_Variable* var) {
    Eeprom_Write(handle->eeprom, var->address, (uint8_t*)&var->reset, 4);
}

uint8_t Memory_Print(char* buf, struct Memory_Variable* var) {
    const uint8_t chars = var->maxDigit - var->minDigit + (var->minDigit != 0);

    float val = var->value;
    for (uint8_t i = 0; i < -var->minDigit; i++) {
        val *= 10;
    }

    uint32_t collect = (uint32_t)val;
    for (int8_t i = 0; i < chars; i++) {
        buf[chars-1-i] = '0' + (collect % 10);
        collect /= 10;

        if (i-var->minDigit == 1) {
            i++;
            buf[chars-1-i] = '.';
        }
    }
    buf[chars] = 0;
    return chars;
}
