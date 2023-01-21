#include "../../../../Engine/Include/Animators/AnimatorManager.h"

AnimatorManager AnimatorManager::singleton; // MIGHT NEED TO MOVE THIS ONE

void Animator::Finish(bool isForced) {
	if (!HasFinished()) {
		state = isForced ? ANIMATOR_STOPPED : ANIMATOR_FINISHED;
		NotifyStopped();
	}
}
void Animator::Stop(void)
{
	Finish(true);
}

void Animator::NotifyStarted(void) {
	AnimatorManager::GetSingleton().MarkAsRunning(this);
	if (onStart)
		(onStart)(this);
}
void Animator::NotifyStopped(void) {
	AnimatorManager::GetSingleton().MarkAsSuspended(this);
	if (onFinish)
		(onFinish)(this);
}
void Animator::NotifyAction(const Animation& anim) {
	if (onAction)
		(onAction)(this, anim);
}


void Animator::TimeShift(timestamp_t offset)
{
	lastTime += offset;
}


Animator::Animator(void)
{
	AnimatorManager::GetSingleton().Register(this);
}
Animator::~Animator(void)
{
	AnimatorManager::GetSingleton().Cancel(this);
}
