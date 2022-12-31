#include "Simulation.h"
#include <time.h>

Simulation::Simulation()
{
	srand(time(NULL));

	initWindow(Vec2i(500,300));

	selectedParticle = 1;
	brushSize = 3;

	//Enable transparent drawings
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	
	particles = nullptr;
	particleSize = 2;
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
			if (particles[x][y]->getData().type != ParticleType::AIR)
			{
				particles[x][y]->update();

				if (particles[x][y]->getData().expired)
					addParticle(x, y, ParticleType::AIR);
			}

			if (particles[x][y]->getData().movement == MovementType::DOWN)
			{
				down(x, y);
			}
			else if (particles[x][y]->getData().movement == MovementType::DOWN_SIDES)
			{
				if (!down(x, y))
				{
					side(x, y);
				}
			}
		}

	//Add particle brush
	if (Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		if (Mouse::getPosition(window->getWindow()).x > 0 &&						//Check x
			Mouse::getPosition(window->getWindow()).x < window->getSize().x &&	//
			Mouse::getPosition(window->getWindow()).y > 0 && 						//Check y
			Mouse::getPosition(window->getWindow()).y < window->getSize().y)	//
		{
			Vec2d mouse = Mouse::getPosition(window->getWindow());

			brush((int)(mouse.x / particleSize), (int)(mouse.y / particleSize), brushSize, (ParticleType)selectedParticle);
		}
	}
	//Remove particle brush
	else if (Mouse::isButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
	{
		if (Mouse::getPosition(window->getWindow()).x > 0 &&						//Check x
			Mouse::getPosition(window->getWindow()).x < window->getSize().x &&	//
			Mouse::getPosition(window->getWindow()).y > 0 && 						//Check y
			Mouse::getPosition(window->getWindow()).y < window->getSize().y)	//
		{
			Vec2d mouse = Mouse::getPosition(window->getWindow());

			eraser((int)(mouse.x / particleSize), (int)(mouse.y / particleSize), brushSize);
		}
	}
}

void Simulation::updateEvents()
{
	while (window->poll_events(event))
	{
		if (event.type == Events::EventType::KEY)
		{
			if (event.keys.action == GLFW_PRESS)
			{
				if (event.keys.key == GLFW_KEY_ESCAPE)
					window->close();

				if (event.keys.key == GLFW_KEY_LEFT && selectedParticle > 1)
					selectedParticle--;
				else if (event.keys.key == GLFW_KEY_RIGHT && selectedParticle < MAX_PARTICLES - 1)
					selectedParticle++;
			}
		}

		if (event.type == Events::EventType::MOUSE_SCROLL)
		{
			if (event.mouseScroll.yoffset > 0 && brushSize < 50)
				brushSize++;
			else if (event.mouseScroll.yoffset < 0 && brushSize > 1)
				brushSize--;
		}

		if (event.type == Events::EventType::MOUSE_BUTTON)
		{
			if (event.mouseButton.action == GLFW_PRESS)
			{
				if (event.mouseButton.button == GLFW_MOUSE_BUTTON_MIDDLE)
				{
					Vec2d mouse = Mouse::getPosition(window->getWindow());
					mouse.x /= particleSize;
					mouse.y /= particleSize;

					Vec2i pos = particles[(int)mouse.x][(int)mouse.y]->getData().position;
					int type = (int)particles[(int)mouse.x][(int)mouse.y]->getData().type;
					Vec4f color = particles[(int)mouse.x][(int)mouse.y]->getData().color;
					int lifetime = particles[(int)mouse.x][(int)mouse.y]->getData().lifetime;
					float weight = particles[(int)mouse.x][(int)mouse.y]->getData().weight;

					std::cout << "Position: " << pos.x << " - " << pos.y << std::endl;
					std::cout << "Type: " << type << std::endl;
					std::cout << "Color: " << color.x << " - " << color.y << " - " << 
						color.z << " - " << color.w << std::endl;
					std::cout << "Lifetime: " << lifetime << std::endl;
					std::cout << "Weight: " << weight << std::endl;

					std::cout << std::endl;
				}
			}
		}
	}
}

