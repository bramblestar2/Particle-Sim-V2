#pragma once

template<typename T>
struct Vec2
{
	Vec2(const T _X = 0, const T _Y = 0)
	{
		x = _X;
		y = _Y;
	}
	T x, y;

	Vec2& operator+=(const Vec2& _Right)
	{
		x += _Right.x;
		y += _Right.y;
		return *this;
	}
	Vec2& operator-=(const Vec2& _Right)
	{
		x -= _Right.x;
		y -= _Right.y;
		return *this;
	}
	Vec2 operator+(const Vec2& _Right)
	{
		Vec2 temp;
		temp.x = this.x + _Right.x;
		temp.y = this.y + _Right.y;
		return temp;
	}
	Vec2 operator-(const Vec2& _Right)
	{
		Vec2 temp;
		temp.x = this.x - _Right.x;
		temp.y = this.y - _Right.y;
		return temp;
	}
};

typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;
typedef Vec2<int> Vec2i;
