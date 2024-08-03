#ifndef CONFIG_LPS22HH_CONF_H_
#define CONFIG_LPS22HH_CONF_H_

//max spi speed 10MHz
#define LPS22HH_HANDLE hspi1
#define LPS22HH_INT_PIN DRDYP_Pin

#define LPS22HH_COUNT 1

enum Lps22hhId {
	Lps22hh1,
};

#endif
