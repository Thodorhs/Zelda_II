#pragma once
#include <SDL_mixer.h>
#include <map>

class SoundManager {
	private:
		static SoundManager* singleton;
		std::map<std::string, Mix_Music*> music;
		std::map<std::string, Mix_Chunk*> chunks;
	public:
		static SoundManager* get_singleton() { return singleton; }

};