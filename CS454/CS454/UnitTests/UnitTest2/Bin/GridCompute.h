#pragma once
#define GRID_ELEMENT_WIDTH 4
#define GRID_ELEMENT_HEIGHT 4

#if TILE_WIDTH % GRID_ELEMENT_WIDTH != 0
#error "TILE_WIDTH % GRID_ELEMENT_WIDTH must be zero!"
#endif

#if TILE_HEIGHT % GRID_ELEMENT_HEIGHT != 0
#error "TILE_HEIGHT % GRID_ELEMENT_HEIGHT must be zero!"
#endif

#define MAX_WIDTH 320
#define MAX_HEIGHT 240
#define TILE_WIDTH 16
#define TILE_HEIGHT 16

typedef unsigned short Index;
typedef unsigned short Dim;
typedef unsigned char byte;


#define GRID_BLOCK_COLUMNS (TILE_WIDTH / GRID_ELEMENT_WIDTH)
#define GRID_BLOCK_ROWS (TILE_HEIGHT / GRID_ELEMENT_HEIGHT)
#define GRID_ELEMENTS_PER_TILE (GRID_BLOCK_ROWS * GRID_BLOCK_COLUMNS)
#define GRID_MAX_HEIGHT (MAX_HEIGHT * GRID_BLOCK_ROWS)
#define GRID_MAX_WIDTH (MAX_WIDTH * GRID_BLOCK_COLUMNS)



using GridIndex = byte;
typedef GridIndex GridMap[GRID_MAX_WIDTH][GRID_MAX_HEIGHT];
static GridMap grid; // example of a global static grid
void SetGridTile(GridMap* m, Dim col, Dim row, GridIndex index)
{
	(*m)[row][col] = index;
}
GridIndex GetGridTile(const GridMap* m, Dim col, Dim row)
{
	return (*m)[row][col];
}