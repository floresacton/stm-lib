#include <lps22hh.h>
#include "string.h"
#include "main.h"

extern SPI_HandleTypeDef LPS22HH_HANDLE;

static GPIO_TypeDef *chipSelectPorts[LPS22HH_COUNT] = { CSP_GPIO_Port};
static uint16_t chipSelectsPins[LPS22HH_COUNT] = { CSP_Pin };

static uint8_t data[LPS22HH_COUNT][LPS22HH_DATA_SIZE] = {0};
static uint32_t* pressures[LPS22HH_COUNT];
static int16_t* temperatures[LPS22HH_COUNT];

void lps22hh_write_register(enum Lps22hhId lps, uint8_t reg, uint8_t data) {
	HAL_GPIO_WritePin(chipSelectPorts[lps], chipSelectsPins[lps],
			GPIO_PIN_RESET);
	HAL_SPI_Transmit(&LPS22HH_HANDLE, &reg, 1, HAL_MAX_DELAY);
	HAL_SPI_Transmit(&LPS22HH_HANDLE, &data, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(chipSelectPorts[lps], chipSelectsPins[lps], GPIO_PIN_SET);
}

uint8_t lps22hh_read_register(enum Lps22hhId lps, uint8_t reg) {
	uint8_t data = 0;
	uint8_t regRW = 0x80 | reg;
	HAL_GPIO_WritePin(chipSelectPorts[lps], chipSelectsPins[lps],
			GPIO_PIN_RESET);
	HAL_SPI_Transmit(&LPS22HH_HANDLE, &regRW, 1, HAL_MAX_DELAY);
	HAL_SPI_Receive(&LPS22HH_HANDLE, &data, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(chipSelectPorts[lps], chipSelectsPins[lps], GPIO_PIN_SET);
	return data;
}

void lps22hh_read_registers(enum Lps22hhId lps, uint8_t reg, uint8_t *output, uint16_t len) {
	uint8_t regRW = 0x80 | reg;
	HAL_GPIO_WritePin(chipSelectPorts[lps], chipSelectsPins[lps],
			GPIO_PIN_RESET);
	HAL_SPI_Transmit(&LPS22HH_HANDLE, &regRW, 1, HAL_MAX_DELAY);
	HAL_SPI_Receive(&LPS22HH_HANDLE, output, len, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(chipSelectPorts[lps], chipSelectsPins[lps], GPIO_PIN_SET);
}

void Lps22hh_Init(void) {
	for (uint8_t i = 0; i < LPS22HH_COUNT; i++) {
		if (lps22hh_read_register(i, LPS22HH_REG_WHO_AM_I) != LPS22HH_ID) {
			Error_Handler();
		}
		pressures[i] = (uint32_t*)data[i];
		temperatures[i] = (int16_t*)data[i]+3;

		//configure ODR 200hz
		//enable low pass filter at bandwidth odr/9
//		lps22hh_write_register(cs, LPS22HH_REG_CTRL_REG1, 0b01110000);

		//configure ODR 200hz ODR/20 filter
		lps22hh_write_register(i, LPS22HH_REG_CTRL_REG1, 0b01111100);
	}
}

uint8_t Lps22hh_ExtFlag(uint16_t pin) {
	return pin == LPS22HH_INT_PIN;
}

void Lps22hh_ExtHandler(void) {
	for (uint8_t i = 0; i < LPS22HH_COUNT; i++) {
		lps22hh_read_registers(i, LPS22HH_REG_PRESS_XL, data[i], LPS22HH_DATA_SIZE);
	}
}

uint32_t Lps22hh_Pressure(enum Lps22hhId lps) {
	return (*pressures[lps])&0x00FFFFFF;
}

int16_t Lps22hh_Temperature(enum Lps22hhId lps) {
	return *temperatures[lps];
}
