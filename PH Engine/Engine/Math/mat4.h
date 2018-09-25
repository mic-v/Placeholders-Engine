/*
	Mat4 v1.0
	Using column-major matrices, like GLSL/OpenGL
	m[i][j] where i is column and j is row
	float m[4][4] = {
		m[0][0], m[1][0], m[2][0], m[3][0], 
		m[0][1], m[1][1], m[2][1], m[3][1],
		m[0][2], m[1][2], m[2][2], m[3][2],
		m[0][3], m[1][3], m[2][3], m[3][3],
	}

	/----------------------------------------------/
		Version 1.0 - Michael Victorino
	/----------------------------------------------/
	Adding only what we require for the camera to work as of right now
	Matrix Multiplacation
	Matrix Rotation
	Projection
	Orthographic
	LookAt

	
*/

#pragma once
#define PI 3.14159265358979323846
#include "Vector3.h"

class mat4
{
public:

	union{
		float m[4][4];
		struct {
			float m00, m01, m02, m03;
			float m10, m11, m12, m13;
			float m20, m21, m22, m23;
			float m30, m31, m32, m33;
		};
	};

	mat4();
	mat4(float d);
	static mat4 identity();
	static mat4 multiply(mat4 x, mat4 y);
	static mat4 translation(vec3 offset);

	static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
	static mat4 perspective(float fov, float aspectR, float near, float far);
	static mat4 rotation(float angle, vec3 a);
	static mat4 lookat(vec3 start, vec3 end, vec3 up);

private:

};
