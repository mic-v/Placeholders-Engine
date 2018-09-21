#pragma once
#include "Vector3.h"
#include <ostream>

#define SIZE 9
class mat33
{
public:
	float mV[9];
	mat33();
	~mat33() {};
	//Text Output
	friend std::ostream& operator<<(std::ostream& out, const mat33 source);
	//Basic Operations
	mat33 operator+(const mat33 rhs) const;
	mat33 operator-(const mat33 rhs) const;
	mat33 operator*(const mat33 rhs) const;
	mat33 operator*(const float scalar) const;
	//Row Manipulators
	void SetRows(vec3 row1, vec3 row2, vec3 row3);
	void GetRows(vec3 row1, vec3 row2, vec3 row3);
	vec3 GetRow(int i);
	//Column Manipulators
	void SetColumns(vec3 col1, vec3 col2, vec3 col3);
	void GetColumns(vec3 col1, vec3 col2, vec3 col3);
	vec3 GetColumn(int i);
	//Manipulators
	mat33 transform(vec3 vec);
	mat33 Inverse();
	mat33 Transpose();
	void Identity();
	float Determinant();
	float Trace();
};


