#include "View.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

View::View(const Vec2f _Size, const Vec2f _Position)
{
	setPosition(_Position.x, _Position.y);
	setSize(_Size.x, _Size.y);
	setScale(1, 1);
}

View::~View()
{
}

void View::setPosition(const float _X, const float _Y)
{
    m_position = Vec2f(_X, _Y);
	m_updated = true;
}

void View::setSize(const float _X, const float _Y)
{
    m_size = Vec2f(_X, _Y);
	m_updated = true;
}

void View::setScale(const float _X, const float _Y)
{
    m_scale = Vec2f(_X, _Y);
	m_updated = true;
}

Vec2f View::getScale() const
{
    return m_scale;
}

Vec2f View::getPosition() const
{
    return m_position;
}

Vec2f View::getSize() const
{
    return m_size;
}

void View::move(const float _X, const float _Y)
{
    m_position += Vec2f(_X, _Y);
	m_updated = true;
}

void View::scale(const float _X, const float _Y)
{
    m_scale += Vec2f(_X, _Y);
	m_updated = true;
}

void View::update()
{
	if (m_updated)
	{
		glViewport(m_position.x, m_position.y, m_size.x * m_scale.x, m_size.y * m_scale.y);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, m_size.x, m_size.y, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		m_updated = false;
	}
}