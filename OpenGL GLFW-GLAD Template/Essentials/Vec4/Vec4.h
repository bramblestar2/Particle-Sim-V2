#pragma once

template<typename T>
struct Vec4
{
	Vec4(const T _X = 0, const T _Y = 0, const T _Z = 0, const T _W = 0)
	{
		x = _X;
		y = _Y;
		z = _Z;
		w = _W;
	}
	T x, y, z, w;

	Vec4& operator+=(const Vec4& _Right)
	{
		x += _Right.x;
		y += _Right.y;
		z += _Right.z;
		w += _Right.w;
		return this;
	}
	Vec4& operator-=(const Vec4& _Right)
	{
		x -= _Right.x;
		y -= _Right.y;
		z -= _Right.z;
		w -= _Right.w;
		return this;
	}
	Vec4 operator+(const Vec4& _Right)
	{
		Vec4 temp;
		temp.x = this.x + _Right.x;
		temp.y = this.y + _Right.y;
		temp.z = this.z + _Right.z;
		temp.w = this.w + _Right.w;
		return temp;
	}
	Vec4 operator-(const Vec4& _Right)
	{
		Vec4 temp;
		temp.x = this.x - _Right.x;
		temp.y = this.y - _Right.y;
		temp.z = this.z - _Right.z;
		temp.w = this.w - _Right.w;
		return temp;
	}
};

typedef Vec4<float> Vec4f;
typedef Vec4<double> Vec4d;
typedef Vec4<int> Vec4i;
