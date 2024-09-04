#ifndef INC_FUSION_H_
#define INC_FUSION_H_

#include "algebra.h"
#include "stdint.h"

struct Fusion_Handle {
	float imuFreq;
	float magFreq;

	float beta; // algorithm gain
	struct Vector4f quat; // quaternion
};

void Fusion_Update(struct Fusion_Handle* handle, struct Vector3f gyro, struct Vector3f accel, struct Vector3f mag);
void Fusion_UpdateImu(struct Fusion_Handle* handle, struct Vector3f gyro, struct Vector3f accel);

#endif
