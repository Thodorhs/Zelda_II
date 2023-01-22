#include "../Include/Grid/GridCompute.h"

void printgrid(GridIndex* grid, unsigned rows, unsigned cols) {
	for (auto c = 0; c < rows * cols * GRID_ELEMENTS_PER_TILE; ++c) {
		if (grid[c] == GRID_SOLID_TILE)
			std::cout << "O";
		else
			std::cout << "-";
	}
	std::cout <<"Last" << std::endl;
}

void ComputeTileGridBlocks1(Index(&MapGetTile)(Dim, Dim), GridIndex* grid, unsigned rows, unsigned cols) {
	for (auto row = 0; row < rows; ++row) //HEIGHT
		for (auto col = 0; col < cols; ++col) { //WIDTH
			memset(
				grid,
				IsTileIndexAssumedEmpty(MapGetTile(col, row)) ? GRID_EMPTY_TILE : GRID_SOLID_TILE,
				GRID_ELEMENTS_PER_TILE
			);
			grid += GRID_ELEMENTS_PER_TILE;
		}
}
