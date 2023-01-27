#pragma once
#include "Clipper.h"
#include "BoundingArea.h"
#include "MotionQuantizer.h"
#include "GravityHandler.h"
#include "../KeyFrameAnimation/AnimationFilm.h"
#include "../Util/EngineDefines.h"
#include "../Grid/GridLayer.h"
#include "SDL.h"

class Clipper;
class Sprite {
public:
	using Mover = std::function<void(const SDL_Rect&, int* dx, int* dy)>;
protected:
	byte frameNo = 0;
	SDL_Rect frameBox; // inside the film
	float x = 0, y = 0;
	float globalx = 0, globaly = 0;
	int w, h;
	bool isVisible = false;
	AnimationFilm* currFilm = nullptr;
	BoundingArea* boundingArea = nullptr;
	unsigned zorder = 0;
	std::string typeId, stateId;
	Mover mover;
	MotionQuantizer quantizer;
	bool directMotion = false;
	GravityHandler gravity;
public:
	int GetGlobalPositionX() { return globalx; }
	int GetGlobalPositionY() { return globaly; }
	void SetGlobalPosition(int _globalx, int _globaly) { globalx = x + _globalx, globaly = y + _globaly; }
	void set_state(std::string id) { stateId = id; }
	std::string get_state() { return stateId; }

	std::string get_type() { return typeId; }
	void change_film(AnimationFilm* new_film) { 
		currFilm = new_film;
		frameNo = new_film->GetTotalFrames();
		SetFrame(0);
	
	}
	
	template <typename Tfunc>
	void SetMover(const Tfunc& f)
	{
		quantizer.SetMover(mover = f);
	}
	const SDL_Rect GetBoxScaledDown(void) const
	{
		return { (int)x, (int)y, w >> 1, h >> 1};
	}
	const SDL_Rect GetBox(void) const
	{
		return { (int)x, (int)y, w , h };
	}

	const SDL_Rect GetGlobalBox(void) const
	{
		return { (int)globalx, (int)globaly, w, h };
	}
	GravityHandler& GetGravityHandler(void)
	{
		return gravity;
	}
	Sprite& SetHasDirectMotion(bool v) { directMotion = v; return *this; }
	bool GetHasDirectMotion(void) const { return directMotion; }
	Sprite& Move(int dx, int dy) {
		if (directMotion) { // apply unconditionally offsets!
			if (gravity.gravityAddicted)
				if (dy == 1) x += dx, y += 0.3;
				else x += dx, y += dy;
			else x += dx, y += dy;
		}
		else {
			quantizer.Move(GetBox(), &dx, &dy);
			gravity.Check(GetBox());
		}
		return *this;
	}
	void SetPos(int _x, int _y) { x = _x; y = _y; }
	void SetZorder(unsigned z) { zorder = z; }
	unsigned GetZorder(void) { return zorder; }
	void Display(BitmapSurface dest, const SDL_Rect& dpyArea, const Clipper& clipper, SDL_Renderer* GameRender) const;
	void SetFrame(byte i) {
		if (i != frameNo) {
			assert(i < currFilm->GetTotalFrames());
			frameBox = currFilm->GetFrameBox(frameNo = i);
			w = frameBox.w << 1;
			h = frameBox.h << 1;
		}
	}
	byte GetFrame(void) const { return frameNo; }
	/*void SetBoundingArea(const BoundingArea& area)
	{
		assert(!boundingArea); boundingArea = area.Clone();
	}
	void SetBoundingArea(BoundingArea* area)
	{
		assert(!boundingArea); boundingArea = area;
	}
	auto GetBoundingArea(void) const -> const BoundingArea*
	{
		return boundingArea;
	}*/
	auto GetTypeId(void) -> const std::string& { return typeId; }
	void SetVisibility(bool v) { isVisible = v; }
	bool IsVisible(void) const { return isVisible; }
	bool CollisionCheck(const Sprite* s) const;
	void Display(BitmapTexture dest, const SDL_Rect& dpyArea, const Clipper& clipper, SDL_Renderer* GameRenderer) const;
	Sprite(int _x, int _y, AnimationFilm* film, const std::string& _typeId = "") :
	x(_x), y(_y), currFilm(film), typeId(_typeId){
		frameNo = currFilm->GetTotalFrames(); SetFrame(0);
	}
};

void PrepareSpriteGravityHandler(GridLayer* gridLayer, Sprite* sprite);
const Sprite::Mover MakeSpriteGridLayerMover(GridLayer* gridLayer, Sprite* sprite);