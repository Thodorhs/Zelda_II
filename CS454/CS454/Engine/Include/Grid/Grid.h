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

typedef std::vector<std::vector<GridIndex>> GridMapOld;
typedef struct grid_block {
	Dim row,col;
	std::vector<Index> els;
	Dim flags;
};
typedef std::vector<std::vector<grid_block>> GridMap;

class _Grid_ {
	
private:
	
		GridMapOld grid_old;
		GridMap grid;
		Index empty = 31;
		Index empty_tiles[5] = {0,1,2,3,4};
public:

		GridMapOld& get_grid() { return grid_old; }
		GridMap& get_s_grid() { return grid; }
		Index get_empty() { return empty; }

	

		Index* get_emp_tiles() { return empty_tiles; }
		 _Grid_();

		GridIndex GetOldGridTileBlock(Dim colTile, Dim rowTile);
		grid_block GetGridTileBlock(Dim rowTile, Dim colTile);
		
		void print_grid();
};

inline int grid_block_columns();
inline int grid_block_rows();
inline int grid_max_height();
inline int grid_max_width();
inline int grid_elements_per_tile();
bool IsTileIndexAssumedEmpty(_Grid_ &grid,Index index);
void SetGridTile(GridMapOld* m, Dim col, Dim row, GridIndex index);
grid_block GetGridTile(const GridMap* m, Dim col, Dim row);

void ComputeTileGridBlocksOld(const TileMap* map,std::unique_ptr<_Grid_>&grid_cl);

void DisplayGridOld(SDL_Rect& viewWin, SDL_Renderer* myrenderer, std::unique_ptr<_Grid_>& grid_cl);
void DisplayGrid(const SDL_Rect& viewWin, SDL_Renderer* myrenderer,const std::unique_ptr<_Grid_>& grid_cl,const int scale);
void ComputeTileGridBlocks(const TileMap* map, std::unique_ptr<_Grid_>& grid_cl);