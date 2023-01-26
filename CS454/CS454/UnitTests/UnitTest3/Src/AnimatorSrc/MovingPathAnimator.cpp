#include "../../../..//Engine/Include/Animators/MovingPathAnimator.h"

void MovingPathAnimator::Progress(timestamp_t currTime) {
	
	PathEntry CurrentEntry = anim->GetPath().at(currRep);

	/*
	while (currTime > lastTime && (currTime - lastTime) >= CurrentEntry.delay){
		if (currFrame == anim->GetEndFrame()) {
			assert(anim->IsForever() || currRep < anim->GetReps());
			currFrame = anim->GetStartFrame(); // flip to start
		}
		else ++currFrame;

		lastTime += anim->GetDelay();
		NotifyAction(*anim);
		if (currFrame == anim->GetEndFrame())
			if (!anim->IsForever() && ++currRep == anim->GetReps()) {
				state = ANIMATOR_FINISHED;
				NotifyStopped();
				return;
			}
	}*/
}


void MovingPath_Action(Sprite* sprite, Animator* animator, const MovingPathAnimation& anim) {

}