#include "../Include/GridMotion.h"
void SetGridMap(GridIndex* g) {
	auto startCol = 0;
	auto startRow = 0;

	for (Dim rowTile = startRow; rowTile <= 42; ++rowTile)
		for (Dim colTile = startCol; colTile <= 21; ++colTile) {
			auto* gridBlock = GetGridTileBlock(colTile, rowTile, 21, g);

			for (auto rowElem = 0; rowElem < GRID_BLOCK_ROWS; ++rowElem)
				for (auto colElem = 0; colElem < GRID_BLOCK_COLUMNS; ++colElem) {
					grid[rowTile*4 + rowElem][colTile*4 + colElem] = *(gridBlock)++;
				}
		
		}
	
	//PrintMap(*(GetGridMap()));
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

	if (GRID_EMPTY_TILE == GetGridTile(m, col, row)) return 1;
	if (GRID_SOLID_TILE == GetGridTile(m, col, row)) return 0;
	std::cout << "nothing ???" << std::endl;
	//return (GetGridTile(m, col, row) & flags) != 0; //was (m,row,col)
}


void PrintMap(GridMap m) {
	for (int i = 0; i < GRID_MAX_HEIGHT; i++) {
		for (int j = 0; j < GRID_MAX_WIDTH; j++) {
			if (m[i][j])
				std::cout << ((int)m[i][j]);
			else
				std::cout << "-";
		}
		std::cout << "END"<<std::endl;
	}
}


void FilterGridMotion(GridMap* m, const SDL_Rect& r, int* dx, int* dy) {
	assert(abs(*dx) <= GRID_ELEMENT_WIDTH);
	assert(abs(*dy) <= GRID_ELEMENT_HEIGHT);

	// try horizontal move
	if (*dx < 0)
		FilterGridMotionLeft(m, r, dx);
	else
		if (*dx > 0)
			FilterGridMotionRight(m, r, dx);
	// try vertical move
	if (*dy < 0) {
		FilterGridMotionUp(m, r, dy);
	}
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
	auto y1_next = r.y + *dy;
	if (y1_next < 0)
		*dy = -r.y;
	else {
		auto newRow = DIV_GRID_ELEMENT_HEIGHT(y1_next);
		auto currRow = DIV_GRID_ELEMENT_HEIGHT(r.y);
		if (newRow != currRow) {
			assert(newRow + 1 == currRow); // we really move up
			auto startCol = DIV_GRID_ELEMENT_WIDTH(r.x);
			auto endCol = DIV_GRID_ELEMENT_WIDTH(r.x + r.w - 1);
			for (auto col = startCol; col <= endCol; ++col)
				if (!CanPassGridTile(m, col, newRow, GRID_BOTTOM_SOLID_MASK)) {
					std::cout << "Cant Move Up" << std::endl;
					*dy = MUL_GRID_ELEMENT_HEIGHT(currRow) - r.y;
					break;
				}
		}
	}
}


void FilterGridMotionDown(GridMap* m, const SDL_Rect& r, int* dy) {
	auto y2 = r.y + r.h - 1;
	auto y2_next = y2 + *dy;
	if (y2_next >= MAX_PIXEL_HEIGHT) {
		*dy = (MAX_PIXEL_HEIGHT)-1 - y2;
	}
	else {
		auto newRow = DIV_GRID_ELEMENT_HEIGHT(y2_next);
		auto currRow = DIV_GRID_ELEMENT_HEIGHT(y2);
		if (newRow != currRow) {
			assert(newRow - 1 == currRow); // we really move down
			auto startCol = DIV_GRID_ELEMENT_WIDTH(r.x);
			auto endCol = DIV_GRID_ELEMENT_WIDTH(r.x + r.w - 1);
			for (auto col = startCol; col <= endCol; ++col)
				if (!CanPassGridTile(m, col, newRow, GRID_TOP_SOLID_MASK)) {
					std::cout << "Cant Move Down" << col << std::endl;
					*dy = (MUL_GRID_ELEMENT_HEIGHT(newRow)) - 1 - y2;
					break;
				}
		}
	}
}