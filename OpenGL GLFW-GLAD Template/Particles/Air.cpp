#include "Air.h"
#include <iostream>

Air::Air(const Vec2i _Position, const float _Size) : Particle(_Position, _Size)
{
	Particle::color = Vec4f(0, 0, 0, 0);
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

void Air::specialUpdate(Particle*** _Grid, Vec2i arrSize)
{
}
