/*

	Matrix format reference
		m[0][0], m[1][0], m[2][0], m[3][0],
		m[0][1], m[1][1], m[2][1], m[3][1],
		m[0][2], m[1][2], m[2][2], m[3][2],
		m[0][3], m[1][3], m[2][3], m[3][3],

	-Asumme all angles are radianized
	-Matrices are column majored
*/


#include "mat4.h"
#include <math.h>
#include <iostream>
mat4::mat4()
{
	m[0][0]= 0; m[1][0] = 0; m[2][0] = 0; m[3][0] = 0;
	m[0][1]= 0; m[1][1] = 0; m[2][1] = 0; m[3][1] = 0;
	m[0][2]= 0; m[1][2] = 0; m[2][2] = 0; m[3][2] = 0;
	m[0][3]= 0; m[1][3] = 0; m[2][3] = 0; m[3][3] = 0;
}

//
// The format for this should be transposed, but
// since it's the diagonal, it doesn't really matter
// e.g. m00 = d; m10 = 0; m20 = 0;...etc but again it's fine
//
mat4::mat4(float d)
{
	m00 = d; m01 = 0; m02 = 0; m03 = 0;
	m10 = 0; m11 = d; m12 = 0; m13 = 0;
	m20 = 0; m21 = 0; m22 = d; m23 = 0;
	m30 = 0; m31 = 0; m32 = 0; m33 = d;
}

//
// It's a diagonal matrix of 1's
//
mat4 mat4::identity()
{
	return mat4(1);
}

//
//
//
//
mat4 mat4::multiply(mat4 x, mat4 y)
{
	mat4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float sum = 0.0f;
			for (int n = 0; n < 4; n++)
			{
				sum += x.m[n][j] * y.m[i][n];
			}
			result.m[i][j] = sum;
		}
	}
	return result;
}
mat4 mat4::translation(vec3 offset)
{
	mat4 result = mat4::identity();
	result.m[3][0] = offset.x;
	result.m[3][1] = offset.y;
	result.m[3][2] = offset.z;
	return result;
}
mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
{
	mat4 result = mat4::identity();
	result.m00 = 2 / (right - left);
	result.m11 = 2 / (top - bottom);
	result.m22 = -2 / (far - near);
	result.m30 = ((right + left) / (right - left));
	result.m31 = ((top + bottom) / (top - bottom));
	result.m32 = ((far + near) / (far - near));

	return result;
}
mat4 mat4::perspective(float fov, float aspectR, float near, float far)
{
	mat4 result;
	result.m[0][0] = 1.0f / (aspectR * tan(fov * 0.5f));
	result.m[1][1] = 1.0f / tan(fov * 0.5f);
	result.m[2][2] = -(far + near) / (far - near);
	result.m[2][3] = -1.0f;
	result.m[3][2] = -(2.0f * far * near) / (far - near);
	return result;
}
mat4 mat4::rotation(float angle, vec3 a)
{
	mat4 result = mat4::identity();

	float c = cos(angle);
	float s = sin(angle);
	float c_ = 1.0f - c;


	result.m[0][0] = a.x * a.x * c_ + c; 
	result.m[0][1] = a.x * a.y * c_ - (a.z * s);
	result.m[0][2] = a.x * a.z * c_ + (a.y * s);

	
	result.m[1][0] = a.x * a.y * c_ + (a.z * s);
	result.m[1][1] = a.y * a.y * c_ + c;
	result.m[1][2] = a.y * a.z * c_ - (a.x * s);

	result.m[2][0] = a.x * a.z * c_ - (a.y * s);
	result.m[2][1] = a.y * a.z * c_ + (a.x * s);
	result.m[2][2] = a.z * a.z * c_ + c;
	return result;
}
mat4 mat4::lookat(vec3 start, vec3 end, vec3 up)
{
	mat4 result = mat4::identity();
	vec3 f = (end - start).Normalize() * -1;
	vec3 r = (vec3::CrossProduct2(up, f)).Normalize();
	vec3 u = vec3::CrossProduct2(f, r);


	result.m[0][0] = r.x; result.m[1][0] = r.y; result.m[2][0] = r.z; result.m[3][0] = vec3::dotProduct2(start, r) * -1.f;
	result.m[0][1] = u.x; result.m[1][1] = u.y; result.m[2][1] = u.z; result.m[3][1] = vec3::dotProduct2(start, u) * -1.f;
	result.m[0][2] = f.x; result.m[1][2] = f.y; result.m[2][2] = f.z; result.m[3][2] = vec3::dotProduct2(start, f) * -1.f;

	return result;

}

