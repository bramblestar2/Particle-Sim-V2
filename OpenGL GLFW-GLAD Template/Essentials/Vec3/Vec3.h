#pragma once

template<typename T>
struct Vec3
{
	Vec3(const T _X = 0, const T _Y = 0, const T _Z = 0)
	{
		x = _X;
		y = _Y;
		z = _Z;
	}
	T x, y, z;

	Vec3& operator+=(const Vec3& _Right)
	{
		x += _Right.x;
		y += _Right.y;
		z += _Right.z;
		return this;
	}
	Vec3& operator-=(const Vec3& _Right)
	{
		x -= _Right.x;
		y -= _Right.y;
		z -= _Right.z;
		return this;
	}
	Vec3 operator+(const Vec3& _Right)
	{
		Vec3 temp;
		temp.x = this.x + _Right.x;
		temp.y = this.y + _Right.y;
		temp.z = this.z + _Right.z;
		return temp;
	}
	Vec3 operator-(const Vec3& _Right)
	{
		Vec3 temp;
		temp.x = this.x - _Right.x;
		temp.y = this.y - _Right.y;
		temp.z = this.z - _Right.z;
		return temp;
	}
};

typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;
typedef Vec3<int> Vec3i;

