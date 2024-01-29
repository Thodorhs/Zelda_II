#include "../../Include/Animators/MovingPathAnimator.h"


void MovingPathAnimator::Progress(timestamp_t currTime) {
	while (currTime > lastTime && (currTime - lastTime) >= anim->GetDelay(currRep)) {
		lastTime += anim->GetDelay(currRep);
		NotifyAction(*anim);
		if (!anim->isForever() && ++currRep == anim->GetReps()) {
			state = ANIMATOR_FINISHED;
			NotifyStopped();
			return;
		}
	}
}

void MovingPathAction(Sprite* sprite, Animator* animator, const MovingPathAnimation& anim) {
	sprite->Move(anim.GetPathDx(((MovingPathAnimator*)animator)->get_index()), anim.GetPathDy(((MovingPathAnimator*)animator)->get_index()));

	sprite->SetFrame(anim.GetFrame(((MovingPathAnimator*)animator)->get_index()));
	animator->SetOnAction(
		[sprite](Animator* animator, const Animation& anim) {
			assert(dynamic_cast<const MovingPathAnimation*>(&anim));
			MovingPathAction(
				sprite, animator,
				(const MovingPathAnimation&)anim
			);

		});
		
}


auto MovingPathAnimator::generic_animator_action(Sprite* s) -> animator_action
{
	return ([s](Animator* animator, const Animation& _anim)
		{
			MovingPathAction(s, animator, (const MovingPathAnimation&)_anim);
		});
}
