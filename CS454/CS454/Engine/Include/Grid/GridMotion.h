#pragma once
#include "Grid.h"
#include "SDL.h"
#include <cassert>

void SetGridMap(GridIndex* g, unsigned rows, unsigned cols);

GridMap* GetGridMap();

void SetGridTile(GridMap* m, Dim col, Dim row, GridIndex index);

GridIndex GetGridTile(const GridMap* m, Dim col, Dim row);

void SetSolidGridTile(GridMap* m, Dim col, Dim row);

void SetEmptyGridTile(GridMap* m, Dim col, Dim row);

void SetGridTileFlags(GridMap* m, Dim col, Dim row, GridIndex flags);

void SetGridTileTopSolidOnly(GridMap* m, Dim col, Dim row);

bool CanPassGridTile(GridMap* m, Dim col, Dim row, GridIndex flags); // i.e. checks if flags set

void PrintMap(GridMap m);

void FilterGridMotion(GridMap* m, const SDL_Rect& r, int* dx, int* dy);

void FilterGridMotionLeft(GridMap* m, const SDL_Rect& r, int* dx);

void FilterGridMotionRight(GridMap* m, const SDL_Rect& r, int* dx);

void FilterGridMotionUp(GridMap* m, const SDL_Rect& r, int* dy);

void FilterGridMotionDown(GridMap* m, const SDL_Rect& r, int* dy);