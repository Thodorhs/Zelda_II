#include "../../../../Engine/Include/Animators/TickAnimator.h"


void TickAnimator::Progress(timestamp_t currTime) {
	if (!anim->IsDiscrete()) { // no discrete fires in every loop!
		elapsedTime = currTime - lastTime;
		lastTime = currTime;
		NotifyAction(*anim);
	}
	else
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