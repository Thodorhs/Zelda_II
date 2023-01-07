#pragma once
#include "Grid.h"
#include <set>


//GridCompute1
void SetGridTile(GridMap* m, Dim col, Dim row, GridIndex index);
bool IsTileIndexAssumedEmpty(Index index);
void ComputeTileGridBlocks1(Index (&MapGetTile)(Dim, Dim), GridIndex* grid);

//Display Grid
GridIndex* GetGridTileBlock(Dim colTile, Dim rowTile, Dim tileCols, GridIndex* grid);
void DisplayGrid(SDL_Rect viewWin, GridIndex* grid, Dim tileCols ,SDL_Renderer* myrenderer);