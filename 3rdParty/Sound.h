#ifndef Sound_h
#define Sound_h

#include <SDL.h>
#include <string>

class Sound
{
public:
	Sound();
	~Sound();

	void loadWav(const std::string& fileName);

	void play() const;
private:
	Sound(const Sound&);
	Sound& operator=(const Sound&);
	
	static void init();

	friend class System;
	SDL_AudioCVT m_audioCvt;
};

#endif
