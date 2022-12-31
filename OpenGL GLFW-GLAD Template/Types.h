#pragma once

const int MAX_PARTICLES = 5;


enum class ParticleType
{
	AIR,
	SAND,
	WATER,
	STONE,
	ACID,
};

enum class MovementType
{
	NONE,		//No movement
	DOWN,		//Down left, down, down right
	DOWN_SIDES,	//Left, (DOWN), right
	UP,			//Up left, up, up right
	UP_SIDES,	//Left, (UP), right
};