#ifndef Input_h
#define Input_h

#include <SDL.h>
#include "System.h"

class Input
{
public:
	Input();
	~Input();

	static int mouseMotionX();
	static int mouseMotionY();

	static int mousePositionX();
	static int mousePositionY();

	static bool mouseDown();

	static bool keyLeft();
	static bool keyRight();
	static bool keyUp();
	static bool keyDown();
	static bool keyFire();

	static void setMouseMotion(int x, int y);
	static void setMousePosition(int x, int y);
	static void setMouseDown(bool down);
	static void setKeys(bool left, bool right, bool up, bool down, bool fire);

private:
	static int s_mouseMotionX;
	static int s_mouseMotionY;
	static int s_mousePositionX;
	static int s_mousePositionY;
	static bool s_mouseDown;

	static bool s_keyLeft;
	static bool s_keyRight;
	static bool s_keyUp;
	static bool s_keyDown;
	static bool s_keyFire;

	friend class System;
};

#endif
