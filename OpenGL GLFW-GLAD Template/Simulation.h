#pragma once
#include "Header/Graphics2D.h"

struct Simulation
{
public:
	Simulation();
	~Simulation();

	void play();

private:
	Window2D window;
};

