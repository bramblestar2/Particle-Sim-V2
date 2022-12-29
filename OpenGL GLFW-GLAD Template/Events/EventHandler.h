#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <vector>
#include <string>
#include "Events.h"

//REWORKING EVENTS
//AND EVENTHANDLER
//When this is finished, it will be renamed
//EventHandler
class EventHandler
{
public:
	~EventHandler()
	{
		if (topEvent.type == Events::EventType::DROP)
			if (topEvent.drop.count != 0)
				delete[] topEvent.drop.paths;

		for (int i = 0; i < eventList.size(); i++)
			if (eventList.at(i).type == Events::EventType::DROP)
			{
				delete[] eventList.at(i).drop.paths;
			}
	}

	void pop_event()
	{
		if (!isEmpty())
		{
			if (topEvent.type == Events::EventType::DROP)
				if (topEvent.drop.count != 0)
					delete[] topEvent.drop.paths;

			topEvent = eventList.at(eventList.size() - 1);
			eventList.pop_back();
		}
	}
	Events current_event() const;
	int event_count() const;
	bool isEmpty() const;
	bool isSetup() const;
	void setup_events(GLFWwindow* window);

private:
	bool setup = false;
	static std::vector<Events> eventList;
	Events topEvent = Events();

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void character_callback(GLFWwindow* window, unsigned int codepoint);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void cursor_enter_callback(GLFWwindow* window, int entered);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void joystick_callback(int jid, int event);
	static void drop_callback(GLFWwindow* window, int count, const char** paths);

	//Window callbacks
	static void window_close_callback(GLFWwindow* window);
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void window_content_scale_callback(GLFWwindow* window, float xscale, float yscale);
	static void window_pos_callback(GLFWwindow* window, int xpos, int ypos);
	static void window_iconify_callback(GLFWwindow* window, int iconified);
	static void window_maximize_callback(GLFWwindow* window, int maximized);
	static void window_focus_callback(GLFWwindow* window, int focused);
	static void window_refresh_callback(GLFWwindow* window);
};