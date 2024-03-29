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

typedef struct grid_block {
	Dim row, col;
	std::vector<Index> els;
	GridIndex flags; //epifilaktika
};
typedef std::vector<std::vector<GridIndex>> GridMapOld;
typedef std::vector<std::vector<grid_block>> GridMap;

class _Grid_ {
private:
	
		GridMapOld grid_old;
		GridMap grid;
		Index empty = 31;
		Dim grid_layer_scale = 1;
public:
		std::unordered_map<Index, bool> static empty_tiles;

		void fill_empty_tiles_map() {
			for (int i = 0; i <= 100; i++) { empty_tiles[i] = false; }
			empty_tiles[61] = true;
			empty_tiles[10] = true;
			empty_tiles[20] = true;
			empty_tiles[3]  = true;
			empty_tiles[42] = true;
            empty_tiles[96] = true;
		}
		GridMapOld& get_grid() { return grid_old; }
		GridMap& get_s_grid() { return grid; }
		Index get_empty() { return empty; }
		void set_scale(const Dim _scale) { grid_layer_scale = _scale; }

		_Grid_();

		GridIndex GetOldGridTileBlock(Dim rowTile, Dim colTile);
		grid_block GetGridTileBlock(Dim rowTile, Dim colTile)const;
		
		void print_grid();


		bool LayerCanPassGridTile(Dim col, Dim row, GridIndex flags) const;
		void LayerFilterGridMotion(const SDL_Rect& r, int* dx, int* dy)const;

		void LayerFilterGridMotionLeft(const SDL_Rect& r, int* dx)const;

		void LayerFilterGridMotionRight(const SDL_Rect& r, int* dx)const;

		void LayerFilterGridMotionUp(const SDL_Rect& r, int* dy)const;

		void LayerFilterGridMotionDown(const SDL_Rect& r, int* dy)const;

		bool IsOnSolidGround(const SDL_Rect &r)const
		{
			int dy = 3;
			LayerFilterGridMotionDown(r, &dy);
			return dy == 0;
		}
		void setGridTile( Dim col, Dim row, GridIndex index);
};

inline int grid_block_columns();
inline int grid_block_rows();
inline int grid_max_height();
inline int grid_max_width();
inline int grid_elements_per_tile();
void SetGridTile(GridMapOld *m,Dim col, Dim row, GridIndex index);
bool IsTileIndexAssumedEmpty(_Grid_ &grid,Index index);
grid_block GetGridTile(const GridMap* m, Dim col, Dim row);
void DisplayGridOld(SDL_Rect& viewWin, SDL_Renderer* myrenderer, std::unique_ptr<_Grid_>& grid_cl);
void DisplayGrid(const SDL_Rect& viewWin, SDL_Renderer* myrenderer,const _Grid_& grid_cl,const int scale);
void ComputeTileGridBlocks(const TileMap* map, std::unique_ptr<_Grid_>& grid_cl);
void ComputeTileGridBlocksOld(const TileMap* map,std::unique_ptr<_Grid_>&grid_cl);