void Simulation::render()
{
	window->clear(50,50,50);

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

//True if a particle has been added
//False if not
bool Simulation::addParticle(const int _X, const int _Y, const ParticleType _Type)
{
	if (_X >= 0 && _X < arrSize.x &&
		_Y >= 0 && _Y < arrSize.y)
	{
		if (particles[_X][_Y]->getData().type != _Type)
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
				particles[_X][_Y] = new Stone(Vec2i(_X, _Y), particleSize);
				break;
			case ParticleType::WATER:
				particles[_X][_Y] = new Water(Vec2i(_X, _Y), particleSize);
				break;
			}

			return true;
		}
	}
	return false;
}

void Simulation::deleteParticle(const int _X, const int _Y)
{
	if (_X >= 0 && _X < arrSize.x &&
		_Y >= 0 && _Y < arrSize.y)
	{
		if (particles[_X][_Y] != nullptr)
			delete particles[_X][_Y];

		particles[_X][_Y] = nullptr;
	}
}

void Simulation::brush(const int _Center_X, const int _Center_Y, const int _Brush_Size, ParticleType _Type)
{
	for (int i = 0; i < _Brush_Size; i++)
	{
		for (int k = 0; k < 360; k++)
		{
			if (!addParticle((int)(sin(k) * i + _Center_X), (int)(cos(k) * i + _Center_Y), _Type))
				k += 2;
		}
	}
}

void Simulation::eraser(const int _Center_X, const int _Center_Y, const int _Brush_Size)
{
	brush(_Center_X, _Center_Y, _Brush_Size, ParticleType::AIR);
}

bool Simulation::down(const int _X, const int _Y)
{
	if (_X >= 0 && _X < arrSize.x && 
		_Y < arrSize.y - 1)
	{
		//Down
		if (particles[_X][_Y+1]->getData().type != ParticleType::AIR)
		{
			//Check movable
			if (particles[_X][_Y + 1]->getData().movable)
			{
				//check weight
				if (particles[_X][_Y] > particles[_X][_Y + 1])
				{
					swapParticles(Vec2i(_X, _Y), Vec2i(_X, _Y + 1));
					return true;
				}
			}
		}
		else if (particles[_X][_Y + 1]->getData().movable)
		{
			swapParticles(Vec2i(_X, _Y), Vec2i(_X, _Y + 1));
			return true;
		}

		switch (rand() % 2)
		{
		case 0:
			//Down left
			if (_X > 0)
			{
				if (particles[_X - 1][_Y + 1]->getData().type != ParticleType::AIR)
				{
					//Check movable
					if (particles[_X - 1][_Y + 1]->getData().movable)
					{
						//check weight
						if (particles[_X][_Y] > particles[_X - 1][_Y + 1])
						{
							swapParticles(Vec2i(_X, _Y), Vec2i(_X - 1, _Y + 1));
							return true;
						}
					}
				}
				else if (particles[_X - 1][_Y + 1]->getData().movable)
				{
					swapParticles(Vec2i(_X, _Y), Vec2i(_X - 1, _Y + 1));
					return true;
				}
			}
			break;
		case 1:
			//Down right
			if (_X < arrSize.x - 1)
			{
				if (particles[_X + 1][_Y + 1]->getData().type != ParticleType::AIR)
				{
					//Check movable
					if (particles[_X + 1][_Y + 1]->getData().movable)
					{
						//check weight
						if (particles[_X][_Y] > particles[_X + 1][_Y + 1])
						{
							swapParticles(Vec2i(_X, _Y), Vec2i(_X + 1, _Y + 1));
							return true;
						}
					}
				}
				else if (particles[_X + 1][_Y + 1]->getData().movable)
				{
					swapParticles(Vec2i(_X, _Y), Vec2i(_X + 1, _Y + 1));
					return true;
				}
			}
			break;
		}
	}

	return false;
}

