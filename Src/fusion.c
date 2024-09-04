#include "fusion.h"
#include "algebra.h"

void Fusion_Update(struct Fusion_Handle* handle, struct Vector3f gyro, struct Vector3f accel, struct Vector3f mag) {
	struct Vector4f q = handle->quat;

	// Rate of change of quaternion from gyroscope
	struct Vector4f qDot;
	qDot.x = -q.y * gyro.x - q.z * gyro.y - q.w * gyro.z;
	qDot.y = q.x * gyro.x + q.z * gyro.z - q.w * gyro.y;
	qDot.z = q.x * gyro.y - q.y * gyro.z + q.w * gyro.x;
	qDot.w = q.x * gyro.z + q.y * gyro.y - q.z * gyro.x;
	Algebra_Scale4f(&qDot, 0.5f);

	Algebra_Normalize3f(&accel);
	Algebra_Normalize3f(&mag);

	// Auxiliary variables to avoid repeated arithmetic
	const float _2q0mx = 2.0f * q.x * mag.x;
	const float _2q0my = 2.0f * q.x * mag.y;
	const float _2q0mz = 2.0f * q.x * mag.z;
	const float _2q1mx = 2.0f * q.y * mag.x;
	const float _2q0 = 2.0f * q.x;
	const float _2q1 = 2.0f * q.y;
	const float _2q2 = 2.0f * q.z;
	const float _2q3 = 2.0f * q.w;
	const float _2q0q2 = 2.0f * q.x * q.z;
	const float _2q2q3 = 2.0f * q.z * q.w;
	const float q0q0 = q.x * q.x;
	const float q0q1 = q.x * q.y;
	const float q0q2 = q.x * q.z;
	const float q0q3 = q.x * q.w;
	const float q1q1 = q.y * q.y;
	const float q1q2 = q.y * q.z;
	const float q1q3 = q.y * q.w;
	const float q2q2 = q.z * q.z;
	const float q2q3 = q.z * q.w;
	const float q3q3 = q.w * q.w;

	// Reference direction of Earth's magnetic field
	const float hx = mag.x * q0q0 - _2q0my * q.w + _2q0mz * q.z + mag.x * q1q1 + _2q1 * mag.y * q.z + _2q1 * mag.z * q.w - mag.x * q2q2 - mag.x * q3q3;
	const float hy = _2q0mx * q.w + mag.y * q0q0 - _2q0mz * q.y + _2q1mx * q.z - mag.y * q1q1 + mag.y * q2q2 + _2q2 * mag.z * q.w - mag.y * q3q3;
	const float _2bx = Algebra_Sqrt(hx * hx + hy * hy);
	const float _2bz = -_2q0mx * q.z + _2q0my * q.y + mag.z * q0q0 + _2q1mx * q.w - mag.z * q1q1 + _2q2 * mag.y * q.w - mag.z * q2q2 + mag.z * q3q3;
	const float _4bx = 2.0f * _2bx;
	const float _4bz = 2.0f * _2bz;

	// Gradient decent algorithm corrective step
	struct Vector4f s;
	s.x = -_2q2 * (2.0f * q1q3 - _2q0q2 - accel.x) + _2q1 * (2.0f * q0q1 + _2q2q3 - accel.y) - _2bz * q.z * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mag.x) + (-_2bx * q.w + _2bz * q.y) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - mag.y) + _2bx * q.z * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mag.z);
	s.y = _2q3 * (2.0f * q1q3 - _2q0q2 - accel.x) + _2q0 * (2.0f * q0q1 + _2q2q3 - accel.y) - 4.0f * q.y * (1 - 2.0f * q1q1 - 2.0f * q2q2 - accel.z) + _2bz * q.w * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mag.x) + (_2bx * q.z + _2bz * q.x) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - mag.y) + (_2bx * q.w - _4bz * q.y) * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mag.z);
	s.z = -_2q0 * (2.0f * q1q3 - _2q0q2 - accel.x) + _2q3 * (2.0f * q0q1 + _2q2q3 - accel.y) - 4.0f * q.z * (1 - 2.0f * q1q1 - 2.0f * q2q2 - accel.z) + (-_4bx * q.z - _2bz * q.x) * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mag.x) + (_2bx * q.y + _2bz * q.w) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - mag.y) + (_2bx * q.x - _4bz * q.z) * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mag.z);
	s.w = _2q1 * (2.0f * q1q3 - _2q0q2 - accel.x) + _2q2 * (2.0f * q0q1 + _2q2q3 - accel.y) + (-_4bx * q.w + _2bz * q.y) * (_2bx * (0.5f - q2q2 - q3q3) + _2bz * (q1q3 - q0q2) - mag.x) + (-_2bx * q.x + _2bz * q.z) * (_2bx * (q1q2 - q0q3) + _2bz * (q0q1 + q2q3) - mag.y) + _2bx * q.y * (_2bx * (q0q2 + q1q3) + _2bz * (0.5f - q1q1 - q2q2) - mag.z);
	Algebra_Normalize4f(&s);

	Algebra_Scale4f(&s, handle->beta);
	Algebra_Subtract4f(&qDot, &s);
	Algebra_Scale4f(&qDot, 1.0f / handle->magFreq);
	Algebra_Add4f(&q, &qDot);
	Algebra_Normalize4f(&(handle->quat));
}

