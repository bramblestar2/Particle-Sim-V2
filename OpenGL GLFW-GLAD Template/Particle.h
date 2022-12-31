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
	struct Data
	{
		Vec4f color;
		Vec2i position;
		
		MovementType movement;
		ParticleType type;
		float weight;
		int lifetime;
		bool movable, destructable;

		bool expired;
	};

public:
	Particle(const Vec2i _Position, const float _Size);

	Data getData();

	void setPosition(const Vec2i _Position);

	void render() override;
	virtual void update() = 0;

	//Will return if weight is more than _Right
	bool operator>(const Particle& _Right);

	//Will return if weight is less than _Right
	bool operator<(const Particle& _Right);
protected:
	//Returns true if lifetime is less than or equal to 0
	bool expired() const;

	//Visual
	Vec4f color;
	Vec2i pos;
	float size;

	//Essential
	MovementType movement;
	ParticleType type;
	float weight;
	int lifetime;
	bool movable;
	bool destructable;
};

