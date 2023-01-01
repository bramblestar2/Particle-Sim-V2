#include "Sand.h"
#include <iostream>

Sand::Sand(const Vec2i _Position, const float _Size) : Particle(_Position, _Size)
{
	Particle::type = ParticleType::SAND;
	Particle::movement = MovementType::DOWN;
	Particle::lifetime = 5000;
	Particle::destructable = true;
	Particle::movable = true;
	Particle::color = Vec4f(.6, .5, 0, 1);
	Particle::weight = 5;
}

Sand::~Sand()
{
}

void Sand::update()
{
	color.x = lerp(color.x, (rand() % 50 / 50.f) + 0.6f, .1f);
	color.y = lerp(color.y, (rand() % 70 / 70.f) + 0.5f, .1f);

	//lifetime--;
}

void Sand::specialUpdate(Particle*** _Grid, Vec2i arrSize)
{
}
