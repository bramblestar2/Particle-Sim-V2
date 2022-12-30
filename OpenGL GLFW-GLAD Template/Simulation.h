#pragma once
#include "Header/Graphics2D.h"
#include "AllParticles.h"

struct Simulation
{
public:
	Simulation();
	~Simulation();

	void run();
	void update();
	void updateEvents();
	void render();
	
private:
	/* Window */
	Window2D* window;
	View v1;
	Events event;

	void initWindow(const Vec2i _Size);


	/* Particles */
	//2d dimensional array
	Particle*** particles;
	Vec2i arrSize;
	float particleSize;

	void setupParticles(const int _Width, const int _Height);
	void clearParticles();
	void addParticle(const int _X, const int _Y, const ParticleType _Type);
	void deleteParticle(const int _X, const int _Y);

};