bool Simulation::up(const int _X, const int _Y)
{
	if (_X >= 0 && _X < arrSize.x &&
		_Y < arrSize.y - 1)
	{
		//Up
		if (particles[_X][_Y - 1]->getData().type != ParticleType::AIR)
		{
			//Check movable
			if (particles[_X][_Y - 1]->getData().movable)
			{
				//check weight
				if (particles[_X][_Y] < particles[_X][_Y - 1])
				{
					swapParticles(Vec2i(_X, _Y), Vec2i(_X, _Y - 1));
					return true;
				}
			}
		}
		else if (particles[_X][_Y - 1]->getData().movable)
		{
			swapParticles(Vec2i(_X, _Y), Vec2i(_X, _Y - 1));
			return true;
		}

		switch (rand() % 2)
		{
		case 0:
			//Up left
			if (_X > 0)
			{
				if (particles[_X - 1][_Y - 1]->getData().type != ParticleType::AIR)
				{
					//Check movable
					if (particles[_X - 1][_Y - 1]->getData().movable)
					{
						//check weight
						if (particles[_X][_Y] < particles[_X - 1][_Y - 1])
						{
							swapParticles(Vec2i(_X, _Y), Vec2i(_X - 1, _Y - 1));
							return true;
						}
					}
				}
				else if (particles[_X - 1][_Y - 1]->getData().movable)
				{
					swapParticles(Vec2i(_X, _Y), Vec2i(_X - 1, _Y - 1));
					return true;
				}
			}
			break;
		case 1:
			//Up right
			if (_X < arrSize.x - 1)
			{
				if (particles[_X + 1][_Y - 1]->getData().type != ParticleType::AIR)
				{
					//Check movable
					if (particles[_X + 1][_Y - 1]->getData().movable)
					{
						//check weight
						if (particles[_X][_Y] < particles[_X - 1][_Y - 1])
						{
							swapParticles(Vec2i(_X, _Y), Vec2i(_X - 1, _Y - 1));
							return true;
						}
					}
				}
				else if (particles[_X + 1][_Y + 1]->getData().movable)
				{
					swapParticles(Vec2i(_X, _Y), Vec2i(_X - 1, _Y - 1));
					return true;
				}
			}
			break;
		}
	}

	return false;
}

bool Simulation::side(const int _X, const int _Y)
{
	if (_X > 0 && _X < arrSize.x-1)
	{
		switch (rand() % 2)
		{
		case 0:
			//Check left
			if (particles[_X - 1][_Y]->getData().type != ParticleType::AIR)
			{
				//Check if movable
				if (particles[_X - 1][_Y]->getData().movable)
				{
					swapParticles(Vec2i(_X, _Y), Vec2i(_X - 1, _Y));
					return true;
				}
			}
			else if (particles[_X - 1][_Y]->getData().movable)
			{
				swapParticles(Vec2i(_X, _Y), Vec2i(_X - 1, _Y));
				return true;
			}
			break;
		case 1:
			//Check right
			if (particles[_X + 1][_Y]->getData().type != ParticleType::AIR)
			{
				//Check if movable
				if (particles[_X + 1][_Y]->getData().movable)
				{
					swapParticles(Vec2i(_X, _Y), Vec2i(_X + 1, _Y));
					return true;
				}
			}
			else if (particles[_X + 1][_Y]->getData().movable)
			{
				swapParticles(Vec2i(_X, _Y), Vec2i(_X + 1, _Y));
				return true;
			}
			break;
		}
	}

	return false;
}

void Simulation::swapParticles(const Vec2i _Pos_One, const Vec2i _Pos_Two)
{
	Particle* temp = particles[_Pos_One.x][_Pos_One.y];

	particles[_Pos_One.x][_Pos_One.y] = particles[_Pos_Two.x][_Pos_Two.y];
	particles[_Pos_Two.x][_Pos_Two.y] = temp;

	particles[_Pos_One.x][_Pos_One.y]->setPosition(_Pos_One);
	particles[_Pos_Two.x][_Pos_Two.y]->setPosition(_Pos_Two);
}
