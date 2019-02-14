#include "Matrix33.h"

std::ostream & operator<<(std::ostream & out, const mat33 source)
{
	//Row
	for (int i = 0; i < 3; i++)
	{
		out << "| ";
		//Column
		for (int j = 0; j < 3; j++)
		{
			out << source.mV[j * 3 + i] << ' ';
		}
		out << '|' << "\n";
	}
	return out;
}

mat33::mat33()
{
	for (int i = 0; i < 9; i++)
	{
		mV[i] = 0.0f;
	}
}

mat33 mat33::operator+(const mat33 rhs) const
{
	mat33 result;
	for (int i = 0; i < 9; i++)
	{
		result.mV[i] = mV[i] + rhs.mV[i];
	}
	return result;
}

mat33 mat33::operator-(const mat33 rhs) const
{
	mat33 result;
	for (int i = 0; i < 9; i++)
	{
		result.mV[i] = mV[i] - rhs.mV[i];
	}
	return result;
}

mat33 mat33::operator*(const mat33 rhs) const
{
	mat33 result;
	
	result.mV[0] = mV[0] * rhs.mV[0] + mV[3] * rhs.mV[1] + mV[6] * rhs.mV[2];	
	result.mV[1] = mV[1] * rhs.mV[0] + mV[4] * rhs.mV[1] + mV[7] * rhs.mV[2];	
	result.mV[2] = mV[2] * rhs.mV[0] + mV[5] * rhs.mV[1] + mV[8] * rhs.mV[2];

	result.mV[3] = mV[0] * rhs.mV[3] + mV[3] * rhs.mV[4] + mV[6] * rhs.mV[5];
	result.mV[4] = mV[1] * rhs.mV[3] + mV[4] * rhs.mV[4] + mV[7] * rhs.mV[5];
	result.mV[5] = mV[2] * rhs.mV[3] + mV[5] * rhs.mV[4] + mV[8] * rhs.mV[5];

	result.mV[6] = mV[0] * rhs.mV[6] + mV[3] * rhs.mV[7] + mV[6] * rhs.mV[8];
	result.mV[7] = mV[1] * rhs.mV[6] + mV[4] * rhs.mV[7] + mV[7] * rhs.mV[8];
	result.mV[8] = mV[2] * rhs.mV[6] + mV[5] * rhs.mV[7] + mV[8] * rhs.mV[8];

	return result;
}

mat33 mat33::operator*(const float scalar) const
{
	mat33 result;
	for (int i = 0; i < 9; i++)
	{
		result.mV[i] = mV[i] * scalar;
	}
	return result;
}

void mat33::SetRows(vec3 row1, vec3 row2, vec3 row3)
{
	mV[0] = row1.x; mV[1] = row2.x; mV[2] = row3.x;
	mV[3] = row1.y; mV[4] = row2.y; mV[5] = row3.y;
	mV[6] = row1.z; mV[7] = row2.z; mV[8] = row3.z;
}

void mat33::GetRows(vec3 row1, vec3 row2, vec3 row3)
{
}

vec3 mat33::GetRow(int i)
{
	return vec3();
}

void mat33::SetColumns(vec3 col1, vec3 col2, vec3 col3)
{
}

void mat33::GetColumns(vec3 col1, vec3 col2, vec3 col3)
{
}

vec3 mat33::GetColumn(int i)
{
	return vec3();
}

mat33 mat33::transform(vec3 vec)
{
	return *this;	
}

mat33 mat33::Inverse()
{
	return mat33();
}

mat33 mat33::Transpose()
{
	float temp = mV[1];
	mV[1] = mV[3];
	mV[3] = temp;

	temp = mV[2];
	mV[2] = mV[6];
	mV[6] = temp;

	temp = mV[5];
	mV[5] = mV[7];
	mV[7] = temp;
	return *this;
}

void mat33::Identity()
{
	mV[0] = 1.0f;
	mV[1] = 0;
	mV[2] = 0;
	mV[3] = 0;
	mV[4] = 1.0f;
	mV[5] = 0;
	mV[6] = 0;
	mV[7] = 0;
	mV[8] = 1.0f;
}

float mat33::Determinant()
{
	return mV[0] * (mV[4] * mV[8] - mV[5] * mV[7])
		 + mV[3] * (mV[2] * mV[7] - mV[1] * mV[8])
		 + mV[6] * (mV[1] * mV[5] - mV[2] * mV[4]);
}

float mat33::Trace()
{
	return mV[0] + mV[4] + mV[8];
}
