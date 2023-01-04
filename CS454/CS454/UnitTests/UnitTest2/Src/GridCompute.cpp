#include "../Bin/GridCompute.h"
#include ""
extern bool IsTileIndexAssumedEmpty(Index index);

void ComputeTileGridBlocks1(const TileMap* map, GridIndex* grid) {
	for (auto row = 0; row < MAX_HEIGHT; ++row)
		for (auto col = 0; col < MAX_WIDTH; ++col) {
			memset(
				grid,
				IsTileIndexAssumedEmpty(GetTile(map, col, row)) ? GRID_EMPTY_TILE : GRID_SOLID_TILE,
				GRID_ELEMENTS_PER_TILE
			);
			grid += GRID_ELEMENTS_PER_TILE;
		}
}

