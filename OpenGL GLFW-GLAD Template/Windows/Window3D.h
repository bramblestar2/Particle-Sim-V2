#pragma once

#include "Window2D.h"
#include "../Camera/Camera.h"

class Window3D : public Window2D
{
public:
	Window3D(const unsigned int _Width,
		const unsigned int _Height,
		const std::string _Title,
		const ContextSettings _Settings = ContextSettings(24, 8));
	Window3D();
	~Window3D();

	void setView(View* _View) = delete;
	void setCamera(Camera* _Camera);
	void display() override;
private:
	Camera* camera;
};