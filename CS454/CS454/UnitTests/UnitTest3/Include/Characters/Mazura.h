#pragma once
#include "Character.h"

class Mazura : public Character {
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

	Mazura(const std::string& id, const SDL_Point _start_pos)
	{
		type = "Mazura";
		Id = id;
		start_pos = _start_pos;
		health = 600;
		rate = 5;
	}
};