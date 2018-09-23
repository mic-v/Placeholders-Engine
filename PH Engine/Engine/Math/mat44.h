#pragma once

#include "math.h "

#define SIZE 16



class mat44
{
public:
	union
	{
		float _m[16];
		vec4 row[4];
	};
public:
	mat44();
	mat44(float diagonal);
	~mat44();

	mat44& operator*(const mat44& right);
	friend mat44& operator*(const mat44& left, const mat44& right);
	mat44& operator*=(const mat44& right);

	friend std::ostream& operator<<(std::ostream& out, const mat44& source);

	static mat44 setPosition(vec3 position);
	static mat44 identity();
	static mat44 diagonal(float scalar);
	static mat44 orthographic(float left, float right, float bottom, float top, float near, float far);
	static mat44 perspective(float fov, float aspectRatio, float near, float far);

	static mat44 translation(const vec3& translation);
	static mat44 rotation(float angle, const vec3& axis);
	static mat44 scale(const vec3& scale);
	static mat44 lookAt(vec3 position, const vec3& right, const vec3& up, const vec3& direction);


private:
};
