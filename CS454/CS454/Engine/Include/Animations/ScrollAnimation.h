#pragma once
#include "Animation.h"

struct ScrollEntry {
	int dx = 0;
	int dy = 0;
	unsigned delay = 0;
};
class ScrollAnimation : public Animation {
public:
	using Scroll = std::vector<ScrollEntry>;
private:
	Scroll scroll;
	unsigned delay = 0;
	unsigned reps = 0;
	int dx = 0;
public:
	bool IsForever(void) const { return !reps; }
	const unsigned GetDelay() { return delay; }
	const unsigned GetReps() { return reps; }
	const unsigned GetDx() const { return dx; }
	void SetDx(int _dx) { dx = _dx; }
	const Scroll& GetScroll(void) const { return scroll; }
	void SetScroll(const Scroll& p) { scroll = p; }
	Animation* Clone(void) const override
	{
		return new ScrollAnimation(id, scroll);
	}
	ScrollAnimation(const std::string& _id, const Scroll& _scroll) :
		Animation(_id), scroll(_scroll) {}
	ScrollAnimation(const std::string& id,unsigned _delay,unsigned _reps) :Animation(id) ,delay(_delay),reps(_reps){}
};
void ScrollAction(TileLayer& ActionLayer, TileLayer& HorizonLayer);