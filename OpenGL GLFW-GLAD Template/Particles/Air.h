#pragma once
#include "../Particle.h"

class Air : public Particle
{
public:
	Air(const Vec2i _Position, const float _Size);
	~Air();

	void update() override;
	void specialUpdate(Particle*** _Grid, Vec2i arrSize) override;
private:
};

