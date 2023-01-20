#pragma once
#include "Animation.h"

class FlashAnimation : public Animation {
private:
	unsigned repetitions = 0;
	unsigned hideDelay = 0;
	unsigned showDelay = 0;
public:
	using Me = FlashAnimation;
	Me& SetRepetitions(unsigned n) { repetitions = n; return *this; }
	unsigned GetRepetitions(void) const { return repetitions; }
	Me& SetHideDeay(unsigned d) { hideDelay = d; return *this; }
	unsigned GetHideDeay(void) const { return hideDelay; }
	Me& SetShowDeay(unsigned d) { showDelay = d; return *this; }
	unsigned GetShowDeay(void) const { return showDelay; }
	Animation* Clone(void) const override
	{
		return new FlashAnimation(id, repetitions, hideDelay, showDelay);
	}
	FlashAnimation(const std::string& _id, unsigned n, unsigned show, unsigned hide) :
		Animation(id), repetitions(n), hideDelay(hide), showDelay(show) {}
};