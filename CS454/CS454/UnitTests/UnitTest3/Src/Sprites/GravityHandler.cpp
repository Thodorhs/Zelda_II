#include "../../../../Engine/Include/Sprites/GravityHandler.h"

void GravityHandler::Check(const SDL_Rect& r) {
	if (gravityAddicted) {
		if (onSolidGround(r)) {
			if (isFalling) {
				isFalling = false;
				onStopFalling();
			}
		}
		else
			if (!isFalling) {
				isFalling = true;
				onStartFalling();
			}
	}
}
