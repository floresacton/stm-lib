#ifndef INC_QMC5883_H_
#define INC_QMC5883_H_

#include "stdint.h"

#define QMC5883_ADDRESS 0x1A
#define QMC5883_ID 0xFF

#define QMC5883_REG_X_OUT_L 0x00 //r
#define QMC5883_REG_X_OUT_H 0x01 //r
#define QMC5883_REG_Y_OUT_L 0x02 //r
#define QMC5883_REG_Y_OUT_H 0x03 //r
#define QMC5883_REG_Z_OUT_L 0x04 //r
#define QMC5883_REG_Z_OUT_H 0x05 //r

#define QMC5883_REG_STATUS 0x06 //r

#define QMC5883_REG_TEMP_OUT_L 0x07 //r
#define QMC5883_REG_TEMP_OUT_H 0x08 //r

#define QMC5883_REG_MODE 0x09 //r-w

#define QMC5883_REG_CONTROL 0x0A //r-w

#define QMC5883_REG_FBR 0x0B //r-w

#define QMC5883_REG_CHIP_ID 0x0D //r

struct Qmc5883 {
    I2C_HandleTypeDef* hi2c;
    Gpio_Handle* intPin;
};

void Qmc5883_Init(Qmc5883* qmc);

uint8_t Qmc5883_ExtFlag(Qmc5883* qmc, uint16_t pin);
void Qmc5883_ExtHandler(Qmc5883* qmc);

int16_t Qmc5883_X(Qmc5883* qmc);
int16_t Qmc5883_Y(Qmc5883* qmc);
int16_t Qmc5883_Z(Qmc5883* qmc);

int16_t Qmc5883_Temperature(Qmc5883* qmc);

#endif
