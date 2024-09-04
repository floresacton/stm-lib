#ifndef INC_ALGEBRA_H_
#define INC_ALGEBRA_H_

struct Vector3f {
	float x;
	float y;
	float z;
};

struct Vector4f {
	float x;
	float y;
	float z;
	float w;
};

struct Transform3f {
	struct Vector3f v1;
	struct Vector3f v2;
	struct Vector3f v3;
};

float Algebra_Sqrt(float val);
float Algebra_InvSqrt(float val);

void Algebra_Normalize3f(struct Vector3f* vec);
void Algebra_Scale3f(struct Vector3f* vec, float val);
void Algebra_Add3f(struct Vector3f* vec, struct Vector3f* add);
float Algebra_Dot3f(struct Vector3f* vec1, struct Vector3f* vec2);
void Algebra_Transform3f(struct Vector3f* vec, struct Transform3f* trans);

void Algebra_Normalize4f(struct Vector4f* vec);
void Algebra_Scale4f(struct Vector4f* vec, float val);
void Algebra_Add4f(struct Vector4f* vec, struct Vector4f* add);
void Algebra_Subtract4f(struct Vector4f* vec, struct Vector4f* sub);

#endif
