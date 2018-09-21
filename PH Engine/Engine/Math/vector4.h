#pragma once
#include <ostream>
#include <math.h>
#include "Vector2.h"
#include "Vector3.h"
#define PI 3.141592635
class vec4
{
public:

	//Actual Data
	float x, y, z, w;

	vec4();
	vec4(float X, float Y, float Z, float W) :x(X), y(Y), z(Z), w(W) {}
	vec4(vec3 vec, float scalar);
	vec4(vec2 left, vec2 right);
	vec4(vec2 vec, float left, float right);
	~vec4();
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

	vec4 operator*(const float scalar) const
	{
		///vec1 * 5
		return vec4((x*scalar), (y*scalar), (z*scalar), (w*scalar));
	}
	vec4 operator+(const vec4& right) const
	{
		//vec1 + vec2
		return vec4((x + right.x), (y + right.y), (z + right.z), (w + right.w));
	}
	vec4 operator-(const vec4& right) const
	{
		//vec1 - vec2
		return vec4((x + right.x), (y + right.y), (z + right.z), (w + right.w));
	}

	vec4& operator+=(const vec4& right)
	{
		*this = *this + right;
		return *this;
	}

	vec4& operator-=(const vec4& right)
	{
		*this = *this - right;
		return *this;
	}

	vec4& operator *= (const float scalar)
	{
		*this = *this * scalar;
		return *this;
	}

	friend std::ostream& operator<< (std::ostream& out, const vec4 source)
	{
		//Example: std::cout << vec1 << std::endl
		//output in cmd: (vec1.x,vec1.y,vec1.z)
		return out << "(" << source.x << "," << source.y << "," << source.z << "," << source.w << ")";
	}

	bool operator==(const vec4 right)
	{
		if (x == right.x && y == right.y && z == right.z && w == right.w)
		{
			return true;
		}
		return false;

	}

	bool operator!=(const vec4 right)
	{
		if (x != right.x && y != right.y && z != right.z && w != right.w)
		{
			return true;
		}
		return false;

	}

	bool operator> (const vec4 right)
	{
		if (x > right.x && y > right.y && z > right.z && w > right.w)
		{
			return true;
		}
		return false;
	}

	bool operator< (const vec4 right)
	{
		if (x < right.x && y < right.y && z < right.z && w < right.w)
		{
			return true;
		}
		return false;
	}

	bool operator>= (const vec4 right)
	{
		if (x >= right.x && y >= right.y && z >= right.z && w >= right.w)
		{
			return true;
		}
		return false;
	}

	bool operator<= (const vec4 right)
	{
		if (x <= right.x && y <= right.y && z <= right.z && w <= right.w)
		{
			return true;
		}
		return false;
	}
	//3D Functions
	float Length(vec4 v1);
	vec4 Normalize(vec4 v1);
	float DotProduct(vec4 v1, vec4 v2);
	float ProjLength(vec4 v1, vec4 v2);
	vec4 ProjPoint(vec4 v1, vec4 v2);
	float ProjAngle(vec4 v1, vec4 v2);
	float DistanceBetweenObj(vec4 v1, vec4 v2);
};