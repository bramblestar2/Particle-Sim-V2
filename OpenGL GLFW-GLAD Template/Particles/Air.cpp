#include "Air.h"
#include <iostream>

Air::Air(const Vec2i _Position, const float _Size) : Particle(_Position, _Size)
{
	Particle::type = ParticleType::AIR;
	Particle::movement = MovementType::NONE;
}

Air::~Air()
{
}

void Air::update()
{
	std::cout << "Air particle is being updated when it shouldn't" << std::endl;
}
