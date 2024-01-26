#pragma once
#include "Animator.h"
#include "../Animations/MovingAnimation.h"


class MovingAnimator : public Animator {
protected:
	MovingAnimation* anim = nullptr;
	unsigned currRep = 0; // animation state
public:
	void Progress(timestamp_t currTime);
	auto GetAnim(void) const -> const MovingAnimation&
	{
		return *anim;
	}
	void Start(MovingAnimation* a, timestamp_t t) {
		anim = a;
		lastTime = t;
		state = ANIMATOR_RUNNING;
		currRep = 0;
		NotifyStarted();
	}


	void Start(timestamp_t t) override
	{
		lastTime = t;
		state = ANIMATOR_RUNNING;
		currRep = 0;
		NotifyStarted();
	}
	auto generic_animator_action(Sprite* s) -> animator_action override;
	void SetDx(const int dx)
	{
		anim->SetDx(dx);
	}

	void SetDy(const int dy)
	{
		anim->SetDy(dy);
	}

	int GetDx() const { return anim->GetDx(); }
	void SetDelay(int delay) { anim->SetDelay(delay); }

	std::string Get_ID() const override { return  id; }
	MovingAnimator(void) = default;
	MovingAnimator(const std::string& _id, MovingAnimation* _anim) : anim(_anim) { id = _id; }
};
void Sprite_MoveAction(Sprite* sprite, Animator* animator, const MovingAnimation& anim);
