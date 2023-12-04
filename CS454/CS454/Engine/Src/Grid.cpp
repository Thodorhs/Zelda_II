#include "../Include/Grid/Grid.h"
#include "../Include/Util/ConfigFuncs.h"

bool IsTileIndexAssumedEmpty(std::unique_ptr<_Grid_>& grid_cl, Index index) {
	if (index == 0xffff)
		return true;
	auto tiles = grid_cl->get_emp_tiles();
	for (int i=0; i <5; i++) {
		if (tiles[i] == index)
			return true;
	}
	return false;

}

void SetGridTile(GridMapOld* m, Dim col, Dim row, GridIndex index){ (*m)[row][col] = index; }

grid_block GetGridTile(const GridMap* m, Dim col, Dim row){ return (*m)[row][col]; }

/*****************CLASS FUNCS**********************/

int grid_block_columns() { return Engine_Consts.Tile_width / Engine_Consts.Grid_el_sz; }

int grid_block_rows() { return Engine_Consts.Tile_height / Engine_Consts.Grid_el_sz; }

int grid_max_width() { return Engine_Consts.map_cols * grid_block_columns(); }

int grid_max_height() { return Engine_Consts.map_rows * grid_block_rows(); }

int grid_elements_per_tile() { return grid_block_rows() * grid_block_columns(); }

void _Grid_::print_grid() {
	for (int i = 0; i < grid_max_height(); i++) {
		for (int j = 0; j < grid_max_width(); j++) {
			std::cout << grid[i][j].flags;
		}
		std::cout << "\n";
	}
}

GridIndex _Grid_::GetOldGridTileBlock(Dim rowTile, Dim colTile) { return grid_old[rowTile][colTile]; }								    								

grid_block _Grid_::GetGridTileBlock(Dim rowTile, Dim colTile) { return grid[rowTile][colTile]; }

_Grid_::_Grid_() {
	//grid_old = GridMapOld(grid_max_height(), std::vector<GridIndex>(grid_max_width(), 0));
	grid = GridMap(grid_max_height(), std::vector<grid_block>(grid_max_width()));
}

void ComputeTileGridBlocks(const TileMap* map, std::unique_ptr<_Grid_>& grid_cl) {
	Index grid_idx = 0;
	Index grid_col = 0;
	Dim col;
	Dim row;
	GridMap& grid = grid_cl->get_s_grid();
	for (row = 0; row < Engine_Consts.map_rows; row++) {
		std::vector<grid_block>& gr_row = grid[grid_idx];
		grid_col = 0;
		for (col = 0; col < Engine_Consts.map_cols; col++) {
			Index tile = GetTile(col, row);
			int count = 0;
			std::vector<Index>elements;
			Dim flags = IsTileIndexAssumedEmpty(grid_cl, tile) ?
			GRID_EMPTY_TILE : GRID_SOLID_TILE;
			for (auto el =0; el <grid_elements_per_tile(); el++) {
				elements.push_back(flags);
			}
			grid_block gb{ row,col,elements,flags};
			gr_row.insert(gr_row.begin() + col, gb);			
		}
		grid_idx++;
	}
}

//!!WHEN VECTOR IS ALLOCATED USE INSERT!!!!!!//// FUAAA GIATIII
void ComputeTileGridBlocksOld(const TileMap* map, std::unique_ptr<_Grid_>& grid_cl) {
	Index grid_idx =0 ;
	Index grid_col = 0;
	Dim col;
	Dim row;
	GridMapOld& grid = grid_cl->get_grid();
	for (row = 0; row < Engine_Consts.map_rows; row++){ 
		std::vector<GridIndex>& gr_row = grid[grid_idx];
		grid_col = 0;
		for (col = 0; col < Engine_Consts.map_cols; col++) {
			Index tile = GetTile(col, row);
			int count = 0;
			for (auto el = grid_col; count < grid_elements_per_tile(); el++,count++) {	
				gr_row.insert(gr_row.begin() + el, IsTileIndexAssumedEmpty(grid_cl, tile) ?
					GRID_EMPTY_TILE :
					GRID_SOLID_TILE);   
			}
			grid_col+=grid_elements_per_tile();
		}
		grid_idx++;
	}
	
}

