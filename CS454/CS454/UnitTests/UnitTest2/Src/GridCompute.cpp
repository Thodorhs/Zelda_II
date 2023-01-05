#include "../../../Engine/Include/GridCompute.h"

//ComputeGrid1
bool IsTileIndexAssumedEmpty(Index index) {
	if (index == 61) return false;
	else return true;
}

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

GridIndex* GetGridTileBlock(Dim colTile, Dim rowTile, Dim tileCols, GridIndex* grid) {
	return grid + (rowTile * tileCols + colTile) * GRID_BLOCK_SIZEOF;
}


void DisplayGrid(SDL_Rect viewWin, GridIndex* grid, Dim tileCols, SDL_Renderer* myrenderer) {
	auto startCol = DIV_TILE_WIDTH(viewWin.x);
	auto startRow = DIV_TILE_HEIGHT(viewWin.y);
	auto endCol = DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1);
	auto endRow = DIV_TILE_HEIGHT(viewWin.y + viewWin.h - 1);
	for (Dim rowTile = startRow; rowTile <= endRow; ++rowTile)
		for (Dim colTile = startCol; colTile <= endCol; ++colTile) {

			auto sx = MUL_TILE_WIDTH(colTile - startCol);
			auto sy = MUL_TILE_HEIGHT(rowTile - startRow);
			auto* gridBlock = GetGridTileBlock(colTile, rowTile, tileCols, grid);
			for (auto rowElem = 0; rowElem < GRID_BLOCK_ROWS; ++rowElem)
				for (auto colElem = 0; colElem < GRID_BLOCK_COLUMNS; ++colElem)

					if (*gridBlock++ & GRID_SOLID_TILE) {
						auto x = sx + colElem * 4;//MUL_GRID_ELEMENT_WIDTH(colElem);
						auto y = sy + rowElem * 4;//MUL_GRID_ELEMENT_HEIGHT(rowElem);
						auto w = GRID_ELEMENT_WIDTH - 1;
						auto h = GRID_ELEMENT_HEIGHT - 1;
						SDL_Rect gridRect;
						gridRect.x = x;
						gridRect.y = y;
						gridRect.w = w;
						gridRect.h = h;
						SDL_RenderDrawRect(myrenderer, &gridRect);
					}
		}
}
