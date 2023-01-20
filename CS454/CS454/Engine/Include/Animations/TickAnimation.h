#include "Animation.h"
#include <assert.h>

class TickAnimation : public Animation {
protected:
	unsigned delay = 0;
	unsigned reps = 1;
	bool isDiscrete = true; // false: when used for custom timed actions
	bool Inv(void) const { return isDiscrete || reps == 1; }
public:
	using Me = TickAnimation;
	unsigned GetDelay(void) const { return delay; }
	Me& SetDelay(unsigned v) { delay = v; return *this; }
	unsigned GetReps(void) const { return reps; }
	Me& SetReps(unsigned n) { reps = n; return *this; }
	bool IsForever(void) const { return !reps; }
	Me& SetForever(void) { reps = 0; return *this; }
	bool IsDiscrete(void) const { return isDiscrete; }
	Animation* Clone(void) const override
	{
		return new TickAnimation(id, delay, reps, isDiscrete);
	}
	TickAnimation(const std::string& _id, unsigned d, unsigned r, bool discrete) :
		Animation(id), delay(d), reps(r), isDiscrete(discrete) {
		assert(Inv());
	}
};
