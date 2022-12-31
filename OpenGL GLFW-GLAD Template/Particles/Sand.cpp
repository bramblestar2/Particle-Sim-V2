#include "Sand.h"

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
	//lifetime--;
}
