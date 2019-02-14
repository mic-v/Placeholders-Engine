#pragma once
#include <ostream>
#include <math.h>
#include "Vector2.h"
#define PI 3.141592635
class vec3
{
public:

	//Actual Data
	float x, y, z;

	//vec3();
	//vec3 vec1 = {x,y,z};
	vec3(float X = 0.0f, float Y = 0.0f, float Z = 0.0f) :x(X), y(Y), z(Z) {}
	vec3(vec2 vec, float scalar);

	~vec3();
	//vec1.set(4,5,6)
	void set(float X, float Y, float Z) { x = X; y = Y; z = Z; }

	/*
	Operators
	*
	+
	-
	<<
	==
	!=
	>
	<
	>=
	<=

*/
	
	vec3 operator*(const float scalar) const
	{
		///vec1 * 5
		return vec3((x*scalar), (y*scalar), (z*scalar));
	}
	vec3 operator+(const vec3 right) const
	{
		//vec1 + vec2
		return vec3((x + right.x), (y + right.y), (z + right.z));
	}

	//friend vec3 operator+(const vec3 left, const vec3 right)
	//{
	//	return vec3((left.x + right.x), (left.y + right.y), (left.z + right.z));
	//}
	vec3 operator-(const vec3 right) const
	{
		//vec1 - vec2
		return vec3((x - right.x), (y - right.y), (z - right.z));
	}

	vec3& operator+=(const vec3& right)
	{
		*this = *this + right;
		return *this;
	}

	vec3& operator-=(const vec3& right)
	{
		*this = *this - right;
		return *this;
	}

	vec3& operator *= (const float scalar)
	{
		*this = *this * scalar;
		return *this;
	}

	friend std::ostream& operator<< (std::ostream& out, const vec3 source)
	{
		//Example: std::cout << vec1 << std::endl
		//output in cmd: (vec1.x,vec1.y,vec1.z)
		return out << "(" << source.x << "," << source.y << "," << source.z << ")";
	}

	bool operator==(const vec3 right)
	{
		if (x == right.x && y == right.y && z == right.z)
		{
			return true;
		}
		return false;

	}

	bool operator!=(const vec3 right)
	{
		if (x != right.x && y != right.y && z != right.z)
		{
			return true;
		}
		return false;

	}

	bool operator> (const vec3 right)
	{
		if (x > right.x && y > right.y && z > right.z)
		{
			return true;
		}
		return false;
	}

	bool operator< (const vec3 right)
	{
		if (x < right.x && y < right.y && z < right.z)
		{
			return true;
		}
		return false;
	}

	bool operator>= (const vec3 right)
	{
		if (x >= right.x && y >= right.y && z >= right.z)
		{
			return true;
		}
		return false;
	}

	bool operator<= (const vec3 right)
	{
		if (x <= right.x && y <= right.y && z <= right.z)
		{
			return true;
		}
		return false;
	}
	//3D Functions
	float Length(vec3 v1);
	float Length();
	static vec3 Normalize(vec3 v1);
	vec3 Normalize();
	float DotProduct(vec3 v1, vec3 v2);
	static float dotProduct2(vec3 v1, vec3 v2);
	float ProjLength(vec3 v1, vec3 v2);
	vec3 ProjPoint(vec3 v1, vec3 v2);
	float ProjAngle(vec3 v1, vec3 v2);
	float DistanceBetweenObj(vec3 v1, vec3 v2);
	vec3 CrossProduct(vec3 v1, vec3 v2);
	static vec3 CrossProduct2(vec3 v1, vec3 v2);















};