#pragma once
#include "Grid.h"
#include <set>
#include <cassert>
#include <Functional>
#include "../MapEditor.h"

void printgrid(GridIndex* grid, unsigned rows, unsigned cols);
void ComputeTileGridBlocks1(Index (&MapGetTile)(Dim, Dim), GridIndex* grid, unsigned rows, unsigned cols);

