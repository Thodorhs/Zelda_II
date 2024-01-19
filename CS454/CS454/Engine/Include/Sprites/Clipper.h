#pragma once
#include <iostream>
#include <functional>
#include "SDL.h"
#include "../TileLayer.h"


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