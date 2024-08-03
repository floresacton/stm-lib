#ifndef INC_OLED_H_
#define INC_OLED_H_

#include "oled_conf.h"

#include "stdint.h"
#include "font.h"
#include "main.h"

#define OLED_REG_CONTRAST 0x81

enum OledColor {
    OledBlack = 0x00u,
    OledWhite = 0xFFu,
};

void Oled_Init(void);
void Oled_Update(void);

void Oled_Reset(void);

void Oled_WriteCommand(uint8_t byte);
void Oled_WriteData(uint8_t *buf, uint32_t buff_size);
void Oled_FillBuffer(uint8_t *buf, uint32_t len);

void Oled_Fill(enum OledColor color);
void Oled_ClearPixel(uint16_t x, uint16_t y);
void Oled_DrawPixel(uint16_t x, uint16_t y);
void Oled_ClearRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void Oled_FillRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void Oled_SetCursor(uint16_t x, uint16_t y);
void Oled_WriteChar(char chr, const struct Font* font);
void Oled_WriteString(const char *str, const struct Font* font);
void Oled_DrawBitmap(uint16_t x, uint16_t y, const uint8_t* bitmap,
		uint16_t w, uint16_t h);

void Oled_SetContrast(uint8_t val);
void Oled_SetPower(uint8_t on);

#endif
