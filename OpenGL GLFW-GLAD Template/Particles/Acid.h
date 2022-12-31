#pragma once
#include "../Particle.h"

class Acid : public Particle
{
public:
	Acid(const Vec2i _Position, const float _Size);
	~Acid();

	void update() override;
	void specialUpdate(Particle*** _Grid, Vec2i arrSize) override;
private:

};
