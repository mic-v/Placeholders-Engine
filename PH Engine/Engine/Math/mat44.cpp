#include "mat44.h"

mat44::mat44()
{
	for (int i = 0; i < 16; i++)
	{
		_m[i] = 0.0f;
	}
}

mat44::mat44(float diagonal)
{
	for (int i = 0; i < 16; i++)
	{
		_m[i] = 0.0f;
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
	//i = rows, j = columns
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float sum = 0.0f;
			for (int s = 0; s < 4; s++)
			{
				sum += _m[j + s * 4] * right._m[s + i * 4];
			}
			_m[i * 4 + j] = sum;
		}
	}
	return *this;

}

mat44 & mat44::operator*=(const mat44& right)
{
	return *this * right;
}

std::ostream& operator<<(std::ostream & out, const mat44 & source)
{
	return out << "Matrix:\n" << source._m[0] << ", " << source._m[1] << ", " << source._m[2] << ", " << source._m[3] << "\n"
		<< source._m[4] << ", " << source._m[5] << ", " << source._m[6] << ", " << source._m[7] << "\n"
		<< source._m[8] << ", " << source._m[9] << ", " << source._m[10] << ", " << source._m[11] << "\n"
		<< source._m[12] << ", " << source._m[13] << ", " << source._m[14] << ", " << source._m[15];
}

mat44 mat44::identity()
{
	return mat44(1.0f);
}

/*
	@orthographic matrix
	@based on an image online
*/
mat44 mat44::orthographic(float left, float right, float bottom, float top, float near, float far)
{
	mat44 result(1.0f);
	result._m[0] = 2 / (right - left);
	result._m[5] = 2 / (top - bottom);
	result._m[10] = -2 / (far - near);
	result._m[3] = ((right + left) / (right - left));
	result._m[7] = ((top + bottom) / (top - bottom));
	result._m[11] = ((far + near) / (far - near));
	return result;

}

mat44 mat44::perspective(float fov, float aspectRatio, float near, float far)
{
	mat44 result(1.0f);
	result._m[15] = 0.0f;
	result._m[14] = 1.0f;

	result._m[0] = 1 / ((aspectRatio)* tan(fov / 2));
	result._m[5] = 1 / (tan(fov / 2));
	result._m[10] = (-near - far) / (near - far);
	result._m[11] = (2 * far * near) / (near - far);

	return result;
}

mat44 mat44::translation(const vec3 & translation)
{
	return mat44();
}

mat44 mat44::rotation(float angle, const vec3 & axis)
{
	return mat44();
}

mat44 mat44::scale(const vec3 & scale)
{
	return mat44();
}

