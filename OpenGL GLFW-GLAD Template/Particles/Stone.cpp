#include "Stone.h"

Stone::Stone(const Vec2i _Position, const float _Size) : Particle(_Position, _Size)
{
	Particle::type = ParticleType::WATER;
	Particle::movement = MovementType::NONE;
	Particle::lifetime = 10000;
	Particle::destructable = true;
	Particle::movable = false;
	Particle::color = Vec4f(.25, .25, .25, 1);
	Particle::weight = 10;
}

Stone::~Stone()
{
}

void Stone::update()
{
	lifetime--;
}
