#pragma once
#include <ostream>
#include <math.h>
#define PI 3.141592635
class vec2
{
public:

	//Actual Data
	float x, y;

	vec2();
	//vec2 vec1 = {x,y};
	vec2(float X, float Y) :x(X), y(Y) {}

	~vec2();
	//vec1.set(x,y)
	void set(float X, float Y) { x = X; y = Y; }

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
	vec2 operator*(const float scalar)
	{
		//vec1 * 5
		return vec2((x*scalar), (y*scalar));
	}
	vec2 operator+(const vec2 right)
	{
		//vec1 + vec2
		return vec2((x + right.x), (y + right.y));
	}
	vec2 operator-(const vec2 right)
	{
		//vec1 - vec2
		return vec2((x - right.x), (y - right.y));
	}

	vec2& operator+=(const vec2& right)
	{
		*this = *this + right;
		return *this;
	}

	vec2& operator-=(const vec2& right)
	{
		*this = *this - right;
		return *this;
	}

	vec2& operator *= (const float scalar)
	{
		*this = *this * scalar;
		return *this;
	}

	friend std::ostream& operator<< (std::ostream& out ,const vec2 source)
	{
		//Example: std::cout << vec1 << std::endl
		//output in cmd: (x,y)
		return out << "(" << source.x << "," << source.y << ")";
	}

	bool operator==(const vec2 right)
	{
		if (x == right.x && y == right.y)
		{
			return true;
		}
		return false;

	}

	bool operator!=(const vec2 right)
	{
		if (x != right.x && y != right.y)
		{
			return true;
		}
		return false;

	}

	bool operator> (const vec2 right)
	{
		if (x > right.x && y > right.y)
		{
			return true;
		}
		return false;
	}

	bool operator< (const vec2 right)
	{
		if (x < right.x && y < right.y)
		{
			return true;
		}
		return false;
	}

	bool operator>= (const vec2 right)
	{
		if (x >= right.x && y >= right.y)
		{
			return true;
		}
		return false;
	}

	bool operator<= (const vec2 right)
	{
		if (x <= right.x && y <= right.y)
		{
			return true;
		}
		return false;
	}

	//2D Functions
	float Length(vec2 v1);
	vec2 Normalize(vec2 v1);
	float DotProduct(vec2 v1, vec2 v2);
	float ProjLength(vec2 v1, vec2 v2);
	vec2 ProjPoint(vec2 v1, vec2 v2);
	float ProjAngle(vec2 v1, vec2 v2);
	float DistanceBetweenObj(vec2 v1, vec2 v2);
	vec2 CrossProduct(vec2 v1, vec2 v2);
};