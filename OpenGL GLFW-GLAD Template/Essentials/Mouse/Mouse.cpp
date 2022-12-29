#include "Mouse.h"

Mouse::Mouse()
{
}

void Mouse::setPosition(const Vec2d _Position)
{
	GLFWwindow* window = glfwGetCurrentContext();
	Vec2i window_pos;
	glfwGetWindowPos(window, &window_pos.x, &window_pos.y);

	glfwSetCursorPos(window, _Position.x - window_pos.x, _Position.y - window_pos.y);
}

void Mouse::setPosition(const Vec2d _Position, GLFWwindow* window)
{
	glfwSetCursorPos(window, _Position.x, _Position.y);
}

Vec2d Mouse::getPosition()
{
	GLFWwindow* window = glfwGetCurrentContext();
	Vec2i window_pos;
	Vec2d cursor_pos;
	glfwGetWindowPos(window, &window_pos.x, &window_pos.y);
	glfwGetCursorPos(window, &cursor_pos.x, &cursor_pos.y);

	return Vec2d(cursor_pos.x + window_pos.x, cursor_pos.y + window_pos.y);
}

Vec2d Mouse::getPosition(GLFWwindow* _Window)
{
	Vec2d pos;
	glfwGetCursorPos(_Window, &pos.x, &pos.y);
	return pos;
}

bool Mouse::isButtonPressed(int _Button)
{
	return glfwGetMouseButton(glfwGetCurrentContext(), _Button);
}

void Mouse::setInputMode(GLFWwindow* _Window, int _State)
{
	glfwSetInputMode(_Window, GLFW_CURSOR, _State);
}
