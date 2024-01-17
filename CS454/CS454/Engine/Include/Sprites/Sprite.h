#pragma once

#include "MotionQuantizer.h"
#include "../KeyFrameAnimation/AnimationFilm.h"
#include "../Util/EngineDefines.h"
#include "../Grid/Grid.h"
#include "SDL.h"
#include "Clipper.h"


class Sprite {
public:
	using Mover = std::function<void(const SDL_Rect&, int* dx, int* dy)>;

protected:
	bool directMotion = false;
	byte frameNo = 0;
	SDL_Rect frameBox; // inside the film
	int x = 0, y = 0;
	bool isVisible = false;
	AnimationFilm* currFilm = nullptr;
	//BoundingArea* boundingArea = nullptr;
	unsigned zorder = 0;
	std::string typeId, stateId;
	Mover mover;
	
	MotionQuantizer quantizer;
public:
	template <typename Tfunc>
	void SetMover(const Tfunc& f)
	{
		quantizer.SetMover(mover = f);
	}

	
	const SDL_Rect GetBox(void) const
	{
		return { x, y, frameBox.w, frameBox.h };
	}
	const SDL_Rect GetScaledBox(void)const
	{
		return { x, y, frameBox.w/2, frameBox.h/2 };
	}
	void Move(int dx, int dy)
	{
		quantizer.Move(GetBox(), &dx, &dy);
	}
	void SetPos(int _x, int _y) { x = _x; y = _y; }
	void SetZorder(unsigned z) { zorder = z; }
	unsigned GetZorder(void) { return zorder; }
	void Display(SDL_Surface dest, const SDL_Rect& dpyArea, const Clipper& clipper, SDL_Renderer* renderer) const;
	void SetFrame(byte i) {
		if (i != frameNo) {
			assert(i < currFilm->GetTotalFrames());
			frameBox = currFilm->GetFrameBox(frameNo = i);
		}
	}
	byte GetFrame(void) const { return frameNo; }
	
	auto GetTypeId(void) -> const std::string& { return typeId; }
	void SetVisibility(bool v) { isVisible = v; }
	bool IsVisible(void) const { return isVisible; }
	bool CollisionCheck(const Sprite* s) const;
	static void Blit(SDL_Renderer* renderer,const SDL_Rect& src_rect,const SDL_Rect& dest_rect, SDL_Texture* film_bitmap);
	Sprite& SetHasDirectMotion(bool v) { directMotion = true; return *this; }
	const Mover MakeSpriteGridLayerMover(TileLayer* layer, Sprite* sprite);

	Sprite(int _x, int _y,AnimationFilm* film, std::string _typeId = "") :
		x(_x), y(_y), currFilm(film), typeId(std::move(_typeId))
	{
		frameNo = currFilm->GetTotalFrames(); SetFrame(0);
	}

};