void Fusion_UpdateImu(struct Fusion_Handle* handle, struct Vector3f gyro, struct Vector3f accel) {
	struct Vector4f q = handle->quat;

	// Rate of change of quaternion from gyroscope
	struct Vector4f qDot;
	qDot.x = -q.y * gyro.x - q.z * gyro.y - q.w * gyro.z;
	qDot.y = q.x * gyro.x + q.z * gyro.z - q.w * gyro.y;
	qDot.z = q.x * gyro.y - q.y * gyro.z + q.w * gyro.x;
	qDot.w = q.x * gyro.z + q.y * gyro.y - q.z * gyro.x;
	Algebra_Scale4f(&qDot, 0.5f);

	Algebra_Normalize3f(&accel);

	// Auxiliary variables to avoid repeated arithmetic
	const float _2q0 = 2.0f * q.x;
	const float _2q1 = 2.0f * q.y;
	const float _2q2 = 2.0f * q.z;
	const float _2q3 = 2.0f * q.w;
	const float _4q0 = 4.0f * q.x;
	const float _4q1 = 4.0f * q.y;
	const float _4q2 = 4.0f * q.z;
	const float _8q1 = 8.0f * q.y;
	const float _8q2 = 8.0f * q.z;
	const float q0q0 = q.x * q.x;
	const float q1q1 = q.y * q.y;
	const float q2q2 = q.z * q.z;
	const float q3q3 = q.w * q.w;

	// Gradient decent algorithm corrective step
	struct Vector4f s;
	s.x = _4q0 * q2q2 + _2q2 * accel.x + _4q0 * q1q1 - _2q1 * accel.y;
	s.y = _4q1 * q3q3 - _2q3 * accel.x + 4.0f * q0q0 * q.y - _2q0 * accel.y - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 + _4q1 * accel.z;
	s.z = 4.0f * q0q0 * q.z + _2q0 * accel.x + _4q2 * q3q3 - _2q3 * accel.y - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 + _4q2 * accel.z;
	s.w = 4.0f * q1q1 * q.w - _2q1 * accel.x + 4.0f * q2q2 * q.w - _2q2 * accel.y;
	Algebra_Normalize4f(&s);

	Algebra_Scale4f(&s, handle->beta);
	Algebra_Subtract4f(&qDot, &s);
	Algebra_Scale4f(&qDot, 1.0f / handle->imuFreq);
	Algebra_Add4f(&(handle->quat), &qDot);
	Algebra_Normalize4f(&(handle->quat));
}
