#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_Image.h"
#include"Util/EngineDefines.h"
#include "MapEditor.h"

//#include "Util/ConfigFuncs.h"

struct Point { int x, y; };
static Index mod_index[255];
static Index div_index[255];

typedef SDL_Rect ViewWindow_t;

typedef struct Render {
	SDL_Surface* ImgSurface;
	SDL_Renderer* myrenderer;
	SDL_Window* Gwindow;
	SDL_Rect ViewWindowR;
	SDL_Texture* Tileset;
	SDL_Texture* RenderTextureTarget;
	
	int view_scale;

	Render(int x, int y, int w, int h, int scale) :
		ViewWindowR({ x, y, w/scale, h/scale }),
		ImgSurface((SDL_Surface*)0),
		myrenderer((SDL_Renderer*)0),
		Gwindow((SDL_Window*)0), 
		Tileset((SDL_Texture*)0),
		view_scale(scale),
		RenderTextureTarget((SDL_Texture*)0) {};
	Render() = default;
};


void TileTerrainDisplay(TileMap* map, const SDL_Rect& viewWin, const SDL_Rect& displayArea, SDL_Renderer* myrenderer, SDL_Texture* Tileset, SDL_Texture* RenderTextureTarget);
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

void pre_cache(void);
