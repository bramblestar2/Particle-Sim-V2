#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <string>
#include "../View/View.h"
#include "../Events/EventHandler.h"
#include "../Essentials/ContextSettings/ContextSettings.h"

class Window2D
{
public:
	Window2D(const unsigned int _Width, 
			 const unsigned int _Height, 
			 const std::string _Title,
			 const ContextSettings _Settings = ContextSettings());
	Window2D();
	virtual ~Window2D();

	void setSize(const unsigned int _Width, const unsigned int _Height);
	void setTitle(const std::string _Title);
	void setPosition(const int _X, const int _Y);
	void move(const int _X, const int _Y);
	void setIcon(const int _Count, GLFWimage* _Images);
	void setAspectRatio(const int _Numer, const int _Denom);
	void setView(View* _View);

	//Window Attributes
	void setVisibility(const bool _IsVisible);
	void setResizable(const bool _IsResizable);
	void setFloating(const bool _IsFloating);
	void setDecorated(const bool _IsDecorated);
	void setSampling(const int _SamplingCount);

	Vec2i getSize();
	Vec2i getPosition();
	GLFWwindow* getWindow();

	bool isVisible();
	bool isFocused();
	bool isOpen();
	
	void clear(const float _R, const float _G, const float _B, const float _A = 255);
	void clear();
	virtual void display();
	void close();

	bool poll_events(Events& event);

protected:
	GLFWwindow* window;
	View* view;
	EventHandler handler;
};