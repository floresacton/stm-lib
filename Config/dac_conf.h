#ifndef CONFIG_DAC_CONF_H_
#define CONFIG_DAC_CONF_H_

#define DAC_COUNT 3

#define DAC_LIST T(hdac1, DAC_CHANNEL_2) T(hdac1, DAC_CHANNEL_1) T(hdac3, DAC_CHANNEL_1)

enum DacId {
	Dac1,
	Dac2,
	Dac3,
};

#endif
