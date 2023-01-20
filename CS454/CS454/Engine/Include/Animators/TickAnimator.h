#pragma once
#include "../Animations/TickAnimation.h"
#include "Animator.h"

class TickAnimator : public Animator {
protected:
	TickAnimation* anim = nullptr;
	unsigned currRep = 0;
	unsigned elapsedTime = 0; // keep track of time passed between triggers
public:
	void Progress(timestamp_t currTime) override;
	unsigned GetCurrRep(void) const { return currRep; }
	unsigned GetElapsedTime(void) const { return elapsedTime; }
	float GetElapsedTimeNormalised(void) const
	{
		return float(elapsedTime) / float(anim->GetDelay());
	}
	void Start(const TickAnimation& a, timestamp_t t) {
		anim = (TickAnimation*)a.Clone();
		lastTime = t;
		state = ANIMATOR_RUNNING;
		currRep = 0;
		elapsedTime = 0;
		NotifyStarted();
	}
	TickAnimator(void) = default;
};
