#include "vector4.h"

vec4::vec4()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

vec4::vec4(vec3 vec, float scalar)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = scalar;
}

vec4::vec4(vec2 left, vec2 right)
{
	x = left.x;
	y = left.y;
	z = right.x;
	w = right.y;
}

vec4::vec4(vec2 vec, float left, float right)
{
	x = vec.x;
	y = vec.y;
	z = left;
	w = right;
}
	

vec4::~vec4()
{
}

float vec4::Length(vec4 v1)
{
	return sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
}

vec4 vec4::Normalize(vec4 v1)
{
	return vec4((v1.x / Length(v1)), (v1.x / Length(v1)), (v1.x / Length(v1)), (v1.x / Length(v1)));
}

float vec4::DotProduct(vec4 v1, vec4 v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w));
}

float vec4::ProjLength(vec4 v1, vec4 v2)
{
	return (DotProduct(v1, v2) / Length(v1));
}

vec4 vec4::ProjPoint(vec4 v1, vec4 v2)
{
	return vec4(((DotProduct(v1, v2) / (Length(v1) * Length(v1))) * v1.x)
		, ((DotProduct(v1, v2) / (Length(v1) * Length(v1))) * v1.y)
		, ((DotProduct(v1, v2) / (Length(v1) * Length(v1))) * v1.z)
		, ((DotProduct(v1, v2) / (Length(v1) * Length(v1))) * v2.w));
}

float vec4::ProjAngle(vec4 v1, vec4 v2)
{
	return ((acos(DotProduct(v1, v2) / (Length(v1) * Length(v2)))) *(180 / PI));

}

float vec4::DistanceBetweenObj(vec4 v1, vec4 v2)
{
	return Length(v2 - v1);
}


