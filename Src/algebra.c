#include "algebra.h"
#include "math.h"
#include "string.h"

float Algebra_Sqrt(float val) {
	return sqrt(val);
}

float Algebra_InvSqrt(float val) {
	float halfx = 0.5f * val;
	float y = val;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}

void Algebra_Normalize3f(struct Vector3f* vec) {
	const float norm = Algebra_InvSqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	vec->x *= norm;
	vec->y *= norm;
	vec->z *= norm;
}
void Algebra_Scale3f(struct Vector3f* vec, float val) {
	vec->x *= val;
	vec->y *= val;
	vec->z *= val;
}
void Algebra_Add3f(struct Vector3f* vec, struct Vector3f* add) {
	vec->x += add->x;
	vec->y += add->y;
	vec->z += add->z;
}
float Algebra_Dot3f(struct Vector3f* vec1, struct Vector3f* vec2) {
	return vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z;
}
void Algebra_Transform3f(struct Vector3f* vec, struct Transform3f* trans) {
	const struct Vector3f res = {.x = Algebra_Dot3f(vec, &trans->v1), .y = Algebra_Dot3f(vec, &trans->v2), .z = Algebra_Dot3f(vec, &trans->v3)};
	memcpy(vec, &res, sizeof(struct Vector3f));
}

void Algebra_Normalize4f(struct Vector4f* vec) {
	const float norm = Algebra_InvSqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z + vec->w * vec->w);
	vec->x *= norm;
	vec->y *= norm;
	vec->z *= norm;
	vec->w *= norm;
}
void Algebra_Scale4f(struct Vector4f* vec, float val) {
	vec->x *= val;
	vec->y *= val;
	vec->z *= val;
	vec->w *= val;
}
void Algebra_Add4f(struct Vector4f* vec, struct Vector4f* add) {
	vec->x += add->x;
	vec->y += add->y;
	vec->z += add->z;
	vec->w += add->w;
}
void Algebra_Subtract4f(struct Vector4f* vec, struct Vector4f* sub) {
	vec->x -= sub->x;
	vec->y -= sub->y;
	vec->z -= sub->z;
	vec->w -= sub->w;
}
