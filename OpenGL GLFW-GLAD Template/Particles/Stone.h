#pragma once
#include "../Particle.h"

class Stone : public Particle
{
public:
	Stone(const Vec2i _Position, const float _Size);
	~Stone();

	void update() override;
private:

};

