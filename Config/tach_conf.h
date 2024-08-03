#ifndef CONFIG_TACH_CONF_H_
#define CONFIG_TACH_CONF_H_

#define TACH_COUNT 3

#define TACH_REF_HANDLE htim1 //50kHz
#define TACH_REF_FREQ 50000

#define TACH_CALC_HANDLE htim2 //50Hz
#define TACH_CALC_FREQ 50

enum TachId {
	Tach1,
	Tach2,
	Tach3,
};

#endif
