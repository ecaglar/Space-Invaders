#pragma once
#include <string>
#include <map>

#include "IManager.h"
#include "Singleton.h"
#include "Sound.h"

/************************************************************************/
/*Handles sound related functionality.Provides a interface to entire game logic.
Loads all the sounds and in game, you can play any sound with its name with just
one line of code.

/************************************************************************/

class SoundManager :
	public IManager, public Singleton<SoundManager>
{
public:
	void tick() ;
	void  clean() ;
	//loads all sounds
	void init();
	//play any sound with its name
	void play_sound(std::string);


private:
	SoundManager(void){};
	SoundManager(SoundManager& const);
	void operator= (SoundManager& const);
	friend class Singleton<SoundManager>;

	//maps the sound name with sound obbject
	std::map<std::string, Sound*> sound_map;



};

