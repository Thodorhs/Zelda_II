#pragma once
#include "Animator.h"
#include "../Animations/FrameRangeAnimation.h"

class FrameRangeAnimator : public Animator {
protected:
	FrameRangeAnimation* anim = nullptr;
	unsigned currFrame = 0; // animation state
	unsigned currRep = 0; // animation state
	
public:
	void Progress(timestamp_t currTime);
	unsigned GetCurrFrame(void) const { return currFrame; }
	unsigned GetCurrRep(void) const { return currRep; }
	void Start(FrameRangeAnimation* a, timestamp_t t) {
	
		anim = a;
		lastTime = t;
		state = ANIMATOR_RUNNING;
		currFrame = anim->GetStartFrame();
		currRep = 0;
		NotifyStarted();
		NotifyAction(*anim);
	}

	void Start(timestamp_t t) 
	override{
		lastTime = t;
		state = ANIMATOR_RUNNING;
		currFrame = anim->GetStartFrame();
		currRep = 0;
		NotifyStarted();
		NotifyAction(*anim);
	}

	void SetDx(const int dx)
	{
		anim->SetDx(dx);
	}

	int GetDx()
	{
		return anim->GetDx();
	}

	void SetDy(const int dy)
	{
		anim->SetDy(dy);
	}

	auto generic_animator_action(Sprite* s) -> animator_action override;
	std::string Get_ID() const override { return  id; }
	FrameRangeAnimator(void) = default;
	FrameRangeAnimator(const std::string& _id) { id = _id; }
	FrameRangeAnimator(const std::string& _id,FrameRangeAnimation *_anim) : anim(_anim) { id = _id; }
	FrameRangeAnimator(FrameRangeAnimation* _anim) : anim(_anim) {}
	auto GetAnimation()const-> const FrameRangeAnimation& { return *anim; }
	
	
};
void FrameRange_Action(Sprite* sprite, Animator* animator, const FrameRangeAnimation& anim);
void FrameRange_Action_noSet(Sprite* sprite, Animator* animator, const FrameRangeAnimation& anim);