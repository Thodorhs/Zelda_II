#include "../Include/Grid/Grid.h"
#include "../Include/Util/ConfigFuncs.h"

std::unordered_map<unsigned short, bool> _Grid_::empty_tiles;

bool IsTileIndexAssumedEmpty(std::unique_ptr<_Grid_>& grid_cl, Index index) {
	if (index == 0xffff)
		return true;
	return grid_cl->empty_tiles[index];
}

void _Grid_::setGridTile(Dim row, Dim col, GridIndex index) { grid[row][col].flags=index; }
void SetGridTile(GridMapOld* m, Dim row, Dim col, GridIndex index) { }

grid_block GetGridTile(const GridMap* m, Dim col, Dim row) { return (*m)[row][col]; }

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

grid_block _Grid_::GetGridTileBlock(Dim rowTile, Dim colTile)const { return grid[rowTile][colTile]; }

_Grid_::_Grid_() {
	//grid_old = GridMapOld(grid_max_height(), std::vector<GridIndex>(grid_max_width(), 0));
	grid = GridMap(grid_max_height(), std::vector<grid_block>(grid_max_width()));
	fill_empty_tiles_map();
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
			GridIndex flags = IsTileIndexAssumedEmpty(grid_cl, tile) ?
			GRID_EMPTY_TILE : GRID_SOLID_TILE;
			for (auto el =0; el <grid_elements_per_tile(); el++) {
				elements.push_back(flags);
			}
			grid_block gb{ row,col,elements,flags};
			//gr_row.insert(gr_row.begin() + col, gb);
			gr_row[col] = gb;
		}
		grid_idx++;
	}
}

