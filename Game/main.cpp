#include "Application.h"
#include "..\3rdParty\System.h"
#include "..\3rdParty\Input.h"
#include <SDL.h>

int
main(int argc, char* argv[])
{
	argc = argc;
	argv = argv;

	System::init();

	Application app;

	SDL_Event event;
	Uint32 oldTicks = SDL_GetTicks();

	bool leftKey = false;
	bool rightKey = false;
	bool upKey = false;
	bool downKey = false;
	bool fireKey = false;	
	bool continueUpdating = true;
	do
 	{
		SDL_Delay(10);
		const Uint32 ticksNow = SDL_GetTicks();
		const float deltaTime = (float) (ticksNow - oldTicks) / 1000.0f;
		oldTicks = ticksNow;
		continueUpdating = app.update(deltaTime);
		if (!continueUpdating)
			break;
		System::clear();
		app.render();
		System::flip();

		Input::setMouseMotion(0, 0);
		Input::setMouseDown(false);

		while (SDL_PollEvent(&event))
		{
	        switch (event.type) 
			{
            case SDL_MOUSEMOTION:
				Input::setMouseMotion(event.motion.xrel, event.motion.yrel);
				Input::setMousePosition(event.motion.x, event.motion.y);
                break;
            case SDL_MOUSEBUTTONDOWN:
				Input::setMouseDown((event.button.button != 0));
                break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
				case SDLK_LEFT:
					leftKey = (event.type == SDL_KEYDOWN);
					break;
				case SDLK_RIGHT:
					rightKey = (event.type == SDL_KEYDOWN);
					break;
				case SDLK_UP:
					upKey = (event.type == SDL_KEYDOWN);
					break;
				case SDLK_DOWN:
					downKey = (event.type == SDL_KEYDOWN);
					break;
				case SDLK_LCTRL:
					fireKey = (event.type == SDL_KEYDOWN);
					break;
				case SDLK_ESCAPE:
					if (event.type == SDL_KEYDOWN)
					{
						continueUpdating = false;
					}
				}
				Input::setKeys(leftKey, rightKey, upKey, downKey, fireKey);
			break;
            case SDL_QUIT:
				continueUpdating = false;
                break;
			}
       }
	} while (continueUpdating);

	return 0;
}
