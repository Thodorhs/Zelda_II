#pragma once
#include "Animator.h"
#include "../Animations/ScrollAnimation.h"

class ScrollAnimator : public Animator {
protected:
	ScrollAnimation* anim = nullptr;
	unsigned currFrame = 0; // animation state
	unsigned currRep = 0; // animation state
public:
	void Progress(timestamp_t currTime);
	unsigned GetCurrFrame(void) const { return currFrame; }
	unsigned GetCurrRep(void) const { return currRep; }
	void Start(ScrollAnimation* a, timestamp_t t) {
		anim = a;
		lastTime = t;
		state = ANIMATOR_RUNNING;
		currFrame = 0;
		currRep = 0;
		NotifyStarted();
		NotifyAction(*anim);
	}
	ScrollAnimator(void) = default;
};
