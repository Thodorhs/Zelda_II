#pragma once
#include "Animator.h"
#include "../Animations/MovingPathAnimation.h"

class MovingPathAnimator : public Animator {
protected:
	MovingPathAnimation* anim = nullptr;
	unsigned currRep = 0; // animation state

public:
	void Progress(timestamp_t currTime);
	void setAnimation(const std::string& _id, unsigned s, unsigned e, unsigned r, int dx, int dy, int d);
	void Start(MovingPathAnimation* a, timestamp_t t);

	MovingPathAnimator(void) = default;
};