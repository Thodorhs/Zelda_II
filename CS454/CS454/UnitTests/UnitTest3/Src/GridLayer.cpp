#include "../../../Engine/Include/Grid/GridLayer.h"

GridLayer::GridLayer(){}
GridLayer::GridLayer(unsigned rows, unsigned cols) {
	totalRows = rows;
	totalColumns = cols;

	Allocate();

	ComputeTileGridBlocks1(GetTile,grid, rows, cols);
	SetGridMap(grid, rows, cols);
	//printgrid(grid, rows, cols);
	//PrintMap(*(GetGridMap()));
}

void GridLayer::FilterGridMotion(const SDL_Rect& r, int* dx, int* dy) const {
	assert(abs(*dx) <= GRID_ELEMENT_WIDTH);
	assert(abs(*dy) <= GRID_ELEMENT_HEIGHT);

	// try horizontal move
	if (*dx < 0)
		GridLayer::FilterGridMotionLeft(r, dx);
	else
		if (*dx > 0)
			GridLayer::FilterGridMotionRight(r, dx);
	// try vertical move
	if (*dy < 0) {
		GridLayer::FilterGridMotionUp(r, dy);
	}
	else
		if (*dy > 0)
			GridLayer::FilterGridMotionDown(r, dy);
}

void GridLayer::FilterGridMotionUp(const SDL_Rect& r, int* dy)const {
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
				if (!CanPassGridTile(GetGridMap(), col, newRow, GRID_BOTTOM_SOLID_MASK)) {
					//std::cout << "Cant Move Up" << std::endl;
					*dy = MUL_GRID_ELEMENT_HEIGHT(currRow) - r.y;
					break;
				}
		}
	}
}

void GridLayer::FilterGridMotionDown(const SDL_Rect& r, int* dy) const {
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
				if (!CanPassGridTile(GetGridMap(), col, newRow, GRID_TOP_SOLID_MASK)) {
					//std::cout << "Cant Move Down" << col << std::endl;
					*dy = (MUL_GRID_ELEMENT_HEIGHT(newRow)) - 1 - y2;
					break;
				}
		}
	}
}

void GridLayer::FilterGridMotionLeft(const SDL_Rect& r, int* dx) const {
	auto x1_next = r.x + *dx;
	if (x1_next < 0) {
		std::cout << "Cant Move Left due to map size" << std::endl;
		*dx = -r.x;
	}
	else {
		auto newCol = DIV_GRID_ELEMENT_WIDTH(x1_next);
		auto currCol = DIV_GRID_ELEMENT_WIDTH(r.x);
		if (newCol != currCol) {
			assert(newCol + 1 == currCol); // we really move left
			auto startRow = DIV_GRID_ELEMENT_HEIGHT(r.y);
			auto endRow = DIV_GRID_ELEMENT_HEIGHT(r.y + r.h - 1);
			for (auto row = startRow; row <= endRow; ++row)
				if (!CanPassGridTile(GetGridMap(), newCol, row, GRID_RIGHT_SOLID_MASK)) {
					std::cout << "Cant Move Left" << std::endl;
					*dx = MUL_GRID_ELEMENT_WIDTH(currCol) - r.x;
					break;
				}
		}
	}
}

void GridLayer::FilterGridMotionRight(const SDL_Rect& r, int* dx) const {
	auto x2 = r.x + r.w - 1;
	auto x2_next = x2 + *dx;
	if (x2_next >= MAX_PIXEL_WIDTH) {
		std::cout << "Cant Move Left due to map size" << std::endl;
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
				if (!CanPassGridTile(GetGridMap(), newCol, row, GRID_LEFT_SOLID_MASK)) {
					std::cout << "Cant Move Right" << row << std::endl;
					*dx = (MUL_GRID_ELEMENT_WIDTH(newCol)) - 1 - x2;
					break;
				}
		}
	}
}