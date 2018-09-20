#include "mat44.h"

mat44::mat44()
{

}

mat44::mat44(float diagonal)
{
	for (int i = 0; i < SIZE; i++)
	{
		_m[i] = 0;
	}
	_m[0] = diagonal;
	_m[5] = diagonal;
	_m[10] = diagonal;
	_m[15] = diagonal;
}

mat44::~mat44()
{
}

mat44& mat44::operator*(const mat44 & right)
{
	// TODO: insert return statement here
	for (int i = 0; i < 16; i++)
	{
		
	}
	return *this;
}
