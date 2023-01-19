#pragma once
#include "../Include/EngineDefines.h"
#include <iostream>
#include <cassert>
#include <functional>
#include <vector>

class AnimationFilm {
	std::vector<SDL_Rect> boxes;
	BitmapTexture* bitmap;
	std::string id;
public:
	struct Data {
		std::string id;
		std::vector<SDL_Rect> rects;
		std::string path;
	};

	byte GetTotalFrames(void) const{ return boxes.size(); }
	BitmapTexture* GetBitmap(void) const { return bitmap; }
	auto GetId(void) const -> const std::string& { return id; }

	const SDL_Rect& GetFrameBox(byte frameNo) const
	{
		assert(boxes.size() > frameNo); return boxes[frameNo];
	}
	void DisplayFrame(SDL_Renderer* dest, const SDL_Rect& at, byte frameNo) const
	{
		SDL_SetRenderTarget(dest, NULL);
		SDL_RenderCopy(dest, bitmap, &GetFrameBox(frameNo), &at);
	}
	void SetBitmap(BitmapTexture* b)
	{
		bitmap = b;
	}

	void Append(const SDL_Rect& r) { boxes.push_back(r); }
	AnimationFilm(const std::string& _id) : id(_id) {}
	AnimationFilm(BitmapTexture* _bitmap, const std::vector<SDL_Rect>& _boxes, const std::string& _id) {
		bitmap = _bitmap;
		boxes = _boxes;
		id = _id;
	}
};