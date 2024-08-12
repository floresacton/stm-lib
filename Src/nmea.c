#include "nmea.h"
#include "stdint.h"
#include "str.h"

static char nmea_parse_hem(char* str) {
	if (*str) {
		return *str;
	}
	return '-';
}

static float nmea_parse_coord(char* str, uint8_t degree_digits) {
	uint8_t deg = 0;
	for (uint8_t i = 0; i < degree_digits && *str; i++) {
		deg *= 10;
		deg += *str-'0';
		str++;
	}
	const float min = Str_ParseFloat(str);
	return min/60.0 + (float)deg;
}

static void nmea_parse_utc(struct Nmea_Handle* handle, char* str) {
	uint8_t hour = 0;
	for (uint8_t i = 0; i < 2 && *str; i++) {
		hour *= 10;
		hour += *str-'0';
		str++;
	}
	uint8_t minute = 0;
	for (uint8_t i = 0; i < 2 && *str; i++) {
		minute *= 10;
		minute += *str-'0';
		str++;
	}
	const float second = Str_ParseFloat(str);

	handle->hour = hour;
	handle->minute = minute;
	handle->second = second;
}

static void nmea_parse_date(struct Nmea_Handle* handle, char* str) {
	uint8_t day = 0;
	for (uint8_t i = 0; i < 2 && *str; i++) {
		day *= 10;
		day += *str-'0';
		str++;
	}
	uint8_t month = 0;
	for (uint8_t i = 0; i < 2 && *str; i++) {
		month *= 10;
		month += *str-'0';
		str++;
	}
	uint8_t year = 0;
	for (uint8_t i = 0; i < 2 && *str; i++) {
		year *= 10;
		year += *str-'0';
		str++;
	}
	handle->day = day;
	handle->month = month;
	handle->year = year;
}

static void nmea_parse_msg(struct Nmea_Handle* handle, char* start) {
	if (!Str_Longer(start, NMEA_MIN_LENGTH)) {
		return;
	}
	start += 2;
	if (Str_Comp(start, "GGA", 3)) {
		start += 3;
		uint8_t count = 0;
		char last = ' ';
		while (last) {
			start++;
			char* end = Str_To(start, ',');
			last = *end;
			*end = '\0';
			//start is a readable string now
			switch (count) {
			case 6:
				handle->satCount = Str_ParseByte(start);
				break;
			case 8:
				handle->altitude = Str_ParseFloat(start);
				break;
			}
			start = end;
			count++;
		}
		return;
	}
	if (Str_Comp(start, "RMC", 3)) {
		start += 3;
		uint8_t count = 0;
		char last = ' ';
		while (last) {
			start++;
			char* end = Str_To(start, ',');
			last = *end;
			*end = '\0';
			//start is a readable string now
			switch (count) {
			case 0:
				nmea_parse_utc(handle, start);
				break;
			case 1:
				handle->fix = *start == 'A';
				break;
			case 2:
				handle->latitude = nmea_parse_coord(start, 2);
				break;
			case 3:
				handle->latHem = nmea_parse_hem(start);
				break;
			case 4:
				handle->longitude = nmea_parse_coord(start, 3);
				break;
			case 5:
				handle->lonHem = nmea_parse_hem(start);
				break;
			case 8:
				nmea_parse_date(handle, start);
				break;
			}
			start = end;
			count++;
		}
		return;
	}
	if (Str_Comp(start, "VTG", 3)) {
		start += 3;
		start = Str_Count(start, ',', 7);
		start++;
		char* speed_end = Str_To(start, ',');
		*speed_end = '\0';
		handle->speed = Str_ParseFloat(start) * 0.621371;
		return;
	}
}

void Nmea_Init(struct Nmea_Handle* handle) {
	handle->fix = 0;
	handle->satCount = 0;

	handle->hour = 0;
	handle->minute = 0;
	handle->second = 0;

	handle->year = 0;
	handle->month = 0;
	handle->day = 0;

	handle->latitude = 0;
	handle->latHem = '-';
	handle->longitude = 0;
	handle->lonHem = '-';
	handle->altitude = 0;

	handle->speed = 0;
}

void Nmea_Parse(struct Nmea_Handle* handle, char* msg) {
	char* start = Str_To(msg, '$');
	char last = ' ';
	while (last) {
		start++;
		char* end = Str_To(start, '$');
		last = *end;
		*end = '\0';
		nmea_parse_msg(handle, start);
		start = end;
	}
}

void Nmea_Timepulse(struct Nmea_Handle* handle) {
//	handle->second += 0.1;
}
