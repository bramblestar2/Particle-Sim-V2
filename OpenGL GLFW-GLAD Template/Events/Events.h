#pragma once

#include <string>
#include <iostream>

class Events
{
protected:
	
	struct Key
	{
		int key; //The key thats been pressed
		int scancode; //The id of a key (can differ from platforms)
		int action; //If the key is pressed, released, or held
		int mods;
	};

	struct Character
	{
		int codepoint; //The key thats been pressed
	};

	struct CursorMoved
	{
		double xpos; //X position of mouse
		double ypos; //Y position of mouse
	};

	struct CursorEntered
	{
		int entered; //The mouse has entered or left the window
	};

	struct MouseButton
	{
		int button; //What button was pressed
		int action; //If the button is pressed or released
		int mods;
	};

	struct MouseScroll
	{
		double xoffset;
		double yoffset;
	};

	struct Joystick
	{
		int jid;
		int event;
	};

	struct Drop
	{
		int count; //The count of the files that were dropped
		std::string* paths; //The paths of the dropped files
	};

	//Window events

	//Window size change
	struct SizeChanged
	{
		int width;
		int height;
	};

	//Frame buffer size change
	struct BufferChanged
	{
		int width;
		int height;
	};

	//Content scale change
	struct ScaleChanged
	{
		float xscale;
		int yscale;
	};

	//Window position moved
	struct WindowMoved
	{
		int xpos; 
		int ypos;
	};

	//Window Iconified
	struct Iconified
	{
		int iconified;
	};

	//Window maximized
	struct Maximized
	{
		int maximized;
	};

	//Windows focus is changed
	struct Focused
	{
		int focused;
	};

public:
	enum class EventType
	{
		KEY,
		CHARACTER,
		CURSOR_MOVED,
		CURSOR_ENTERED,
		MOUSE_BUTTON,
		MOUSE_SCROLL,
		JOYSTICK,
		DROP,

		CLOSED,
		SIZE_CHANGED,
		BUFFER_CHANGED,
		SCALE_CHANGED,
		WINDOW_MOVED,
		ICONIFIED,
		MAXIMIZED,
		FOCUSED,
		REFRESH,
	};

	EventType type;

	union
	{
		Key keys;
		Character character;
		CursorMoved cursorMoved;
		CursorEntered cursorEntered;
		MouseButton mouseButton;
		MouseScroll mouseScroll;
		Joystick joystick;
		Drop drop;

		SizeChanged sizeChanged;
		BufferChanged bufferChanged;
		ScaleChanged scaleChanged;
		WindowMoved windowMoved;
		Iconified iconified;
		Maximized maximized;
		Focused focused;
	};
};
