#pragma once
#include "MotionQuantizer.h"
#include "../KeyFrameAnimation/AnimationFilm.h"

class Clipper;
class Sprite {
public:
	using Mover = std::function<void(const SDL_Rect&, int* dx, int* dy)>;
protected:
	byte frameNo = 0;
	SDL_Rect frameBox; // inside the film
	int x = 0, y = 0;
	bool isVisible = false;
	AnimationFilm* currFilm = nullptr;
	BoundingArea* boundingArea = nullptr;
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
	void Move(int dx, int dy)
	{
		quantizer.Move(GetBox(), &dx, &dy);
	}
	void SetPos(int _x, int _y) { x = _x; y = _y; }
	void SetZorder(unsigned z) { zorder = z; }
	unsigned GetZorder(void) { return zorder; }