#include "Vertex2D.h"

Vertex2D::Vertex2D(const Vec2f _Position, const Vec4f _Color, const Vec2f _Texture, const Vec3f _Normal)
{
	position = _Position;
	color = _Color;
	texture = _Texture;
	normal = _Normal;
}
