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

struct Point { int x, y; };

void TileTerrainDisplay(TileMap* map, const SDL_Rect& viewWin, const SDL_Rect& displayArea, SDL_Surface* ImgSurface, SDL_Renderer* myrenderer);
void PutTile(Dim x, Dim y, Index tile, SDL_Renderer* myrenderer, SDL_Texture* texture);

//Scrolling
int GetMapPixelWidth(void);
int GetMapPixelHeight(void);
void Scroll(SDL_Rect* viewWin, int dx, int dy);
bool CanScrollHoriz(const SDL_Rect& viewWin, int dx);
bool CanScrollVert(const SDL_Rect& viewWin, int dy);

static void FilterScrollDistance(
	int viewStartCoord, // x or y
	int viewSize, // w or h
	int* d, // dx or dy
	int maxMapSize // w or h 
);
void FilterScroll(const SDL_Rect& viewWin, int* dx, int* dy);
void ScrollWithBoundsCheck(SDL_Rect* viewWin, int dx, int dy);
