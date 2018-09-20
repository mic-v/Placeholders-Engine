#pragma once

#include "math.h  "

#define SIZE 16

class mat44
{
public:
	float _m[SIZE];
public:
	mat44();
	mat44(float diagonal);
	~mat44();

	mat44& operator*(const mat44& right);
	mat44& operator*=(const mat44& right);

	friend std::ostream& operator<<(std::ostream& out, const mat44& source);

	static mat44 identity();
	static mat44 orthographic(float left, float right, float bottom, float top, float near, float far);
	static mat44 perspective(float fov, float aspectRatio, float near, float far);

	static mat44 translation(const vec3& translation);
	static mat44 rotation(float angle, const vec3& axis);
	static mat44 scale(const vec3& scale);


private:
};
