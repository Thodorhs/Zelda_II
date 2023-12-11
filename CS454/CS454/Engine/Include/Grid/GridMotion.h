#pragma once
#include "Grid.h"
#include "SDL.h"
#include <cassert>

void SetGridTile(GridMapOld* m, Dim col, Dim row, GridIndex index);

void SetSolidGridTile(GridMapOld* m, Dim col, Dim row);

void SetEmptyGridTile(GridMapOld* m, Dim col, Dim row);

void SetGridTileFlags(GridMapOld* m, Dim col, Dim row, GridIndex flags);

void SetGridTileTopSolidOnly(GridMapOld* m, Dim col, Dim row);

bool CanPassGridTile(GridMap* m, Dim col, Dim row, GridIndex flags); // i.e. checks if flags set

void PrintMap(GridMapOld m);

void FilterGridMotion(GridMap* m, const SDL_Rect& r, int* dx, int* dy);

void FilterGridMotionLeft(GridMap* m, const SDL_Rect& r, int* dx);

void FilterGridMotionRight(GridMap* m, const SDL_Rect& r, int* dx);

void FilterGridMotionUp(GridMap* m, const SDL_Rect& r, int* dy);

void FilterGridMotionDown(GridMap* m, const SDL_Rect& r, int* dy);