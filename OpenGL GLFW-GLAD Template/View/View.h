#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include "../Essentials/Vec2/Vec2.h"

class View
{
public:
	View(const Vec2f _Size = Vec2f(100,100), const Vec2f _Position = Vec2f());
	~View();

	void setPosition(const float _X = 0.f, const float _Y = 0.f);
	void setSize(const float _X = 0.f, const float _Y = 0.f);
	void setScale(const float _X = 0.f, const float _Y = 0.f);

	Vec2f getScale() const;
	Vec2f getPosition() const;
	Vec2f getSize() const;
	
	void move(const float _X = 0.f, const float _Y = 0.f);
	void scale(const float _X = 0.f, const float _Y = 0.f);
	
	void update(); //Updates GLViewport
private:
	Vec2f m_position;
	Vec2f m_size;
	Vec2f m_scale;

	bool m_updated;
};