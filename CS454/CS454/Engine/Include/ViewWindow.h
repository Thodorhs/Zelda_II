#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_Image.h"
#include"Util/EngineDefines.h"
#include "MapEditor.h"



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
