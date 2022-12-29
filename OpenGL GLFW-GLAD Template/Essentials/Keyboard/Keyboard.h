#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <string>

class Keyboard
{
public:
	Keyboard();

	static bool isKeyPressed(int _Key);
	static std::string getKeyName(int _Key, int _Scancode);
	static int getScancode(int _Key);
};