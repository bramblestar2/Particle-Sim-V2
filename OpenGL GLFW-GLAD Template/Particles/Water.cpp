#include "Water.h"

Water::Water(const Vec2i _Position, const float _Size) : Particle(_Position, _Size)
{
	Particle::type = ParticleType::WATER;
	Particle::movement = MovementType::DOWN_SIDES;
	Particle::lifetime = 500;
	Particle::destructable = true;
	Particle::movable = true;
	Particle::color = Vec4f(0, 0, 1, 1);
	Particle::weight = 6;
}

Water::~Water()
{
}

void Water::update()
{
}
