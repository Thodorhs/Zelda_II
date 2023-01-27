#include <iostream>
#include <functional>
#include "SDL.h"
#include "../TileLayer.h"

// generic clipper assuming any terrain-based view
// and any bitmap-based display area
class Clipper {
public:
	using View = std::function<const SDL_Rect& (void)>;
private:
	View view;
public:
	Clipper& SetView(const View& f)
	{
		view = f; return *this;
	}
	bool Clip(
		const SDL_Rect& r,
		const SDL_Rect& dpyArea,
		SDL_Point* dpyPos,
		SDL_Rect* clippedBox
	) const;
	Clipper(void) = default;
	Clipper(const Clipper&) = default;
};

const Clipper MakeTileLayerClipper(TileLayer* layer);