//!!WHEN VECTOR IS ALLOCATED USE INSERT!!!!!!//// FUAAA GIATIII
void ComputeTileGridBlocksOld(const TileMap* map, std::unique_ptr<_Grid_>& grid_cl) {
	Index grid_idx =0 ;
	Index grid_col = 0;
	GridMapOld& grid = grid_cl->get_grid();
	for (Dim row = 0; row < Engine_Consts.map_rows; row++){ 
		std::vector<GridIndex>& gr_row = grid[grid_idx];
		grid_col = 0;
		for (Dim col = 0; col < Engine_Consts.map_cols; col++) {
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

//view win was too large when scale = 1 so endcol,row went out of bounds
void DisplayGrid(const SDL_Rect& viewWin, SDL_Renderer* myrenderer,const _Grid_& grid_cl,const int scale) {
	auto startCol = DIV_TILE_WIDTH(viewWin.x, Engine_Consts.power);
	auto startRow = DIV_TILE_HEIGHT(viewWin.y, Engine_Consts.power);
	auto endCol = DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1, Engine_Consts.power);
	auto endRow = DIV_TILE_HEIGHT(viewWin.y + viewWin.h - 1, Engine_Consts.power);
	auto dpyX = MOD_TILE_WIDTH(viewWin.x, Engine_Consts.Tile_width);
	auto dpyY = MOD_TILE_WIDTH(viewWin.y, Engine_Consts.Tile_height);
	int grid_rows =  grid_block_rows();
	int grid_cols = grid_block_columns();
	Dim space = 0; //space between grid_old elements 
	for (Dim rowTile = startRow; rowTile <= endRow; ++rowTile) {
		for (Dim colTile = startCol; colTile <= endCol; ++colTile) {
			const auto block = grid_cl.GetGridTileBlock(rowTile, colTile);
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

/*****************MOTION CLASS FUNCS**********************/
#include "../../Engine/Include/Util/Print.h"
bool _Grid_::LayerCanPassGridTile(Dim col, Dim row, GridIndex flags)const { // i.e. checks if flags set
	auto res = (grid)[row][col].flags & flags;
	return res == 0;
}

void _Grid_::LayerFilterGridMotionLeft(const SDL_Rect& r, int* dx)const {
	Dim power = Engine_Consts.grid_power;
	Dim scale = grid_layer_scale;
	auto x1_next = r.x + *dx;
	if (x1_next < 0)
		*dx = -r.x;
	else {
		auto newCol = DIV_GRID_ELEMENT_WIDTH(x1_next, power) / scale;
		auto currCol = DIV_GRID_ELEMENT_WIDTH(r.x, power) / scale;
		if (newCol != currCol) {
			assert(newCol + 1 == currCol); // we really move left
			auto startRow = DIV_GRID_ELEMENT_HEIGHT(r.y, power) / scale;
			auto endRow = DIV_GRID_ELEMENT_HEIGHT(r.y + r.h - 1, power) / scale;
			for (auto row = startRow; row <= endRow; ++row)
				if (!LayerCanPassGridTile(newCol, row, GRID_RIGHT_SOLID_MASK)) {
					//pr_warning("can't move left");
					*dx = MUL_GRID_ELEMENT_WIDTH(currCol, power) - r.x / scale;
					break;
				}
		}
	}
}

void _Grid_::LayerFilterGridMotionRight( const SDL_Rect& r, int* dx)const {
	Dim power = Engine_Consts.grid_power;
	Dim scale = grid_layer_scale;
	auto x2 = (r.x + r.w - 1);
	auto x2_next = x2 + *dx;
	if (x2_next >= Engine_Consts.Map_width*scale) {
		*dx = (Engine_Consts.Map_width - 1) - x2;
		//pr_warning("can't move right");
	}
	else {
		auto newCol = DIV_GRID_ELEMENT_WIDTH(x2_next, power) / scale;
		auto currCol = DIV_GRID_ELEMENT_WIDTH(x2, power) / scale;
		if (newCol != currCol) {
			assert(newCol - 1 == currCol); // we really move right
			auto startRow = DIV_GRID_ELEMENT_HEIGHT(r.y, power) / scale;
			auto endRow = DIV_GRID_ELEMENT_HEIGHT(r.y + r.h - 1, power) / scale;
			for (auto row = startRow; row <= endRow; ++row)
				if (!LayerCanPassGridTile(newCol, row, GRID_LEFT_SOLID_MASK)) {
					//pr_warning("can't move right");
					*dx = (MUL_GRID_ELEMENT_WIDTH(newCol, power) - 1) - x2 / scale;
					break;
				}
		}
	}
}

void _Grid_::LayerFilterGridMotionUp(const SDL_Rect& r, int* dy) const{
	Dim power = Engine_Consts.grid_power;
	Dim scale = grid_layer_scale;
	auto y1_next = r.y + *dy;
	if (y1_next < 0) {
		*dy = -r.y;
		//pr_warning("can't move up");
	}
	else {
		auto newRow = DIV_GRID_ELEMENT_HEIGHT(y1_next, power) / scale;
		auto currRow = DIV_GRID_ELEMENT_HEIGHT(r.y, power) / scale;
		if (newRow != currRow) {
			assert(newRow + 1 == currRow); // we really move up
			auto startCol = DIV_GRID_ELEMENT_WIDTH(r.x, power) / scale;
			auto endCol = DIV_GRID_ELEMENT_WIDTH(r.x + r.w - 1, power) / scale;
			for (auto col = startCol; col <= endCol; ++col)
				if (!LayerCanPassGridTile(col, newRow, GRID_BOTTOM_SOLID_MASK)) {
					//pr_warning("can't move up");
					*dy = MUL_GRID_ELEMENT_HEIGHT(currRow, power) - r.y / scale;
					break;
				}
		}
	}
}

void _Grid_::LayerFilterGridMotionDown(const SDL_Rect& r, int* dy) const{
	Dim power = Engine_Consts.grid_power;
	Dim scale = grid_layer_scale;
	auto y2 = r.y + r.h - 1;
	auto y2_next = y2 + *dy;
	if (y2_next >= Engine_Consts.Map_height*scale) {
		//pr_warning("can't move down");
		*dy = (Engine_Consts.Map_height) - 1 - y2;
	}
	else {
		auto newRow = DIV_GRID_ELEMENT_HEIGHT(y2_next, power) / scale;
		auto currRow = DIV_GRID_ELEMENT_HEIGHT(y2, power) / scale;
		if (newRow != currRow) {
			assert(newRow - 1 == currRow); // we really move down
			auto startCol = DIV_GRID_ELEMENT_WIDTH(r.x, power) / scale;
			auto endCol = DIV_GRID_ELEMENT_WIDTH(r.x + r.w - 1, power) / scale;
			for (auto col = startCol; col <= endCol; ++col)
				if (!LayerCanPassGridTile(col, newRow, GRID_TOP_SOLID_MASK)) {
					//pr_warning("can't move down");
					*dy = (MUL_GRID_ELEMENT_HEIGHT(newRow, power)) - 1 - y2 / scale;
					break;
				}
		}
	}
}

void _Grid_::LayerFilterGridMotion(const SDL_Rect& r, int* dx, int* dy)const {
	assert(
		abs(*dx) <= Engine_Consts.Grid_el_sz*grid_layer_scale && abs(*dy) <= Engine_Consts.Grid_el_sz*grid_layer_scale
	);
	// try horizontal move
	if (*dx < 0)
		LayerFilterGridMotionLeft(r, dx);
	else
		if (*dx > 0)
			LayerFilterGridMotionRight(r, dx);
	// try vertical move
	if (*dy < 0)
		LayerFilterGridMotionUp(r, dy);
	else
		if (*dy > 0)
			LayerFilterGridMotionDown(r, dy);
}