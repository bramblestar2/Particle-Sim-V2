#pragma once

#include "../Vec2/Vec2.h"
#include "../Vec3/Vec3.h"
#include "../Vec4/Vec4.h"

class Vertex2D
{
public:
	Vertex2D(const Vec2f _Position = Vec2f(), const Vec4f _Color = Vec4f(),
			 const Vec2f _Texture = Vec2f(), const Vec3f _Normal = Vec3f());

	Vec2f position;
	Vec4f color;
	Vec2f texture;
	Vec3f normal;
};