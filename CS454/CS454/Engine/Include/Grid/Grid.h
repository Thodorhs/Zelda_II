#pragma once
#include"../Util/EngineDefines.h"
#include "../MapEditor.h"
#include <iostream>

#define GRID_THIN_AIR_MASK		0x0000 // element is ignored
#define GRID_LEFT_SOLID_MASK	0x0001 // bit 0
#define GRID_RIGHT_SOLID_MASK	0x0002 // bit 1
#define GRID_TOP_SOLID_MASK		0x0004 // bit 2
#define GRID_BOTTOM_SOLID_MASK	0x0008 // bit 3
#define GRID_GROUND_MASK		0x0010 // bit 4, keep objects top / bottom (gravity)
#define GRID_FLOATING_MASK		0x0020 // bit 5, keep objects anywhere inside (gravity)
#define GRID_EMPTY_TILE GRID_THIN_AIR_MASK
#define GRID_SOLID_TILE \
(GRID_LEFT_SOLID_MASK | GRID_RIGHT_SOLID_MASK | GRID_TOP_SOLID_MASK | GRID_BOTTOM_SOLID_MASK)


#define MAX_PIXEL_WIDTH(i,power)  (MUL_TILE_WIDTH(i,power))
#define MAX_PIXEL_HEIGHT(i,power) (MUL_TILE_HEIGHT(i,power))


#define DIV_GRID_ELEMENT_WIDTH(i,power)		((i)>>power)
#define DIV_GRID_ELEMENT_HEIGHT(i,power)	((i)>>power)
#define MUL_GRID_ELEMENT_WIDTH(i,power)		((i)<<power)
#define MUL_GRID_ELEMENT_HEIGHT(i,power)	((i)<<power)

#define GRID_BLOCK_SIZEOF \
(GRID_ELEMENTS_PER_TILE * sizeof(GridIndex))

typedef std::vector<std::vector<GridIndex>> GridMap;

class _Grid_ {
	
private:
	
		GridMap grid;
		Index empty = 61;
		Index empty_tiles[20] = { 61,48,49,50,60,62,72,73,74,84,85,96,97,16,28,40 };
public:

		GridMap& get_grid() { return grid; }
		Index get_empty() { return empty; }

		inline int grid_block_columns();
		inline int grid_block_rows();
		inline int grid_max_height();
		inline int grid_max_width();
		inline int grid_elements_per_tile();

		Index* get_emp_tiles() { return empty_tiles; }
		 _Grid_();

		GridIndex GetGridTileBlock(Dim colTile, Dim rowTile);
		
		void print_grid();
};


bool IsTileIndexAssumedEmpty(_Grid_ &grid,Index index);
void DisplayGrid(SDL_Rect viewWin, GridIndex* grid, Dim tileCols, SDL_Renderer* myrenderer);
void SetGridTile(GridMap* m, Dim col, Dim row, GridIndex index);
GridIndex GetGridTile(const GridMap* m, Dim col, Dim row);
void SetSolidGridTile(GridMap* m, Dim col, Dim row);

void SetEmptyGridTile(GridMap* m, Dim col, Dim row);

void SetGridTileFlags(GridMap* m, Dim col, Dim row, GridIndex flags);

void SetGridTileTopSolidOnly(GridMap* m, Dim col, Dim row);

bool CanPassGridTile(GridMap* m, Dim col, Dim row, GridIndex flags);
void ComputeTileGridBlocks1(const TileMap* map,std::unique_ptr<_Grid_>&grid_cl);

void DisplayGrid(SDL_Rect& viewWin, SDL_Renderer* myrenderer, std::unique_ptr<_Grid_>& grid_cl);
