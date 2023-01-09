#include "../../../Engine/Include/GridCompute.h"


void ComputeTileGridBlocks1(Index(&MapGetTile)(Dim, Dim), GridIndex* grid) {
	for (auto row = 0; row < 42; ++row) //HEIGHT
		for (auto col = 0; col < 21; ++col) { //WIDTH
			memset(
				grid,
				IsTileIndexAssumedEmpty(MapGetTile(col, row)) ? GRID_EMPTY_TILE : GRID_SOLID_TILE,
				GRID_ELEMENTS_PER_TILE
			);
			grid += GRID_ELEMENTS_PER_TILE;
		}
}
