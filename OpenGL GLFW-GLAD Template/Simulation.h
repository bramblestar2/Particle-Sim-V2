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
	int selectedParticle;
	int brushSize;

	//2d dimensional array
	Particle*** particles;
	Particle*** back_particles; //Not visible
	Vec2i arrSize;
	float particleSize;

	void setupParticles(Particle*** _Grid, const int _Width, const int _Height);
	void clearParticles(Particle*** _Grid);
	bool addParticle(Particle*** _Grid, const int _X, const int _Y, const ParticleType _Type);
	void deleteParticle(Particle*** _Grid, const int _X, const int _Y);

	//Tools
	void brush(const int _Center_X, const int _Center_Y, const int _Brush_Size, ParticleType _Type);
	void eraser(const int _Center_X, const int _Center_Y, const int _Brush_Size);

	//Moving particles

	//Return false when particle cant move
	bool down(const int _X, const int _Y);
	//Return false when particle cant move
	bool up(const int _X, const int _Y);
	//Return false when particle cant move
	bool side(const int _X, const int _Y);

	void swapParticles(const Vec2i _Pos_One, const Vec2i _Pos_Two);
	void moveParticle(const Vec2i _Pos_One, const Vec2i _Pos_Two); 
	void swapGrids(); //Swaps the front and back grid, clearing the front grid first
};