void DisplayGrid(const SDL_Rect& viewWin, SDL_Renderer* myrenderer,const std::unique_ptr<_Grid_>& grid_cl,const int scale) {
	auto startCol = DIV_TILE_WIDTH(viewWin.x, Engine_Consts.power);
	auto startRow = DIV_TILE_HEIGHT(viewWin.y, Engine_Consts.power);
	auto endCol = DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1, Engine_Consts.power);
	auto endRow = DIV_TILE_HEIGHT(viewWin.y + viewWin.h - 1, Engine_Consts.power);
	auto dpyX = MOD_TILE_WIDTH(viewWin.x, Engine_Consts.Tile_width);
	auto dpyY = MOD_TILE_WIDTH(viewWin.y, Engine_Consts.Tile_height);
	int grid_rows =  grid_block_rows();
	int grid_cols = grid_block_columns();
	Dim space = 1; //space between grid_old elements 
	for (Dim rowTile = startRow; rowTile <= endRow; ++rowTile) {
		for (Dim colTile = startCol; colTile <= endCol; ++colTile) {
			auto block = grid_cl->GetGridTileBlock(rowTile, colTile);
			std::vector<Index> elements = block.els;
			auto sx = MUL_TILE_WIDTH(colTile - startCol,Engine_Consts.power);
			auto sy = MUL_TILE_HEIGHT(rowTile - startRow,Engine_Consts.power);
			for (int i = 0; i < grid_rows; i++){
				for (int j = 0; j < grid_cols; j++) {
					if (elements[i * grid_rows + j] & GRID_SOLID_TILE) {
						SDL_Rect gridRect = { 0,0,0,0 };
						
						gridRect.x = ((sx + MUL_GRID_ELEMENT_WIDTH(j, Engine_Consts.grid_power) - dpyX)) * scale;
						gridRect.y = ((sy + MUL_GRID_ELEMENT_HEIGHT(i, Engine_Consts.grid_power) - dpyY)) * scale;
						gridRect.w = (Engine_Consts.Grid_el_sz - space) * scale;
						gridRect.h = (Engine_Consts.Grid_el_sz - space) * scale;

						SDL_RenderDrawRect(myrenderer, &gridRect);
					}
				}
			}
		}
	}
}

void DisplayGridOld(SDL_Rect& viewWin, SDL_Renderer* myrenderer, std::unique_ptr<_Grid_>& grid_cl) {
	auto startCol = DIV_TILE_WIDTH(viewWin.x, Engine_Consts.power);
	auto startRow = DIV_TILE_HEIGHT(viewWin.y, Engine_Consts.power);
	auto endCol = DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1, Engine_Consts.power);
	auto endRow = DIV_TILE_HEIGHT(viewWin.y + viewWin.h - 1, Engine_Consts.power);
	auto dpyX = MOD_TILE_WIDTH(viewWin.x, Engine_Consts.Tile_width);
	auto dpyY = MOD_TILE_WIDTH(viewWin.y, Engine_Consts.Tile_height);
	for (Dim rowTile = startRow; rowTile <= endRow; ++rowTile){
		for (Dim colTile = startCol; colTile <= endCol; ++colTile) {
			if (!IsTileIndexAssumedEmpty(grid_cl, GetTile(colTile, rowTile))) {
				auto gridBlock = grid_cl->GetOldGridTileBlock(rowTile, colTile);
				SDL_Rect gridRect;
				int scale = get_config_value<int>(configurators_t::RENDER_CONFIG, "view_scale");
				gridRect.x = (MUL_GRID_ELEMENT_WIDTH(colTile - startCol, Engine_Consts.grid_power) - dpyX) * scale ;
				gridRect.y = (MUL_GRID_ELEMENT_HEIGHT(rowTile - startRow, Engine_Consts.grid_power) - dpyY) * scale ;
				gridRect.w = (Engine_Consts.Grid_el_sz - 1) * scale;
				gridRect.h = (Engine_Consts.Grid_el_sz - 1) * scale;

				SDL_RenderDrawRect(myrenderer, &gridRect);
			}
		}
	}
}
/*****************END OF CLASS FUNCS**********************/