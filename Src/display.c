#include <bitmap.h>
#include <button.h>
#include "display.h"
#include "oled.h"
#include "stdio.h"
#include "gps.h"
#include "tach.h"
#include "control.h"
#include "math.h"
#include "lps22hh.h"
#include "qmc5883.h"

static void control_ratio_update() {
	Oled_ClearRectangle(44, 34, 86, 45);
	Oled_SetCursor(51, 34);
	char buf[DISPLAY_MAX_CHARACTERS];
	sprintf(buf, "%04.0f", Control_Ratio()*1000.0);
	Oled_WriteString(buf, &Font_7x10);
	Oled_DrawBitmap(56, 42, Bitmap_Decimal, 3, 3);
}

static void control_live_update() {
	Oled_ClearRectangle(44, 34, 86, 45);
	Oled_SetCursor(51, 34);
	char buf[DISPLAY_MAX_CHARACTERS];
	sprintf(buf, "%04.0f", Control_Slip()*10.0);
	Oled_WriteString(buf, &Font_7x10);
	Oled_DrawBitmap(70, 42, Bitmap_Decimal, 3, 3);
}

static void rpm_live_update(uint8_t chan) {
	Oled_ClearRectangle(48, 34, 75, 44);
	Oled_SetCursor(48, 34);
	char buf[DISPLAY_MAX_CHARACTERS];
//	sprintf(buf, "%4d", Tach_RPM(chan));
	///////
//	float pressure = 100.0*Lps22hh_Pressure(0)/4096.0-200;
//	float temperature = Lps22hh_Temperature(0)/100.0-4;
//	Oled_Fill(0);
//	Oled_SetCursor(48, 24);
//	sprintf(buf, "%5.1f", temperature);
//	Oled_WriteString(buf, &font_7x10);
//	Oled_SetCursor(48, 34);
//	sprintf(buf, "%5.1f", pressure);
//	Oled_WriteString(buf, &font_7x10);
//	Oled_SetCursor(48, 44);
//
//	float kelvin = temperature+273.15;
//
////	    var d = - 0.0065;
////	    var j = Math.pow((pressure/sea level, (8.31432 * -0.0065) / (9.80665 * 0.0289644));
////	    return (((kelvin) * ((1 / j) - 1)) / d)
//
//	float height = kelvin/0.0065*(1-pow(pressure/101325, 0.190263));
//	sprintf(buf, "%5.1f", height);
	//////
//	uint8_t status = Qmc5883_Status();
//	Qmc5883_Update();
	int16_t x = Qmc5883_X();
	int16_t y = Qmc5883_Y();
	int16_t z = Qmc5883_Z();
	int16_t t = Qmc5883_Temperature();
	Oled_Fill(0);
	Oled_SetCursor(28, 14);
	sprintf(buf, "%06hd", t);
	Oled_WriteString(buf, &Font_7x10);

	Oled_SetCursor(28, 24);
	sprintf(buf, "%06hd", x);
//	sprintf(buf, "%5.1f", x);
	Oled_WriteString(buf, &Font_7x10);
	Oled_SetCursor(28, 34);
	sprintf(buf, "%06hd", y);
//	sprintf(buf, "%5.1f", y);
	Oled_WriteString(buf, &Font_7x10);
	Oled_SetCursor(28, 44);
	sprintf(buf, "%06hd", z);
	Oled_WriteString(buf, &Font_7x10);
}

static void tach1_live_update(void) {
	rpm_live_update(Tach1);
}

static void tach2_live_update(void) {
	rpm_live_update(Tach2);
}

static void tach3_live_update(void) {
	rpm_live_update(Tach3);
}

static void gps_live_update(void) {
	Oled_ClearRectangle(44, 34, 86, 45);
	if (Gps_Fix()) {
		Oled_SetCursor(51, 34);
		char buf[DISPLAY_MAX_CHARACTERS];
		sprintf(buf, "%4.0f", Gps_Speed()*10.0);
		Oled_WriteString(buf, &Font_7x10);
		Oled_DrawBitmap(70, 42, Bitmap_Decimal, 3, 3);
	}else{
		Oled_SetCursor(43, 34);
		Oled_WriteString("No Fix", &Font_7x10);
	}
}

