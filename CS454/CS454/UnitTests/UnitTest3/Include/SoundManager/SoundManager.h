#pragma once
#include <SDL_mixer.h>
#include <map>
#include <string>
#include "../../../../Engine/Include/Util/Print.h"
#include <filesystem>

class SoundManager {
private:
	static SoundManager singleton;
	std::map<std::string, Mix_Music*> music;
	std::map<std::string, Mix_Chunk*> chunks;
public:
	static auto get_singleton(void) -> SoundManager& { return singleton; }
	Mix_Music* get_music(std::string name);
	Mix_Chunk* get_sfx(std::string name);
	void audio_init();
	void play_music(std::string name, int loops);
	void pause_music();
	void resume_music();
	void play_sfx(std::string name, int loops,int channel);

};