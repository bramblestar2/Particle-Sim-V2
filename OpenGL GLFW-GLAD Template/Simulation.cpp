#include "Simulation.h"

Simulation::Simulation()
{
	initWindow(Vec2i(200,200));

	//Enable transparent drawings
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	
	particles = nullptr;
	particleSize = 5;
	setupParticles(window->getSize().x / particleSize, window->getSize().y / particleSize);
}

Simulation::~Simulation()
{
	//Delete window pointer
	delete window;

	clearParticles();
}

void Simulation::run()
{
	while (window->isOpen())
	{
		update();
		updateEvents();
		render();
	}
}

void Simulation::update()
{
	for (int y = arrSize.y-1; y > -1; y--)
		for (int x = 0; x < arrSize.x; x++)
		{
			if (particles[x][y]->getType() != ParticleType::AIR)
				particles[x][y]->update();
		}
}

void Simulation::updateEvents()
{
	while (window->poll_events(event))
	{
		if (event.type == Events::EventType::KEY)
		{
			if (event.keys.key == GLFW_KEY_ESCAPE)
				window->close();
		}

		if (event.type == Events::EventType::MOUSE_BUTTON)
		{
			if (event.mouseButton.action == GLFW_PRESS &&
				event.mouseButton.button == GLFW_MOUSE_BUTTON_LEFT)
			{
				Vec2d mouse = Mouse::getPosition(window->getWindow());

				addParticle((int)(mouse.x / particleSize), (int)(mouse.y / particleSize), ParticleType::SAND);

				//std::cout << (int)(mouse.x / particleSize) << " - " << (int)(mouse.y / particleSize) << std::endl;
			}
			else if (event.mouseButton.action == GLFW_PRESS &&
					 event.mouseButton.button == GLFW_MOUSE_BUTTON_RIGHT)
			{
				Vec2d mouse = Mouse::getPosition(window->getWindow());

				deleteParticle((int)(mouse.x / particleSize), (int)(mouse.y / particleSize));
				addParticle((int)(mouse.x / particleSize), (int)(mouse.y / particleSize), ParticleType::AIR);
			}
		}
	}
}

void Simulation::render()
{
	window->clear();

	for (int x = 0; x < arrSize.x; x++)
		for (int y = 0; y < arrSize.y; y++)
		{
			//if (particles[x][y]->getType() != ParticleType::AIR)
				particles[x][y]->render();
		}

	window->display();
}

void Simulation::initWindow(const Vec2i _Size)
{
	window = new Window2D(_Size.x, _Size.y, "Particle Sandbox", ContextSettings(0, 0, 0, 1, 2));
	window->setView(&v1);
	
	//Setup view
	v1.setSize(_Size.x, _Size.y);
}

void Simulation::setupParticles(const int _Width, const int _Height)
{
	clearParticles();

	arrSize.x = _Width;
	arrSize.y = _Height;

	particles = new Particle**[_Width];

	for (int x = 0; x < _Width; x++)
	{
		particles[x] = new Particle * [_Height];
	}

	for (int x = 0; x < _Width; x++)
		for (int y = 0; y < _Height; y++)
			particles[x][y] = new Air(Vec2i(x, y), particleSize);
}

void Simulation::clearParticles()
{
	//Check if particles is not a nullptr
	if (particles != nullptr)
	{
		for (int x = 0; x < arrSize.x; x++)
		{
			if (particles[x] != nullptr)
			{
				for (int y = 0; y < arrSize.y; y++)
				{
					deleteParticle(x, y);
				}

				delete[] particles[x];
			}
		}

		delete[] particles;
	}
}

void Simulation::addParticle(const int _X, const int _Y, const ParticleType _Type)
{
	deleteParticle(_X, _Y);

	switch (_Type)
	{
	case ParticleType::AIR:
		particles[_X][_Y] = new Air(Vec2i(_X, _Y), particleSize);
		break;
	case ParticleType::SAND:
		particles[_X][_Y] = new Sand(Vec2i(_X, _Y), particleSize);
		break;
	case ParticleType::STONE:
		//particles[_X][_Y] = new Stone(Vec2i(_X, _Y), particleSize);
		break;
	case ParticleType::WATER:
		//particles[_X][_Y] = new Water(Vec2i(_X, _Y), particleSize);
		break;
	}
}

void Simulation::deleteParticle(const int _X, const int _Y)
{
	if (particles[_X][_Y] != nullptr)
		delete particles[_X][_Y];

	particles[_X][_Y] = nullptr;
}
