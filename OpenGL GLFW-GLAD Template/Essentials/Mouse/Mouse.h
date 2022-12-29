#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

#include "../Vec2/Vec2.h"

class Mouse
{
public:
	Mouse();

	static void setPosition(const Vec2d _Position);
	static void setPosition(const Vec2d _Position, GLFWwindow* window);

	static Vec2d getPosition();
	static Vec2d getPosition(GLFWwindow* _Window);
	static bool isButtonPressed(int _Button);
	static void setInputMode(GLFWwindow* _Window, int _State);
private:

};