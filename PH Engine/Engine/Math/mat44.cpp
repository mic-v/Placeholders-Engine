#include "mat44.h"
#include <iostream>


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
				sum += _m[s + i * 4] * right._m[j + s * 4];
			}
			_m[j + i * 4] = sum;
		}
	}
	return *this;

}


mat44& mat44::operator*=(const mat44& right)
{
	return *this * right;
}

mat44 & operator*(const mat44 & left, const mat44 & right)
{
	mat44 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float sum = 0.0f;
			for (int s = 0; s < 4; s++)
			{
				sum += left._m[i + s * 4] * right._m[s + j * 4];
			}
			result._m[j + i * 4] = sum;
		}
	}
	return result;
}

std::ostream& operator<<(std::ostream & out, const mat44 & source)
{
	return out << "Matrix:\n" << source._m[0] << ", " << source._m[1] << ", " << source._m[2] << ", " << source._m[3] << "\n"
		<< source._m[4] << ", " << source._m[5] << ", " << source._m[6] << ", " << source._m[7] << "\n"
		<< source._m[8] << ", " << source._m[9] << ", " << source._m[10] << ", " << source._m[11] << "\n"
		<< source._m[12] << ", " << source._m[13] << ", " << source._m[14] << ", " << source._m[15];
}

mat44 mat44::setPosition(vec3 position)
{
	mat44 result = mat44::identity();
	result._m[3] = -(position.x);
	result._m[7] = -(position.y);
	result._m[11] = -(position.z);

	return result;
}

mat44 mat44::identity()
{
	return mat44(1.0f);
}

mat44 mat44::diagonal(float scalar)
{
	mat44 result = mat44::identity();
	result._m[0] = scalar;
	result._m[5] = scalar;
	result._m[10] = scalar;
	result._m[15] = scalar;
	return result;
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
	result._m[12] = ((right + left) / (right - left));
	result._m[13] = ((top + bottom) / (top - bottom));
	result._m[14] = ((far + near) / (far - near));
	return result;

}

mat44 mat44::perspective(float fov, float aspectRatio, float near, float far)
{
	mat44 result(1.0f);
	result._m[15] = 0.0f;

	result._m[0] = 1.0f / (aspectRatio * tan(toRad(fov * 0.5f)));
	result._m[5] = 1.0f / tan(toRad(fov * 0.5f));
	//result._m[0] = result._m[5] / aspectRatio;
	//result._m[5] = 1.0f / (tan(toRad(fov / 2)));
	result._m[10] = (near + far) / (near - far);
	result._m[14] = -1.0f;
	result._m[11] = (2.0f * near * far) / (near - far);

	return result;
}

mat44 mat44::translation(const vec3 & translation)
{
	mat44 result(1.0f);

	result._m[3] = translation.x;
	result._m[7] = translation.y;
	result._m[11] = translation.z;
	
	return result;
}

mat44 mat44::rotation(const mat44& rotate,float angle, const vec3 & axis)
{
	mat44 result(1.0f);
	float rotation = toRad(angle);
	float c = cos(rotation);
	float s = sin(rotation);
	float _c = 1.0f - c;

	result._m[0] = axis.x * axis.x * _c + c;
	result._m[1] = axis.x * axis.y * _c - (axis.z * s);
	result._m[2] = axis.x * axis.z * _c + (axis.y * s);
	
	result._m[4] = axis.x * axis.y * _c + (axis.z * s);
	result._m[5] = axis.y * axis.y * _c + c;
	result._m[6] = axis.y * axis.z * _c - (axis.x * s);

	result._m[8] = axis.x * axis.z * _c - (axis.y * s);
	result._m[9] = axis.y * axis.z * _c + (axis.x * s);
	result._m[10] = axis.z * axis.z * _c + c;

	return (result * rotate);

}

mat44 mat44::scale(const vec3 & scale)
{
	mat44 result(1.0f);

	result._m[0] = scale.x;
	result._m[5] = scale.y;
	result._m[10] = scale.z;

	return result;
}

mat44 mat44::lookAt(vec3 position,const vec3 & right, const vec3 & up, const vec3 & direction)
{
	mat44 pos = mat44::setPosition(position);
	mat44 camera = mat44::identity();
	vec3 f = (direction - position);
	f = f.Normalize(f);
	camera._m[0] = right.x; camera._m[4] = right.y; camera._m[8] = right.z;
	camera._m[1] = up.x; camera._m[5] = up.y; camera._m[9] = up.z;
	camera._m[2] = f.x; camera._m[6] = f.y; camera._m[10] = f.z;
	mat44 result = pos * camera;
	return result;

}

/*


*/

mat44 mat44::lookAt2(vec3 position, vec3 target, vec3 up)
{
	//std::cout << position.x << std::endl;
	//std::cout << position.y << std::endl;
	//std::cout << position.z << std::endl;
	//std::cout << target.x << std::endl;
	//std::cout << target.y << std::endl;
	//std::cout << target.z << std::endl;
	//std::cout << f.x << std::endl;
	//std::cout << f.y << std::endl;
	//std::cout << f.z << std::endl;
	vec3 f = (target - position).Normalize();
	vec3 r = (vec3::CrossProduct2(f, up.Normalize()));
	vec3 u = vec3::CrossProduct2(r, f);
	mat44 pos = mat44::setPosition(position);
	//std::cout << f << std::endl;
	//std::cout << r << std::endl;
	//std::cout << u << std::endl;
	mat44 camera = mat44::identity();
	camera._m[0] = r.x; camera._m[4] = r.y; camera._m[8] = r.z;
	camera._m[1] = u.x; camera._m[5] = u.y; camera._m[9] = u.z;
	camera._m[2] = f.x; camera._m[6] = f.y; camera._m[10] = f.z;
	//std::cout << "Pos" << std::endl;
	//std::cout << pos << std::endl;
	//std::cout << "Camera" << std::endl;
	//std::cout << camera << std::endl;
	mat44 result = pos * camera;
	return result;
}

