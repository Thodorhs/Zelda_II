#include "../../Include/Characters/Character.h"

void Character::NotifyStarted(void) {
	if (onStart)
		onStart(this);
}

void Character::NotifyStopped(void) {
	if (onStop)
		onStop(this);
}

void Character::NotifyAction(void) {
	if (onAction)
		onAction(this);
}