void compass_live_update(void) {

}

void barometer_live_update(void) {

}

void gyro_live_update(void) {

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
static struct Screen control_live = {.type = ScreenLive, .update = &control_live_update};
static struct Screen control_ratio = {.type = ScreenLive, .update = &control_ratio_update};
static struct Screen control_slip = {.type = ScreenEdit, .memType = MemFloat, .loc = MemSlipThresh};
static struct Screen control_aux = {.type = ScreenEdit, .memType = MemShort, .loc = MemAuxThresh};
static struct Screen control_min = {.type = ScreenEdit, .memType = MemShort, .loc = MemMinRpm};

static struct Option control_options[5] = {
		{.type = OptionRedirect, .text = "Live", .redirect = &control_live},
		{.type = OptionRedirect, .text = "Ratio", .redirect = &control_ratio},
		{.type = OptionRedirect, .text = "Slip", .redirect = &control_slip},
		{.type = OptionRedirect, .text = "Aux", .redirect = &control_aux},
		{.type = OptionRedirect, .text = "Min", .redirect = &control_min}};
static struct Screen control = {.type = ScreenScroll, .optionCount = 5, .options = control_options};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
static struct Screen tach1_live = {.type = ScreenLive, .update = &tach1_live_update};
static struct Screen tach1_spokes = {.type = ScreenEdit, .memType = MemByte, .loc = MemTach1Spokes};
static struct Screen tach1_thresh = {.type = ScreenEdit, .memType = MemShort, .loc = MemTach1Thresh};
static struct Screen tach1_max = {.type = ScreenEdit, .memType = MemShort, .loc = MemTach1Max};

static struct Option tach1_options[4] = {
		{.type = OptionRedirect, .text = "Live", .redirect = &tach1_live},
		{.type = OptionRedirect, .text = "Spokes", .redirect = &tach1_spokes},
		{.type = OptionRedirect, .text = "Thresh", .redirect = &tach1_thresh},
		{.type = OptionRedirect, .text = "Max", .redirect = &tach1_max}};
static struct Screen tach1 = {.type = ScreenScroll, .optionCount = 4, .options = tach1_options};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
static struct Screen tach2_live = {.type = ScreenLive, .update = &tach2_live_update};
static struct Screen tach2_spokes = {.type = ScreenEdit, .memType = MemByte, .loc = MemTach2Spokes};
static struct Screen tach2_thresh = {.type = ScreenEdit, .memType = MemShort, .loc = MemTach2Thresh};
static struct Screen tach2_max = {.type = ScreenEdit, .memType = MemShort, .loc = MemTach2Max};

static struct Option tach2_options[4] = {
		{.type = OptionRedirect, .text = "Live", .redirect = &tach2_live},
		{.type = OptionRedirect, .text = "Spokes", .redirect = &tach2_spokes},
		{.type = OptionRedirect, .text = "Thresh", .redirect = &tach2_thresh},
		{.type = OptionRedirect, .text = "Max", .redirect = &tach2_max}};
static struct Screen tach2 = {.type = ScreenScroll, .optionCount = 4, .options = tach2_options};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
static struct Screen tach3_live = {.type = ScreenLive, .update = &tach3_live_update};
static struct Screen tach3_spokes = {.type = ScreenEdit, .memType = MemByte, .loc = MemTach3Spokes};
static struct Screen tach3_thresh = {.type = ScreenEdit, .memType = MemShort, .loc = MemTach3Thresh};
static struct Screen tach3_max = {.type = ScreenEdit, .memType = MemShort, .loc = MemTach3Max};

static struct Option tach3_options[4] = {
		{.type = OptionRedirect, .text = "Live", .redirect = &tach3_live},
		{.type = OptionRedirect, .text = "Spokes", .redirect = &tach3_spokes},
		{.type = OptionRedirect, .text = "Thresh", .redirect = &tach3_thresh},
		{.type = OptionRedirect, .text = "Max", .redirect = &tach3_max}};
static struct Screen tach3 = {.type = ScreenScroll, .optionCount = 4, .options = tach3_options};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
static struct Screen gps_live = {.type = ScreenLive, .update = &gps_live_update};
static struct Screen gps_tire = {.type = ScreenEdit, .memType = MemFloat, .loc = MemGpsTire};

static struct Option gps_options[2] = {
		{.type = OptionRedirect, .text = "Live", .redirect = &gps_live},
		{.type = OptionRedirect, .text = "Tire", .redirect = &gps_tire}};
static struct Screen gps = {.type = ScreenScroll, .optionCount = 2, .options = gps_options};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
static struct Screen compass_live = {.type = ScreenLive, .update = &compass_live_update};

static struct Option compass_options[1] = {
		{.type = OptionRedirect, .text = "Live", .redirect = &compass_live}};
static struct Screen compass = {.type = ScreenScroll, .optionCount = 1, .options = compass_options};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
static struct Screen barometer_live = {.type = ScreenLive, .update = &barometer_live_update};

static struct Option barometer_options[1] = {
		{.type = OptionRedirect, .text = "Live", .redirect = &barometer_live}};
static struct Screen barometer = {.type = ScreenScroll, .optionCount = 1, .options = barometer_options};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
static struct Screen gyro_live = {.type = ScreenLive, .update = &gyro_live_update};

static struct Option gyro_options[1] = {
		{.type = OptionRedirect, .text = "Live", .redirect = &gyro_live}};
static struct Screen gyro = {.type = ScreenScroll, .optionCount = 1, .options = gyro_options};
/////////////////////////////////////////////////////////////////////////////////////////////////////////
static struct Option menu_options[9] = {
		{.type = OptionRedirect, .text = "Control", .redirect = &control},
		{.type = OptionRedirect, .text = "Tach 1", .redirect = &tach1},
		{.type = OptionRedirect, .text = "Tach 2", .redirect = &tach2},
		{.type = OptionRedirect, .text = "Tach 3", .redirect = &tach3},
		{.type = OptionRedirect, .text = "GPS", .redirect = &gps},
		{.type = OptionRedirect, .text = "Compass", .redirect = &compass},
		{.type = OptionRedirect, .text = "Barometer", .redirect = &barometer},
		{.type = OptionRedirect, .text = "Gyro/Accel", .redirect = &gyro},
		{.type = OptionAction, .text = "Reset", .action = &Memory_Reset}};
static struct Screen menu = {.type = ScreenScroll, .optionCount = 9, .options =
		menu_options, };
/////////////////////////////////////////////////////////////////////////////////////////////////////////

static struct Screen *stack[DISPLAY_MAX_STACK] = {&menu};
static uint8_t stackIndex = 0;

//edit variables
static int8_t incrementIndex;
static float increment;
static float valBuf;

static uint8_t int_max(uint8_t a, uint8_t b) {
	if (a > b) {
		return a;
	}
	return b;
}

static void display_update_cursor(void) {
	Oled_ClearRectangle(10, 16, 18, 64);
	Oled_SetCursor(10, 16 * (stack[stackIndex]->select - stack[stackIndex]->scroll + 1) + 6);
	Oled_WriteString(">", &Font_7x10);
}

static void display_update_options(void) {
	for (uint8_t i = 0; i < 3; i++) {
		Oled_ClearRectangle(20, 16 * (i + 1), 122, 16 * (i + 1) + 16);
		if (i < stack[stackIndex]->optionCount) {
			Oled_SetCursor(20, 16 * (i + 1) + 6);
			Oled_WriteString(stack[stackIndex]->options[stack[stackIndex]->scroll+i].text, &Font_7x10);
			if (stack[stackIndex]->options[stack[stackIndex]->scroll+i].type == OptionToggle) {
				if (Memory_ReadByte(stack[stackIndex]->options[stack[stackIndex]->scroll+i].toggleLoc)) {
					Oled_WriteString(stack[stackIndex]->options[stack[stackIndex]->scroll+i].on, &Font_7x10);
				}else{
					Oled_WriteString(stack[stackIndex]->options[stack[stackIndex]->scroll+i].off, &Font_7x10);
				}
			}
		}
	}
	if (stack[stackIndex]->optionCount > 3) {
		Oled_ClearRectangle(124, 18, 126, 62);
		Oled_DrawBitmap(122, 16, Bitmap_Scroll, 6, 48);
		//unit = 44/option_count
		//start = 18 + unit*scroll
		//end = 18 + unit*(scroll+3) - 1
		const uint8_t start = 18 + 44*stack[stackIndex]->scroll/stack[stackIndex]->optionCount;
		const uint8_t end = 18 + 44*(stack[stackIndex]->scroll+3)/stack[stackIndex]->optionCount;
		Oled_FillRectangle(124, start, 126, end);
	}else{
		Oled_ClearRectangle(122, 16, 128, 64);
	}
}

static void display_load_variable(void) {
	if (stack[stackIndex]->memType == MemByte) {
		valBuf = Memory_ReadByte(stack[stackIndex]->loc);
	}else if (stack[stackIndex]->memType == MemShort) {
		valBuf = Memory_ReadShort(stack[stackIndex]->loc);
	}else if (stack[stackIndex]->memType == MemFloat) {
		valBuf = Memory_ReadFloat(stack[stackIndex]->loc);
	}
}

static void display_save_variable(void) {
	if (stack[stackIndex]->memType == MemByte) {
		Memory_WriteByte(stack[stackIndex]->loc, valBuf);
	}else if (stack[stackIndex]->memType == MemShort) {
		Memory_WriteShort(stack[stackIndex]->loc, valBuf);
	}else if (stack[stackIndex]->memType == MemFloat) {
		Memory_WriteFloat(stack[stackIndex]->loc, valBuf);
	}
}

static void display_update_increment(void) {
	Oled_ClearRectangle(44, 31, 88, 33);
	Oled_DrawBitmap(72-7*incrementIndex, 31, Bitmap_Increment, 7, 2);
}

static void display_update_variable(void) {
	Oled_ClearRectangle(44, 34, 86, 44);
	Oled_SetCursor(44, 34);
	char buf[DISPLAY_MAX_CHARACTERS];
	if (stack[stackIndex]->memType == MemFloat) {
		sprintf(buf, "  %04.0f", valBuf*10.0);
		Oled_WriteString(buf, &Font_7x10);
		Oled_DrawBitmap(78, 42, Bitmap_Decimal, 3, 3);
	}else if (stack[stackIndex]->memType == MemShort) {
		sprintf(buf, "%05.0f", valBuf);
		Oled_WriteString(buf, &Font_7x10);
	}else{
		sprintf(buf, "  %03.0f", valBuf);
		Oled_WriteString(buf, &Font_7x10);
	}
}

static void display_init_screen(void) {
	Oled_Fill(OledWhite);
	if (stack[stackIndex]->type == ScreenScroll) {
		display_update_options();
		display_update_cursor();
	}else if (stack[stackIndex]->type == ScreenEdit) {
		incrementIndex = 0;
		increment = 1;
		display_load_variable();
		display_update_increment();
		display_update_variable();
	}else if (stack[stackIndex]->type == ScreenLive) {
		//DO NOTHING
	}
}

void Display_Init(void) {
	Oled_DrawBitmap(0, 0, Bitmap_Logo, 128, 16);
	Oled_DrawBitmap(120, 0, Bitmap_NoSignal, 8, 8);
	display_init_screen();
	Oled_Update();
}

void Display_Update(void) {
	if (stack[stackIndex]->type == ScreenScroll) {
		if (Button_Pressed(ButtonUp)) {
			if (stack[stackIndex]->select == stack[stackIndex]->scroll && stack[stackIndex]->optionCount > 3) {
				if (!stack[stackIndex]->select) {
					stack[stackIndex]->select = stack[stackIndex]->optionCount - 1;
					stack[stackIndex]->scroll = int_max(2, stack[stackIndex]->select) - 2;
					display_update_cursor();
				} else {
					stack[stackIndex]->select--;
					stack[stackIndex]->scroll--;
				}
				display_update_options();
			} else {
				if (!stack[stackIndex]->select) {
					stack[stackIndex]->select = stack[stackIndex]->optionCount - 1;
				} else {
					stack[stackIndex]->select--;
				}
				display_update_cursor();
			}
			Oled_Update();
		}else if (Button_Pressed(ButtonDown)) {
			if (stack[stackIndex]->select == stack[stackIndex]->scroll + 2 && stack[stackIndex]->optionCount > 3) {
				if (stack[stackIndex]->select == stack[stackIndex]->optionCount - 1) {
					stack[stackIndex]->select = 0;
					stack[stackIndex]->scroll = 0;
					display_update_cursor();
				} else {
					stack[stackIndex]->select++;
					stack[stackIndex]->scroll++;
				}
				display_update_options();
			} else {
				if (stack[stackIndex]->select == stack[stackIndex]->optionCount-1) {
					stack[stackIndex]->select = 0;
				}else{
					stack[stackIndex]->select++;
				}
				display_update_cursor();
			}
			Oled_Update();
		}else if (Button_Pressed(ButtonEnter)) {
			if (stack[stackIndex]->options[stack[stackIndex]->select].type == OptionRedirect) {
				stack[stackIndex+1] = stack[stackIndex]->options[stack[stackIndex]->select].redirect;
				stackIndex++;
				display_init_screen();
			}else if (stack[stackIndex]->options[stack[stackIndex]->select].type == OptionToggle) {
				const uint8_t loc = stack[stackIndex]->options[stack[stackIndex]->select].toggleLoc;
				Memory_WriteByte(loc, !Memory_ReadByte(loc));
				display_update_options();
			}else if (stack[stackIndex]->options[stack[stackIndex]->select].type == OptionAction) {
				(*stack[stackIndex]->options[stack[stackIndex]->select].action)();
			}
			Oled_Update();
		}else if (Button_Pressed(ButtonBack)) {
			stack[stackIndex]->scroll = 0;
			stack[stackIndex]->select = 0;
			if (stackIndex > 0) {
				stackIndex--;
			}
			display_init_screen();
			Oled_Update();
		}
	}else if (stack[stackIndex]->type == ScreenEdit) {
		if (Button_Pressed(ButtonUp)) {
			valBuf += increment;
			if (stack[stackIndex]->memType == MemByte && valBuf > 255) {
				valBuf = 255;
			}
			if (stack[stackIndex]->memType == MemShort && valBuf > 65535) {
				valBuf = 65535;
			}
			display_update_variable();
			Oled_Update();
		}else if (Button_Pressed(ButtonDown)) {
			valBuf -= increment;
			if (valBuf < 0) {
				valBuf = 0;
			}
			display_update_variable();
			Oled_Update();
		}else if (Button_Pressed(ButtonEnter)) {
			incrementIndex++;
			if (stack[stackIndex]->memType == MemFloat) {
				if (incrementIndex > 2) {
					incrementIndex = -1;
				}
			}else if (stack[stackIndex]->memType == MemByte){
				if (incrementIndex > 2) {
					incrementIndex = 0;
				}
			}else{
				if (incrementIndex > 4) {
					incrementIndex = 0;
				}
			}
			increment = 1;
			for (uint8_t i = 0; i < incrementIndex; i++) {
				increment *= 10;
			}
			for (int8_t i = incrementIndex; i < 0; i++) {
				increment /= 10;
			}
			display_update_increment();
			Oled_Update();
		}else if (Button_Pressed(ButtonBack)) {
			display_save_variable();
			stackIndex--;
			display_init_screen();
			Oled_Update();
		}
	}else if (stack[stackIndex]->type == ScreenLive) {
		(*stack[stackIndex]->update)();
		if (Button_Pressed(ButtonBack)) {
			stackIndex--;
			display_init_screen();
		}
		Oled_Update();
	}
}

void Display_UpdateGPS(uint8_t fix) {
	Oled_ClearRectangle(120, 0, 128, 8);
	if (fix) {
		Oled_DrawBitmap(120, 0, Bitmap_Signal, 8, 8);
	}else{
		Oled_DrawBitmap(120, 0, Bitmap_NoSignal, 8, 8);
	}
	Oled_Update();
}
