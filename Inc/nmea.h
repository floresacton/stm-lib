#ifndef INC_NMEA_H_
#define INC_NMEA_H_

#include "stdint.h"

#define NMEA_BUF_SIZE 90
#define NMEA_MIN_LENGTH 5

struct Time {
	uint8_t hour;
	uint8_t min;
	float second;

	uint8_t day;
	uint8_t month;
	uint8_t year;
};

struct Position {
	float latitude;
	char latHem;
	float longitude;
	char lonHem;
	float altitude;
};

void Nmea_Parse(char* data);
void Nmea_Timepulse(void);

float Nmea_Speed(void);

uint8_t Nmea_Satellites(void);

struct Time* Nmea_Time(void);
struct Position* Nmea_Position(void);

#endif
