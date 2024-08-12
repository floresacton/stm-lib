#ifndef INC_OLED_H_
#define INC_OLED_H_

// //#define OLED_I2C
// //#define OLED_HANDLE hi2c2
// //#define OLED_ADDRESS (0x3C << 1)

// #define OLED_WIDTH 128
// #define OLED_HEIGHT 64
// #define OLED_BUFFER_SIZE OLED_WIDTH * OLED_HEIGHT / 8

// #define OLED_X_OFFSET 0
// #define OLED_X_OFFSET_LOWER (OLED_X_OFFSET & 0x0F)
// #define OLED_X_OFFSET_UPPER ((OLED_X_OFFSET >> 4) & 0x07)

#include "stdint.h"
#include "font.h"
#include "main.h"

#define OLED_REG_CONTRAST 0x81

enum Oled_Mode {
    Oled_I2c = 0u;
    Oled_Spi = 1u;
};

enum Oled_Color {
    Oled_Black = 0x00u,
    Oled_White = 0xFFu,
};

struct Oled_Handle {
    enum Oled_Mode;

    I2C_HandleTypeDef* hi2c;
    uint8_t address;

    SPI_HandleTypeDef* hspi; // 10MHz max
    Gpio_Handle* csPin;
    Gpio_Handle* dcPin; // command
    Gpio_Handle* rsPin; // reset

    uint8_t width;
    uint8_t height;

    uint8_t offset; // x offset

    // booleans
    uint8_t invertColor;
    uint8_t mirrorVertical;
    uint8_t mirrorHorizontal;

    //calculated
    uint16_t bufSize;
    uint8_t offsetLower;
    uint8_t offsetUpper;
};

void Oled_Init(Oled_Handle* oled);
void Oled_Update(Oled_Handle* oled);

void Oled_Reset(Oled_Handle* oled);

void Oled_WriteCommand(Oled_Handle* oled, uint8_t command);
void Oled_WriteData(Oled_Handle* oled, uint8_t *buf, uint32_t len);
void Oled_FillBuffer(Oled_Handle* oled, uint8_t *buf, uint32_t len);

void Oled_Fill(Oled_Handle* oled, enum Oled_Color color);
void Oled_DrawPixel(Oled_Handle* oled, uint16_t x, uint16_t y);
void Oled_DrawHorizontalLine(Oled_Handle* oled, uint8_t x1, uint8_t x2, uint8_t y);
void Oled_FillRectangle(Oled_Handle* oled, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void Oled_SetCursor(Oled_Handle* oled, uint16_t x, uint16_t y);
void Oled_DrawChar(Oled_Handle* oled, char chr, const struct Font* font);
void Oled_DrawString(Oled_Handle* oled, const char *str, const struct Font* font);
void Oled_DrawBitmap(Oled_Handle* oled, uint16_t x, uint16_t y, const uint8_t* bitmap,
		uint16_t w, uint16_t h);

void Oled_ClearPixel(Oled_Handle* oled, uint16_t x, uint16_t y);
void Oled_ClearRectangle(Oled_Handle* oled, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

void Oled_SetContrast(Oled_Handle* oled, uint8_t val);
void Oled_SetPower(Oled_Handle* oled, uint8_t state);

#endif
