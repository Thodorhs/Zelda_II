#pragma once
#include "Animation.h"

class MovingAnimation : public Animation {
protected:
	unsigned reps = 0; // 0=forever
	int dx = 0, dy = 0;
	unsigned delay = 0;
public:
	using Me = MovingAnimation;
	int GetDx(void) const { return dx; }
	Me& SetDx(int v) { dx = v; return *this; }
	int GetDy(void) const { return dy; }
	Me& SetDy(int v) { dy = v; return *this; }
	unsigned GetDelay(void) const { return delay; }
	Me& SetDelay(unsigned v) { delay = v; return *this; }
	unsigned GetReps(void) const { return reps; }
	Me& SetReps(unsigned n) { reps = n; return *this; }
	bool IsForever(void) const { return !reps; }
	Me& SetForever(void) { reps = 0; return *this; }
	Animation* Clone(void) const override
	{
		return new MovingAnimation(id, reps, dx, dy, delay);
	}
	MovingAnimation(
		const std::string& _id, unsigned _reps, int _dx, int _dy, unsigned _delay
	) : Animation(_id), reps(_reps), dx(_dx), dy(_dy), delay(_delay) {}
};
