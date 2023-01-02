#pragma once
#include "../Include/MapEditor.h"
#include"../Include/GridMotion.h" 


extern bool IsTileIndexAssumedEmpty(Index index);
void ComputeTileGridBlocks1(const TileMap* map, GridIndex* grid);