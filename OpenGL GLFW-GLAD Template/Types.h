#pragma once

enum class ParticleType
{
	AIR,
	SAND,
	WATER,
	STONE,
};

namespace p
{
	namespace Air
	{
		const Vec4f color = Vec4f(0, 0, 0, 0);
		const float weight = 0;
		const int lifetime = 0;
		const bool movable = true;
	};
	
	namespace Sand
	{
		const Vec4f color = Vec4f(0.90, 0.45, 0.00, 1);
		const float weight = 0;
		const int lifetime = 0;
		const bool movable = true;
	};

	namespace Water
	{
		const Vec4f color = Vec4f(0.4, 0.5, 1, 0.8);
		const float weight = 0;
		const int lifetime = 0;
		const bool movable = true;
	};

	namespace Stone
	{
		const Vec4f color = Vec4f(0.56, 0.56, 0.56, 1);
		const float weight = 0;
		const int lifetime = 0;
		const bool movable = false;
	};
}