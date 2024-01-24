#include "../../Include/Animators/MovingAnimator.h"


void MovingAnimator::Progress(timestamp_t currTime) {
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
void Sprite_MoveAction(Sprite* sprite,Animator* animator ,const MovingAnimation& anim) {
	
	sprite->Move(anim.GetDx(), anim.GetDy());
	

	animator->SetOnAction(
		[sprite](Animator* animator, const Animation& anim) {
			assert(dynamic_cast<const MovingAnimation*>(&anim));
			Sprite_MoveAction(
				sprite,animator,
				(const MovingAnimation&)anim
			);
		}
	);
}

auto MovingAnimator::generic_animator_action(Sprite* s) -> animator_action {
	return ([s](Animator* animator, const Animation& anim)
		{
			Sprite_MoveAction(s, animator, (const MovingAnimation&)anim);
		});
}