#include "../../../Engine/Include/GridMotion.h"
void SetGridMap(GridIndex* g) {
	auto startCol = 0;
	auto startRow = 0;

	for (Dim rowTile = startRow; rowTile <= 42; ++rowTile)
		for (Dim colTile = startCol; colTile <= 21; ++colTile) {
			auto* gridBlock = GetGridTileBlock(colTile, rowTile, 21, g);

			for (auto rowElem = 0; rowElem < GRID_BLOCK_ROWS; ++rowElem)
				for (auto colElem = 0; colElem < GRID_BLOCK_COLUMNS; ++colElem) {
					grid[rowTile*4 + rowElem][colTile*4 + colElem] = *(gridBlock);
				}
		
		}
}

GridMap* GetGridMap() {
	return &grid;
}

void SetSolidGridTile(GridMap* m, Dim col, Dim row)
{
	SetGridTile(m, col, row, GRID_SOLID_TILE);
}

void SetGridTile(GridMap* m, Dim col, Dim row, GridIndex index)
{
	(*m)[row][col] = index;
}

GridIndex GetGridTile(const GridMap* m, Dim col, Dim row)
{
	return (*m)[row][col];
}

void SetEmptyGridTile(GridMap* m, Dim col, Dim row)
{
	SetGridTile(m, col, row, GRID_EMPTY_TILE);
}
void SetGridTileFlags(GridMap* m, Dim col, Dim row, GridIndex flags)
{
	SetGridTile(m, col, row, flags);
}
void SetGridTileTopSolidOnly(GridMap* m, Dim col, Dim row)
{
	SetGridTileFlags(m, row, col, GRID_TOP_SOLID_MASK);
}
bool CanPassGridTile(GridMap* m, Dim col, Dim row, GridIndex flags) // i.e. checks if flags set
{
	//std::cout << col << "|" << row << std::endl;
	if (GRID_EMPTY_TILE == (int)GetGridTile(m, col, row)) return 1;
	if (GRID_SOLID_TILE == (int)GetGridTile(m, col, row)) return 0;
	//return (GetGridTile(m, col, row) & flags) != 0; //was (m,row,col)
}
void PrintMap() {
	for (int i = 0; i < GRID_MAX_HEIGHT; i++) {
		for (int j = 0; j < GRID_MAX_WIDTH; j++) {
			if (grid[i][j])
				std::cout << ((int)grid[i][j]);
			else
				std::cout << "-";
		}
		std::cout << "END"<<std::endl;
	}
}
void FilterGridMotion(GridMap* m, const SDL_Rect& r, int* dx, int* dy) {
	assert(
		abs(*dx) <= GRID_ELEMENT_WIDTH && abs(*dy) <= GRID_ELEMENT_HEIGHT
	);

	// try horizontal move
	if (*dx < 0)
		FilterGridMotionLeft(m, r, dx);
	else
		if (*dx > 0)
			FilterGridMotionRight(m, r, dx);
	// try vertical move
	if (*dy < 0)
		FilterGridMotionUp(m, r, dy);
	else
		if (*dy > 0)
			FilterGridMotionDown(m, r, dy);
}

void FilterGridMotionLeft(GridMap* m, const SDL_Rect& r, int* dx) {
	auto x1_next = r.x + *dx;
	if (x1_next < 0)
		*dx = -r.x;
	else {
		auto newCol = DIV_GRID_ELEMENT_WIDTH(x1_next);
		auto currCol = DIV_GRID_ELEMENT_WIDTH(r.x);
		if (newCol != currCol) {
			assert(newCol + 1 == currCol); // we really move left
			auto startRow = DIV_GRID_ELEMENT_HEIGHT(r.y);
			auto endRow = DIV_GRID_ELEMENT_HEIGHT(r.y + r.h - 1);
			for (auto row = startRow; row <= endRow; ++row)
				if (!CanPassGridTile(m, newCol, row, GRID_RIGHT_SOLID_MASK)) {
					std::cout << "Cant Move Left" << std::endl;
					*dx = MUL_GRID_ELEMENT_WIDTH(currCol) - r.x;
					break;
				}
		}
	}
}

void FilterGridMotionRight(GridMap* m, const SDL_Rect& r, int* dx) {
	auto x2 = r.x + r.w - 1;
	auto x2_next = x2 + *dx;
	if (x2_next >= MAX_PIXEL_WIDTH) {
		std::cout << "Check" << std::endl;
		*dx = (MAX_PIXEL_WIDTH)-1 - x2;
	}
	else {
		auto newCol = DIV_GRID_ELEMENT_WIDTH(x2_next);
		auto currCol = DIV_GRID_ELEMENT_WIDTH(x2);
		if (newCol != currCol) {
			assert(newCol - 1 == currCol); // we really move right
			auto startRow = DIV_GRID_ELEMENT_HEIGHT(r.y);
			auto endRow = DIV_GRID_ELEMENT_HEIGHT(r.y + r.h - 1);
			for (auto row = startRow; row <= endRow; ++row)
				if (!CanPassGridTile(m, newCol, row, GRID_LEFT_SOLID_MASK)) {
					std::cout << "Cant Move Right" << row << std::endl;
					*dx = (MUL_GRID_ELEMENT_WIDTH(newCol))-1 - x2;
					break;
				}
		}
	}
}

void FilterGridMotionUp(GridMap* m, const SDL_Rect& r, int* dy) {

}

void FilterGridMotionDown(GridMap* m, const SDL_Rect& r, int* dy) {

}