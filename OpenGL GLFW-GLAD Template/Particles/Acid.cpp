#include "Acid.h"
#include <iostream>

Acid::Acid(const Vec2i _Position, const float _Size) : Particle(_Position, _Size)
{
	Particle::type = ParticleType::ACID;
	Particle::movement = MovementType::DOWN_SIDES;
	Particle::lifetime = 2000;
	Particle::destructable = true;
	Particle::movable = true;
	Particle::color = Vec4f(0, 1, 0.2, 1);
	Particle::weight = 3;
}

void Acid::update()
{
	color.y = lerp(color.y, (rand() % 76 / 255) + .7, .1f);
	color.z = lerp(color.z, (rand() % 51 / 255), .1f);
}

void Acid::specialUpdate(Particle*** _Grid, Vec2i arrSize)
{
	bool destroyedParticle = false;
	int damageAmount = -50;

	/* Check Up */
	if (pos.y > 0)
	{
		//Up Left
		if (pos.x > 0)
			if (_Grid[pos.x - 1][pos.y - 1]->getData().type != ParticleType::AIR &&
				_Grid[pos.x - 1][pos.y - 1]->getData().type != ParticleType::ACID)
			{
				_Grid[pos.x - 1][pos.y - 1]->addLifetime(damageAmount);
				destroyedParticle = _Grid[pos.x - 1][pos.y - 1]->getData().expired ? true : destroyedParticle;
			}

		//Up
		if (_Grid[pos.x][pos.y - 1]->getData().type != ParticleType::AIR &&
			_Grid[pos.x][pos.y - 1]->getData().type != ParticleType::ACID)
		{
			_Grid[pos.x][pos.y - 1]->addLifetime(damageAmount);
			destroyedParticle = _Grid[pos.x][pos.y - 1]->getData().expired ? true : destroyedParticle;
		}

		//Up Right
		if (pos.x < arrSize.x - 1)
			if (_Grid[pos.x + 1][pos.y - 1]->getData().type != ParticleType::AIR &&
				_Grid[pos.x + 1][pos.y - 1]->getData().type != ParticleType::ACID)
			{
				_Grid[pos.x + 1][pos.y - 1]->addLifetime(damageAmount);
				destroyedParticle = _Grid[pos.x + 1][pos.y - 1]->getData().expired ? true : destroyedParticle;
			}
	}

	/* Check Sides */
	//Left
	if (pos.x > 0)
		if (_Grid[pos.x - 1][pos.y]->getData().type != ParticleType::AIR &&
			_Grid[pos.x - 1][pos.y]->getData().type != ParticleType::ACID)
		{
			_Grid[pos.x - 1][pos.y]->addLifetime(damageAmount);
			destroyedParticle = _Grid[pos.x - 1][pos.y]->getData().expired ? true : destroyedParticle;
		}

	//Right
	if (pos.x < arrSize.x - 1)
		if (_Grid[pos.x + 1][pos.y]->getData().type != ParticleType::AIR &&
			_Grid[pos.x + 1][pos.y]->getData().type != ParticleType::ACID)
		{
			_Grid[pos.x + 1][pos.y]->addLifetime(damageAmount);
			destroyedParticle = _Grid[pos.x + 1][pos.y]->getData().expired ? true : destroyedParticle;
		}
	
	/* Check Down */
	if (pos.y < arrSize.y-1)
	{
		//Down Left
		if (pos.x > 0)
			if (_Grid[pos.x - 1][pos.y + 1]->getData().type != ParticleType::AIR &&
				_Grid[pos.x - 1][pos.y + 1]->getData().type != ParticleType::ACID)
			{
				_Grid[pos.x - 1][pos.y + 1]->addLifetime(damageAmount);
				destroyedParticle = _Grid[pos.x - 1][pos.y + 1]->getData().expired ? true : destroyedParticle;
			}

		//Down
		if (_Grid[pos.x][pos.y + 1]->getData().type != ParticleType::AIR &&
			_Grid[pos.x][pos.y + 1]->getData().type != ParticleType::ACID)
		{
			_Grid[pos.x][pos.y + 1]->addLifetime(damageAmount);
			destroyedParticle = _Grid[pos.x][pos.y + 1]->getData().expired ? true : destroyedParticle;
		}

		//Down Right
		if (pos.x < arrSize.x - 1)
			if (_Grid[pos.x + 1][pos.y + 1]->getData().type != ParticleType::AIR &&
				_Grid[pos.x + 1][pos.y + 1]->getData().type != ParticleType::ACID)
			{
				_Grid[pos.x + 1][pos.y + 1]->addLifetime(damageAmount);
				destroyedParticle = _Grid[pos.x + 1][pos.y + 1]->getData().expired ? true : destroyedParticle;
			}
	}

	if (destroyedParticle)
	{
		lifetime -= 500;
	}
}
