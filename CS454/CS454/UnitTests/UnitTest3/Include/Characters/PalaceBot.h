#pragma once
#include "Character.h"

class PalaceBot : public Character {

public:
	void progress_character()override {
		NotifyAction();
	}
	void Start() override
	{
		isActive = true;
		NotifyStarted();
	}

	void Stop()override
	{
		isActive = false;
		NotifyStopped();
	}


	PalaceBot(const std::string& id, const SDL_Point _start_pos)
	{
		type = "Bot";
		Id = id;
		start_pos = _start_pos;
		health = 64;
	}
};