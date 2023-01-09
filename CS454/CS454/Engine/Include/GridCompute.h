#pragma once
#include "Grid.h"
#include <set>


//GridCompute1
bool IsTileIndexAssumedEmpty(Index index);
void ComputeTileGridBlocks1(Index (&MapGetTile)(Dim, Dim), GridIndex* grid);

