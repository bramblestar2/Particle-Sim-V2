#pragma once

const int MAX_PARTICLES = 4;


enum class ParticleType
{
	AIR,
	SAND,
	WATER,
	STONE,
};

enum class MovementType
{
	NONE,		//No movement
	DOWN,		//Down left, down, down right
	DOWN_SIDES,	//Left, (DOWN), right
	UP,			//Up left, up, up right
	UP_SIDES,	//Left, (UP), right
};