#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_Image.h"
#include "MapEditor.h"

struct Rect { int x, y, w, h; };
struct Point { int x, y; };

class ViewWindow {
private:

public:
	float CameraPosX;
	float CameraPosY;

	int MouseX;
	int MouseY;

	void TileTerrainDisplay(TileMap* map, const Rect& viewWin, const Rect& displayArea, SDL_Surface* ImgSurface, SDL_Renderer* myrenderer, SDL_Window* Gwindow);
	void PutTile(SDL_Rect dstrect, unsigned short x, unsigned short y, SDL_Rect srcrect, unsigned short tile, SDL_Renderer* myrenderer, SDL_Texture* tileTexture);

	//Scrolling
	/*
	int GetMapPixelWidth(void);
	int GetMapPixelHeight(void);
	void Scroll(Rect* viewWin, int dx, int dy);
	bool CanScrollHoriz(const Rect& viewWin, int dx);
	bool CanScrollVert(const Rect& viewWin, int dy);
	static void FilterScrollDistance(
		int viewStartCoord, // x or y
		int viewSize, // w or h
		int* d, // dx or dy
		int maxMapSize // w or h 
	);
	void FilterScroll(const Rect& viewWin, int* dx, int* dy);*/
};