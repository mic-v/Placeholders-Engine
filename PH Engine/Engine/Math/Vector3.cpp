#include "Vector3.h"

vec3::vec3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

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

vec3 vec3::Normalize(vec3 v1)
{
	return vec3((v1.x / Length(v1)), (v1.y / Length(v1)),(v1.z/Length(v1)));
}

float vec3::DotProduct(vec3 v1, vec3 v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y)+(v1.z * v2.z));
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
