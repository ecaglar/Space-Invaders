#include "Input.h"
#include <string>

int Input::s_mouseMotionX = 0;
int Input::s_mouseMotionY = 0;
int Input::s_mousePositionX = 0;
int Input::s_mousePositionY = 0;
bool Input::s_mouseDown = false;

bool Input::s_keyLeft = false;
bool Input::s_keyRight = false;
bool Input::s_keyUp = false;
bool Input::s_keyDown = false;
bool Input::s_keyFire = false;

Input::Input()
{
}

Input::~Input()
{
}

int
Input::mouseMotionX()
{
	return s_mouseMotionX;
}

int
Input::mouseMotionY()
{
	return s_mouseMotionY;
}

int
Input::mousePositionX()
{
	return s_mousePositionX;
}

int
Input::mousePositionY()
{
	return s_mousePositionY;
}

bool
Input::mouseDown()
{
	return s_mouseDown;
}

bool
Input::keyLeft()
{
	return s_keyLeft;
}

bool
Input::keyRight()
{
	return s_keyRight;
}

bool
Input::keyUp()
{
	return s_keyUp;
}

bool
Input::keyDown()
{
	return s_keyDown;
}

bool
Input::keyFire()
{
	return s_keyFire;
}

void
Input::setMouseMotion(int x, int y)
{
	s_mouseMotionX = x;
	s_mouseMotionY = y;
}

void
Input::setMousePosition(int x, int y)
{
	s_mousePositionX = x;
	s_mousePositionY = y;
}

void
Input::setMouseDown(bool down)
{
	s_mouseDown = down;
}

void
Input::setKeys(bool left, bool right, bool up, bool down, bool fire)
{
	s_keyLeft = left;
	s_keyRight = right;
	s_keyUp = up;
	s_keyDown = down;
	s_keyFire = fire;
}
