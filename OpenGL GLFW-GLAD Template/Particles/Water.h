#pragma once
#include "../Particle.h"

class Water : public Particle
{
public:
	Water(const Vec2i _Position, const float _Size);
	~Water();

	void update() override;
	void specialUpdate(Particle*** _Grid, Vec2i arrSize) override;
private:

};
