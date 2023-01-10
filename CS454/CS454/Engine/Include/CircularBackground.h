#pragma once
#include <iostream>
#include "SDL.h"

typedef SDL_Surface Bitmap;

class CircularBackground { // horizontal stripe
private:
	Rect viewWin;
	Bitmap bg = nullptr;
public:
	void Scroll(int dx) {
		viewWin.x += dx;
		if (viewWin.x < 0)
			viewWin.x = bg.w + viewWin.x;
		else
			if (viewWin.x >= bg.w)
				viewWin.x = viewWin.x - bg.w;
	}
	void Display(Bitmap dest, int x, int y) const {
		auto bg_w = bg.w;
		auto w1 = std::min(bg_w - viewWin.x, viewWin.w);
		//BitmapBlit(bg, { viewWin.x, viewWin.y, w1, viewWin.h }, dest, { x, y });
		if (w1 < viewWin.w) { // not whole view win fits
			auto w2 = viewWin.w - w1; // the remaining part
			//BitmapBlit(bg, { 0, viewWin.y, w2, viewWin.h }, dest, { x + w1, y });
		}
	}
};
