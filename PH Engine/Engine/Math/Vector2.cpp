#include "Vector2.h"

vec2::vec2()
{
	x = 0.0f;
	y = 0.0f;
}

vec2::~vec2()
{
}

float vec2::Length(vec2 v1)
{
	return sqrt((v1.x * v1.x) + (v1.y * v1.y));
}

vec2 vec2::Normalize(vec2 v1)
{
	return vec2((v1.x / Length(v1)), (v1.y / Length(v1)));
}

float vec2::DotProduct(vec2 v1, vec2 v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y));
}

float vec2::ProjLength(vec2 v1, vec2 v2)
{
	return (DotProduct(v1, v2) / Length(v1));
}

vec2 vec2::ProjPoint(vec2 v1, vec2 v2)
{
	return vec2(((DotProduct(v1, v2) / (Length(v1) * Length(v1))) * v1.x), ((DotProduct(v1, v2) / (Length(v1) * Length(v1))) * v1.y));
}

float vec2::ProjAngle(vec2 v1, vec2 v2)
{
	return (acos((DotProduct(v1, v2) / (Length(v1) * Length(v2)))) *(180 / PI));
}

float vec2::DistanceBetweenObj(vec2 v1, vec2 v2)
{
	return Length(v2 - v1);
}

vec2 vec2::CrossProduct(vec2 v1, vec2 v2)
{
	return vec2((v1.x * v2.y), (v1.y * v2.x));
}