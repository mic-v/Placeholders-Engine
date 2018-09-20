#pragma once

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
	mat44& operator*=(float scalar);

private:
};
