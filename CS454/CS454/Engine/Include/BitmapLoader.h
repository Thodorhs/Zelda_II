#pragma once
#include "../Include/EngineDefines.h"
#include "SDL_image.h"
#include <iostream>
#include <cassert>
#include <functional>
#include <vector>
#include <map>


class BitmapLoader {
private:
	using Bitmaps = std::map<std::string, BitmapTexture*>;
	Bitmaps bitmaps;
	BitmapTexture* GetBitmap (const std::string& path) const {
		auto i = bitmaps.find(path);
		return i != bitmaps.end() ? i->second : nullptr;
	}
public:
	BitmapTexture* Load (const std::string& path, SDL_Renderer* GameRenderer) {
		auto b = GetBitmap(path);
		if (!b) {
			bitmaps[path] = b = SDL_CreateTextureFromSurface(GameRenderer, IMG_Load(path.c_str()));
			assert(b);
		}
		return b;
	}
	// prefer to massively clear bitmaps at the end than
	// to destroy individual bitmaps during gameplay
	void CleanUp(void) {
		for (auto& i : bitmaps)
			SDL_DestroyTexture(i.second);
		bitmaps.clear();
	}
	BitmapLoader() {}
	~BitmapLoader() { CleanUp(); }
};
