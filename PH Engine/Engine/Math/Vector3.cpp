#include "Vector3.h"

vec3::vec3(vec2 vec, float scalar)
{
	x = vec.x;
	y = vec.y;
	z = scalar;
}

vec3::~vec3()
{
}

float vec3::Length(vec3 v1)
{
	return sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
}

float vec3::Length()
{
	return sqrt((x * x) + (y * y) + (z * z));
}

vec3 vec3::Normalize(vec3 v1)
{
	float length = sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
	return vec3(v1.x / length, v1.y / length, v1.z / length);
	//return vec3((v1.x / Length(v1)), (v1.y / Length(v1)),(v1.z/Length(v1)));
}

vec3 vec3::Normalize()
{
	float length = Length();
	return vec3(x / length, y / length, z / length);
}

float vec3::DotProduct(vec3 v1, vec3 v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y)+(v1.z * v2.z));
}

float vec3::dotProduct2(vec3 v1, vec3 v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

float vec3::ProjLength(vec3 v1, vec3 v2)
{
	return (DotProduct(v1, v2) / Length(v1));
}

vec3 vec3::ProjPoint(vec3 v1, vec3 v2)
{
	return vec3(((DotProduct(v1, v2) / (Length(v1) * Length(v1))) * v1.x)
				 , ((DotProduct(v1, v2) / (Length(v1) * Length(v1))) * v1.y)
				 , ((DotProduct(v1, v2) / (Length(v1) * Length(v1))) * v1.z));
}

float vec3::ProjAngle(vec3 v1, vec3 v2)
{
	return ((acos(DotProduct(v1, v2) / (Length(v1) * Length(v2)))) *(180 / PI));

}

float vec3::DistanceBetweenObj(vec3 v1, vec3 v2)
{
	return Length(v2 - v1);
}

vec3 vec3::CrossProduct(vec3 v1, vec3 v2)
{
	return vec3(((v1.y * v1.z)-(v1.z*v2.y)),((v1.x*v2.z)-(v1.z*v2.x)),((v1.x*v2.y)-(v1.y*v2.x)));
}

vec3 vec3::CrossProduct2(vec3 v1, vec3 v2)
{
	return vec3(((v1.y * v2.z) - (v1.z*v2.y)), ((v1.z*v2.x) - (v1.x*v2.z)), ((v1.x*v2.y) - (v1.y*v2.x)));
}
