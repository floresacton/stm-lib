#ifndef CONFIG_ICM42688_CONF_H_
#define CONFIG_ICM42688_CONF_H_

#define ICM42688_SPI_HANDLE hspi1 //24Mhz max
#define ICM42688_INT_PIN INTG_Pin

//ensure no overflow
#define ICM42688_REF_HANDLE htim4
#define ICM42688_REF_FREQ 16000000

#define ICM42688_CALC_FREQ 500

#endif
