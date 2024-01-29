#pragma once
#include "Character.h"

class Guma :  public Character {
private:
	unsigned rate;
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

	unsigned GetRate() { return rate; }
	void SetRate(const unsigned _rate) { rate = _rate; }

	Guma(const std::string& id, const SDL_Point _start_pos)
	{
		type = "Guma";
		Id = id;
		start_pos = _start_pos;
		health = 64;
		rate = 5;
	}
};