#include "../../Include/SoundManager/SoundManager.h"

auto sound_path() {
	std::filesystem::path cwd = std::filesystem::current_path();
	std::string find_first_part_path = cwd.string();
	size_t pos = find_first_part_path.find("out");
	std::string half_path = find_first_part_path.substr(0, pos);
	std::string full_asset_path = half_path + "UnitTests/UnitTest3/UnitTest3Media/sounds/";
	return full_asset_path;
}

Mix_Music* SoundManager::get_music(std::string name) {
	std::string music_path = sound_path().append(name);
	if (music[music_path] == nullptr) {
		music[music_path] = Mix_LoadMUS(music_path.c_str());
		if (music[music_path] == NULL)
			pr_info("cant load music file");
	}
	return music[music_path];
}

Mix_Chunk* SoundManager::get_sfx(std::string name) {
	std::string music_path = sound_path().append(name);
	if (chunks[music_path] == nullptr) {
		chunks[music_path] = Mix_LoadWAV(music_path.c_str());
		if (chunks[music_path] == NULL)
			pr_info("cant load sound effect file");
	}
	return chunks[music_path];
}

void SoundManager::audio_init() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		pr_info("error initializing audio");
	Mix_VolumeMusic(53);
}

void SoundManager::play_music(std::string name, int loops) {
	Mix_PlayMusic(get_music(name), loops);
}

void SoundManager::pause_music() {
	if (Mix_PlayingMusic() != 0)
		Mix_PauseMusic();
}

void SoundManager::resume_music() {
	if (Mix_PausedMusic() != 0)
		Mix_ResumeMusic();
}

void SoundManager::play_sfx(std::string name, int loops, int channel) {
	Mix_PlayChannel(channel,get_sfx(name), loops);
}