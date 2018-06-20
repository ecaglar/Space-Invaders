#ifndef System_h
#define System_h

#include <SDL.h>

class System
{
public:
	System();
	~System();

	static void init();
	static void clear();
	static void flip();

	static SDL_Surface* screenSurface();
private:
	static SDL_Surface* s_screen;
};

#endif
