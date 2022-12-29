#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include "Drawable.h"
#include "Essentials/Vec4/Vec4.h"
#include "Essentials/Vec2/Vec2.h"
#include "Types.h"

class Particle : public Drawable
{
public:
	Particle(const Vec2i _Position, const float _Size);

	ParticleType getType() const;
	int getLifetime() const;
	bool isMovable() const;

	//Returns true if lifetime is less than or equal to 0
	bool expired() const;

	void render() override;

	//Will return if weight is more than _Right
	bool operator>(const Particle& _Right);
private:
	//Visual
	Vec4f color;
	Vec2i pos;
	float size;

	//Essential
	ParticleType type;
	float weight;
	int lifetime;

	bool movable;
};

