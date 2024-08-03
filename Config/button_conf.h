#ifndef CONFIG_BUTTON_CONF_H_
#define CONFIG_BUTTON_CONF_H_

#include "main.h"

#define BUTTON_HANDLE htim3 //50hz

#define BUTTON_COUNT 4

#define BUTTON_LIST T(BTN1) T(BTN2) T(BTN3) T(BTN4)

enum ButtonId {
	ButtonUp,
	ButtonDown,
	ButtonEnter,
	ButtonBack,
};

#endif
