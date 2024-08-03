#ifndef INC_LPS22HH_H_
#define INC_LPS22HH_H_

#include "lps22hh_conf.h"

#include "stdint.h"

#define LPS22HH_DATA_SIZE 5

#define LPS22HH_ADDRESS 0xBA
#define LPS22HH_ID 0b10110011

//registers
#define LPS22HH_REG_INTERRUPT_CFG 0x0B //r-w

#define LPS22HH_REG_THS_P_L 0x0C //r-w
#define LPS22HH_REG_THS_P_H 0x0D //r-w

#define LPS22HH_REG_IF_CTRL 0x0E //r-w

#define LPS22HH_REG_WHO_AM_I 0x0F //r

#define LPS22HH_REG_CTRL_REG1 0x10 //r-w
#define LPS22HH_REG_CTRL_REG2 0x11 //r-w
#define LPS22HH_REG_CTRL_REG3 0x12 //r-w

#define LPS22HH_REG_FIFO_CTRL 0x13 //r-w
#define LPS22HH_REG_FIFO_WTM  0x14 //r-w

#define LPS22HH_REG_REF_P_L 0x15 //r
#define LPS22HH_REG_REF_P_H 0x16 //r

#define LPS22HH_REG_RPDS_L 0x18 //r-w
#define LPS22HH_REG_RPDS_H 0x19 //r-w

#define LPS22HH_REG_INT_SOURCE 0x24 //r

#define LPS22HH_REG_FIFO_STATUS1 0x25 //r
#define LPS22HH_REG_FIFO_STATUS2 0x26 //r

#define LPS22HH_REG_STATUS 0x27 //r

#define LPS22HH_REG_PRESS_XL 0x28 //r
#define LPS22HH_REG_PRESS_L  0x29 //r
#define LPS22HH_REG_PRESS_H  0x2A //r

#define LPS22HH_REG_TEMP_L  0x2B //r
#define LPS22HH_REG_TEMP_H  0x2C //r

#define LPS22HH_REG_FIFO_DATA_OUT_PRESS_XL 0x78 //r
#define LPS22HH_REG_FIFO_DATA_OUT_PRESS_L 0x79 //r
#define LPS22HH_REG_FIFO_DATA_OUT_PRESS_H 0x7A //r

#define LPS22HH_REG_FIFO_DATA_OUT_TEMP_L 0x7B //r
#define LPS22HH_REG_FIFO_DATA_OUT_TEMP_H 0x7C //r

void Lps22hh_Init(void);

uint8_t Lps22hh_ExtFlag(uint16_t pin);
void Lps22hh_ExtHandler(void);

uint32_t Lps22hh_Pressure(enum Lps22hhId lps);
int16_t Lps22hh_Temperature(enum Lps22hhId lps);

#endif
