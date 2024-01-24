#pragma once
#include "Animator.h"
#include "../Animations/ScrollAnimation.h"

class ScrollAnimator : public Animator {
protected:
	ScrollAnimation* anim = nullptr;
	unsigned currFrame = 0; // animation state
	unsigned currRep = 0; // animation state
	std::string id;
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

	void Start(timestamp_t t) override
	{
		lastTime = t;
		state = ANIMATOR_RUNNING;
		currRep = 0;
		NotifyStarted();
	}
	std::string Get_ID() const override { return  id; }
	ScrollAnimator(void) = default;
	ScrollAnimator(const std::string& _id,ScrollAnimation *_anim) : id(_id) ,anim(_anim){}
	auto generic_animator_action(Sprite* s) -> animator_action override;
};
