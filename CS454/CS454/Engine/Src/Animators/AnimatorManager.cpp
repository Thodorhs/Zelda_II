#include "../../Include/Animators/AnimatorManager.h"
AnimatorManager AnimatorManager::singleton;


Animator::Animator(void)
{
	AnimatorManager::GetSingleton().Register(this);
}
Animator::~Animator(void)
{
	AnimatorManager::GetSingleton().Cancel(this);
}
