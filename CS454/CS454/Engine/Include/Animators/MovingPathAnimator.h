#pragma once
#include "Animator.h"
#include "../Animations/MovingPathAnimation.h"

class MovingPathAnimator : public Animator {
protected:
	MovingPathAnimation* anim = nullptr;
	unsigned currRep = 0; // animation state

public:
	void Progress(timestamp_t currTime)override;
	void setAnimation(const std::string& _id, unsigned s, unsigned e, unsigned r, int dx, int dy, int d);
	void Start(MovingPathAnimation* a, timestamp_t t);
	auto generic_animator_action(Sprite* s) -> animator_action override;
	std::string Get_ID() const override { return  id; }
	void Start(timestamp_t t)override
	{

		lastTime = t;
		state = ANIMATOR_RUNNING;
		currRep = 0;
		NotifyStarted();
	}


	unsigned get_index() { return currRep; }

	


	MovingPathAnimator(void) = default;
	MovingPathAnimator(const std::string &_id,MovingPathAnimation *_anim)
	{
		id = _id;
		anim = _anim;
	};
};