#ifndef INC_NMEA_H_
#define INC_NMEA_H_

#include "stdint.h"

#define NMEA_BUF_SIZE 90
#define NMEA_MIN_LENGTH 5

struct Nmea_Handle {
	// internal
	uint8_t fix;
	uint8_t satCount;

	uint8_t hour;
	uint8_t minute;
	float second;

	uint8_t year;
	uint8_t month;
	uint8_t day;

	float latitude;
	char latHem;
	float longitude;
	char lonHem;
	float altitude;

	float speed;
};

void Nmea_Init(struct Nmea_Handle* handle);

void Nmea_Parse(struct Nmea_Handle* handle, char* msg);
void Nmea_Timepulse(struct Nmea_Handle* handle);

#endif
