#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_Image.h"
#include "MapEditor.h"

#define MUL_TILE_WIDTH(i) ((i)<<4)
#define MUL_TILE_HEIGHT(i)((i)<<4)
#define DIV_TILE_WIDTH(i) ((i)>>4)
#define DIV_TILE_HEIGHT(i)((i)>>4)
#define MOD_TILE_WIDTH(i) ((i)&15)
#define MOD_TILE_HEIGHT(i)((i)&15)


struct Rect { int x, y, w, h; };
struct Point { int x, y; };

class ViewWindow {
private:
	int MapPixelWidth = 21 * 16;
	int MapPixelHeight = 42 * 16;

public:
	float CameraPosX;
	float CameraPosY;

	int MouseX;
	int MouseY;

	void TileTerrainDisplay(TileMap* map, const Rect& viewWin, const Rect& displayArea, SDL_Surface* ImgSurface, SDL_Renderer* myrenderer);
	void PutTile(Dim x, Dim y, Index tile, SDL_Renderer* myrenderer, SDL_Texture* texture);

	//Scrolling
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
	void FilterScroll(const Rect& viewWin, int* dx, int* dy);
	void ScrollWithBoundsCheck(Rect* viewWin, int dx, int dy);

};