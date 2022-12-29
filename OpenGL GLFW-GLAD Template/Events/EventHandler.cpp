#include "EventHandler.h"

std::vector<Events> EventHandler::eventList;

Events EventHandler::current_event() const
{
	return topEvent;
}

int EventHandler::event_count() const
{
	return eventList.size();
}

bool EventHandler::isEmpty() const
{
	return eventList.empty();
}

bool EventHandler::isSetup() const
{
	return setup;
}

void EventHandler::setup_events(GLFWwindow* window)
{
	glfwSetKeyCallback(window, key_callback);
	glfwSetCharCallback(window, character_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetCursorEnterCallback(window, cursor_enter_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetJoystickCallback(joystick_callback);
	glfwSetDropCallback(window, drop_callback);

	glfwSetWindowCloseCallback(window, window_close_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetWindowContentScaleCallback(window, window_content_scale_callback);
	glfwSetWindowPosCallback(window, window_pos_callback);
	glfwSetWindowIconifyCallback(window, window_iconify_callback);
	glfwSetWindowMaximizeCallback(window, window_maximize_callback);
	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowRefreshCallback(window, window_refresh_callback);

	setup = true;
}

void EventHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Events temp;
	temp.keys.key = key;
	temp.keys.scancode = scancode;
	temp.keys.action = action;
	temp.keys.mods = mods;
	temp.type = Events::EventType::KEY;
	eventList.push_back(temp);
}

void EventHandler::character_callback(GLFWwindow* window, unsigned int codepoint)
{
	Events temp;
	temp.character.codepoint = codepoint;
	temp.type = Events::EventType::CHARACTER;
	eventList.push_back(temp);
}

void EventHandler::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Events temp;
	temp.cursorMoved.xpos = xpos;
	temp.cursorMoved.ypos = ypos;
	temp.type = Events::EventType::CURSOR_MOVED;
	eventList.push_back(temp);
}

void EventHandler::cursor_enter_callback(GLFWwindow* window, int entered)
{
	Events temp;
	temp.cursorEntered.entered = entered;
	temp.type = Events::EventType::CURSOR_ENTERED;
	eventList.push_back(temp);
}

void EventHandler::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Events temp;
	temp.mouseButton.button = button;
	temp.mouseButton.action = action;
	temp.mouseButton.mods = mods;
	temp.type = Events::EventType::MOUSE_BUTTON;
	eventList.push_back(temp);
}

void EventHandler::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Events temp;
	temp.mouseScroll.xoffset = xoffset;
	temp.mouseScroll.yoffset = yoffset;
	temp.type = Events::EventType::MOUSE_SCROLL;
	eventList.push_back(temp);
}

void EventHandler::joystick_callback(int jid, int event)
{
	Events temp;
	temp.joystick.jid = jid;
	temp.joystick.event = event;
	temp.type = Events::EventType::JOYSTICK;
	eventList.push_back(temp);
}

void EventHandler::drop_callback(GLFWwindow* window, int count, const char** paths)
{
	Events temp;
	temp.drop.count = count;
	
	temp.drop.paths = count != 0 ? new std::string[count] : nullptr;
	for (int i = 0; i < count; i++)
		temp.drop.paths[i] = paths[i];
	
	temp.type = Events::EventType::DROP;
	eventList.push_back(temp);
}

//Window callbacks

void EventHandler::window_close_callback(GLFWwindow* window)
{
	Events temp;
	temp.type = Events::EventType::CLOSED;
	eventList.push_back(temp);
}

void EventHandler::window_size_callback(GLFWwindow* window, int width, int height)
{
	Events temp;
	temp.sizeChanged.width = width;
	temp.sizeChanged.height = height;
	temp.type = Events::EventType::SIZE_CHANGED;
	eventList.push_back(temp);
}

void EventHandler::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	Events temp;
	temp.bufferChanged.width = width;
	temp.bufferChanged.height = height;
	temp.type = Events::EventType::BUFFER_CHANGED;
	eventList.push_back(temp);
}

void EventHandler::window_content_scale_callback(GLFWwindow* window, float xscale, float yscale)
{
	Events temp;
	temp.scaleChanged.xscale = xscale;
	temp.scaleChanged.yscale = yscale;
	temp.type = Events::EventType::SCALE_CHANGED;
	eventList.push_back(temp);
}

void EventHandler::window_pos_callback(GLFWwindow* window, int xpos, int ypos)
{
	Events temp;
	temp.windowMoved.xpos = xpos;
	temp.windowMoved.ypos = ypos;
	temp.type = Events::EventType::WINDOW_MOVED;
	eventList.push_back(temp);
}

void EventHandler::window_iconify_callback(GLFWwindow* window, int iconified)
{
	Events temp;
	temp.iconified.iconified = iconified;
	temp.type = Events::EventType::ICONIFIED;
	eventList.push_back(temp);
}

void EventHandler::window_maximize_callback(GLFWwindow* window, int maximized)
{
	Events temp;
	temp.maximized.maximized = maximized;
	temp.type = Events::EventType::MAXIMIZED;
	eventList.push_back(temp);
}

void EventHandler::window_focus_callback(GLFWwindow* window, int focused)
{
	Events temp;
	temp.focused.focused = focused;
	temp.type = Events::EventType::FOCUSED;
	eventList.push_back(temp);
}

void EventHandler::window_refresh_callback(GLFWwindow* window)
{
	Events temp;
	temp.type = Events::EventType::REFRESH;
	eventList.push_back(temp);
}
