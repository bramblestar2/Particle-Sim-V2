#pragma once
#include "../Particle.h"

class Sand : public Particle
{
public:
	Sand(const Vec2i _Position, const float _Size);
	~Sand();

	void update() override;
	void specialUpdate(Particle*** _Grid, Vec2i arrSize) override;
private:
};

