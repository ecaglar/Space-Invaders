#include "System.h"
#include "Assert.h"
#include "Sound.h"
#include <SDL_ttf.h>
#include <string>

SDL_Surface* System::s_screen = 0;

extern void mixaudio(void *unused, Uint8 *stream, int len);

System::System()
{
}

System::~System()
{
	SDL_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}

void
System::init()
{
	ASSERT_RESULT_DECL(const int sdlInitResult, SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO));
	ASSERT_DESCRIPTION(sdlInitResult == 0, "SDL_Init failed: " << SDL_GetError());

	SDL_WM_SetCaption("SimBin Vaders", "SimBin Vaders");

	s_screen = SDL_SetVideoMode(640, 480, 0, SDL_HWSURFACE|SDL_DOUBLEBUF);
	ASSERT_DESCRIPTION(s_screen, "SDL_SetVideoMode failed: " << SDL_GetError());

	SDL_ShowCursor(0);
	
	ASSERT_RESULT_DECL(const int ttfInitResult, TTF_Init());
	ASSERT_DESCRIPTION(ttfInitResult == 0, "TTF_Init failed: " << TTF_GetError());

	SDL_AudioSpec audioSpecs;
	SDL_AudioSpec obtainedSpecs;

	audioSpecs.freq = 22050;
	audioSpecs.format = AUDIO_S16;
	audioSpecs.channels = 2;
	audioSpecs.samples = 512;
	audioSpecs.callback = mixaudio;
	audioSpecs.userdata = 0;

	Sound::init();

	ASSERT_RESULT_DECL(const int sdlOpenAudioResult, SDL_OpenAudio(&audioSpecs, &obtainedSpecs));
	ASSERT_DESCRIPTION(sdlOpenAudioResult == 0, "SDL_OpenAudio failed: " << SDL_GetError());

	SDL_PauseAudio(0);
}

void
System::clear()
{
	ASSERT_RESULT_DECL(const int result, SDL_FillRect(s_screen, 0, SDL_MapRGB(s_screen->format, 100, 100, 255)));
	ASSERT_DESCRIPTION(result == 0, "SDL_FillRect failed: " << SDL_GetError());
}

void
System::flip()
{
	ASSERT_RESULT_DECL(const int result, SDL_Flip(s_screen));
	ASSERT_DESCRIPTION(result == 0, "SDL_Flip failed: " << SDL_GetError());
}

SDL_Surface*
System::screenSurface()
{
	ASSERT_DESCRIPTION(s_screen, "No screen surface exists! Did you forget to call init?");
	return s_screen;
}
