#include "Water.h"
#include <iostream>

Water::Water(const Vec2i _Position, const float _Size) : Particle(_Position, _Size)
{
	Particle::type = ParticleType::WATER;
	Particle::movement = MovementType::DOWN_SIDES;
	Particle::lifetime = 2000;
	Particle::destructable = true;
	Particle::movable = true;
	Particle::color = Vec4f(0, 0, 1, 1);
	Particle::weight = 2;
}

Water::~Water()
{
}

void Water::update()
{
	//lifetime--;
}

void Water::specialUpdate(Particle*** _Grid, Vec2i arrSize)
{
}