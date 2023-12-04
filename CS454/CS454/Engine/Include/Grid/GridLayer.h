#pragma once
//#include "Grid.h"
#include "GridMotion.h"
#include "GridCompute.h"
//#include "../../../Engine/Include/GridCompute2.h"
/*
class GridLayer {
private:
	GridIndex* grid_old = nullptr;
	unsigned total = 0;
	Dim totalRows = 0, totalColumns = 0;
	void Allocate(void) {
		total = totalRows * totalColumns * GRID_ELEMENTS_PER_TILE;
		grid_old = new GridIndex[total];
		memset(grid_old, GRID_EMPTY_TILE, total);
	}
	// TODO: adapt as needed and insert all rest motion control functions 
	// inside the private section
	void FilterGridMotionUp(const SDL_Rect& r, int* dy) const;
	void FilterGridMotionDown(const SDL_Rect& r, int* dy) const;
	void FilterGridMotionLeft(const SDL_Rect& r, int* dx) const;
	void FilterGridMotionRight(const SDL_Rect& r, int* dx) const;
public:
	void FilterGridMotion(const SDL_Rect& r, int* dx, int* dy) const;
	bool IsOnSolidGround(const SDL_Rect& r) const { // will need later for gravity
		int dy = 1; // down 1 pixel
		FilterGridMotionDown(r, &dy);
		return dy == 0; // if true IS attached to solid ground
	}
	GridIndex* &GetBuffer(void) { return grid_old; }
	//const GridIndex*& GetBuffer(void) const { return grid_old; }
	GridLayer();
	GridLayer(unsigned rows, unsigned cols);
};*/