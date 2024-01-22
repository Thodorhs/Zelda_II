#pragma once
#include <iostream>
#include <functional>
#include "SDL.h"

class GravityHandler {
public:
	using OnSolidGroundPred = std::function<bool(const SDL_Rect&)>;
	using OnStartFalling = std::function<void(void)>;
	using OnStopFalling = std::function<void(void)>;
	
protected:
	bool gravityAddicted = true;
	bool isFalling = false;
	OnStartFalling onStartFalling;
	OnStopFalling onStopFalling;
	OnSolidGroundPred onSolidGround;
public:
	void set_gravity_addicted(const bool state) { gravityAddicted = state; }

	template <typename T> void SetOnStartFalling(const T& f)
	{
		onStartFalling = f;
	}
	template <typename T> void SetOnStopFalling(const T& f)
	{
		onStopFalling = f;
	}
	template <typename T> void SetOnSolidGround(const T& f)
	{
		onSolidGround = f;
	}
	void Reset(void) { isFalling = false; }
	void Check(const SDL_Rect& r);
};
