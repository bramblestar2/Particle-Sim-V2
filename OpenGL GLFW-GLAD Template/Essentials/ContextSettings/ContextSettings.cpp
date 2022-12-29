#include "ContextSettings.h"

ContextSettings::ContextSettings(int depthBits, int stencilBits, int antiAliasing, int majorVersion, int minorVersion)
{
	this->transparent = false;
	this->decorated = true;
	this->resizable = true;
	this->sRGB = false;

	this->refreshRate = 0;
	this->antiAliasing = antiAliasing;
	this->depthBits = depthBits;
	this->stencilBits = stencilBits;
	this->minorVersion = minorVersion;
	this->majorVersion = majorVersion;
}