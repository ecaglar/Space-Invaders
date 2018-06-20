#include "SoundManager.h"




void SoundManager::tick()
{

}

void SoundManager::clean()
{

}

void SoundManager::init()
{
	Sound* s;

	s = new Sound();
	s->loadWav("../Data/sounds/explosion.wav");
	sound_map["explosion"] = s;

	s = new Sound();
	s->loadWav("../Data/sounds/player_shot.wav");
	sound_map["player_shot"] = s;

	s = new Sound();
	s->loadWav("../Data/sounds/vader_movement_1.wav");
	sound_map["vader_movement_1"] = s;

	s = new Sound();
	s->loadWav("../Data/sounds/vader_movement_2.wav");
	sound_map["vader_movement_2"] = s;

	s = new Sound();
	s->loadWav("../Data/sounds/vader_shot.wav");
	sound_map["vader_shot"] = s;

	s = new Sound();
	s->loadWav("../Data/sounds/voice_game_over.wav");
	sound_map["voice_game_over"] = s;

	s = new Sound();
	s->loadWav("../Data/sounds/voice_get_ready.wav");
	sound_map["voice_get_ready"] = s;

}

void SoundManager::play_sound(std::string name)
{
	std::map<std::string, Sound*>::iterator i;
	i = sound_map.find(name);
	if(i != sound_map.end()){
		Sound* sound = i->second;
		sound->play();
	}
}
