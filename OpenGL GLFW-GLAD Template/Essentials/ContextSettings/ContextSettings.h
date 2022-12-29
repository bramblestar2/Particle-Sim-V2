#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>

class ContextSettings
{
public:
	ContextSettings(int depthBits = 0, int stencilBits = 0, int antiAliasing = 0, 
					int majorVersion = 0, int minorVersion = 0);

	bool transparent;
	bool decorated;
	bool resizable;
	bool sRGB;
	
	int refreshRate;
	int antiAliasing;
	int depthBits;
	int stencilBits;
	int minorVersion;
	int majorVersion;
};
