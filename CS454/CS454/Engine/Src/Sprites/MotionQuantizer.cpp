#include "../../../Engine/Include/Sprites/MotionQuantizer.h"

void MotionQuantizer::Move(const SDL_Rect& r, int* dx, int* dy) {
	if (!used)
		mover(r, dx, dy);
	else
		do {
			auto sign_x = number_sign(*dx);
			auto sign_y = number_sign(*dy);
			auto dxFinal = sign_x * std::min(horizMax, sign_x * *dx);
			auto dyFinal = sign_y * std::min(vertMax, sign_y * *dy);
			mover(r, &dxFinal, &dyFinal);
			if (!dxFinal) // X motion denied
				*dx = 0;
			else
				*dx -= dxFinal;
			if (!dyFinal) // Y motion denied
				*dy = 0;
			else
				*dy -= dyFinal;
		} while (*dx || *dy);
}
