#include "../../Include/Animators/ScrollingAnimator.h"

void ScrollAnimator::Progress(timestamp_t currTime) {
	while (currTime > lastTime && (currTime - lastTime) >= anim->GetDelay()) {
		lastTime += anim->GetDelay();
		NotifyAction(*anim);
		if (!anim->IsForever() && ++currRep == anim->GetReps()) {
			state = ANIMATOR_FINISHED;
			NotifyStopped();
			return;
		}
	}
}

#include "../../Include/GameLoopFuncs/Input.h"

void ScrollAction(Sprite* sprite, Animator* animator, const ScrollAnimation& anim) {
	
	InputKeys::GetSingleton().move_pixels_x(anim.GetDx());
	animator->SetOnAction(
		[sprite](Animator* animator, const Animation& anim) {
			assert(dynamic_cast<const ScrollAnimation*>(&anim));
			ScrollAction(
				sprite, animator,
				(const ScrollAnimation&)anim
			);
		}
	);
}

auto ScrollAnimator::generic_animator_action(Sprite* s) -> animator_action
{
	return ([s](Animator* animator, const Animation& anim)
		{
			ScrollAction(s, animator, (const ScrollAnimation&)anim);
		});
};