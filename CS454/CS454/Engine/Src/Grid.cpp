#include "../Include/Grid/Grid.h"

bool IsTileIndexAssumedEmpty(std::unique_ptr<_Grid_>& grid_cl, Index index) {
	//return index == grid_cl->get_empty();
	auto tiles = grid_cl->get_emp_tiles();
	for (int i=0; i <16; i++) {
		if (tiles[i] == index)
			return true;
	}
	return false;

}

void SetGridTile(GridMap* m, Dim col, Dim row, GridIndex index)
{
	(*m)[row][col] = index;
}

GridIndex GetGridTile(const GridMap* m, Dim col, Dim row)
{
	return (*m)[row][col];
}

void SetSolidGridTile(GridMap* m, Dim col, Dim row)
{
	SetGridTile(m, col, row, GRID_SOLID_TILE);
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
	return (GetGridTile(m, row, col)) & (flags != 0);
}


//CLASS FUNCS


int _Grid_::grid_block_columns() {
	return Engine_Consts.Tile_width /Engine_Consts.Grid_el_sz;
}
int _Grid_::grid_block_rows() {
	return Engine_Consts.Tile_height / Engine_Consts.Grid_el_sz;
}

int _Grid_::grid_max_width() {
	return Engine_Consts.map_cols * grid_block_columns();
}

int _Grid_::grid_max_height() {
	return Engine_Consts.map_rows * grid_block_rows();
}

int _Grid_::grid_elements_per_tile() {
	return grid_block_rows() * grid_block_columns();
}

void _Grid_::print_grid() {
	for (int i = 0; i < grid_max_height(); i++) {

		for (int j = 0; j < grid_max_width(); j++) {

			std::cout << (int)grid[i][j];

		}
		std::cout << "\n";
	}
}

GridIndex _Grid_::GetGridTileBlock(Dim rowTile, Dim colTile) {
	return grid[rowTile][colTile];  
}								    								


grid_block _Grid_::GetGridTileBlock_2(Dim rowTile, Dim colTile) {return grid_test[rowTile][colTile];}


_Grid_::_Grid_()
{
	grid = GridMap(grid_max_height(), std::vector<GridIndex>(grid_max_width(), 0));
	grid_test = S_Grid_Map(grid_max_height(), std::vector<grid_block>(grid_max_width()));
}


void ComputeTileGridBlocks1_5(const TileMap* map, std::unique_ptr<_Grid_>& grid_cl) {
	Index grid_idx = 0;
	Index grid_col = 0;
	Dim col;
	Dim row;
	S_Grid_Map& grid = grid_cl->get_s_grid();
	for (row = 0; row < Engine_Consts.map_rows; row++) {
		std::vector<grid_block>& gr_row = grid[grid_idx];
		grid_col = 0;
		for (col = 0; col < Engine_Consts.map_cols; col++) {
			Index tile = GetTile(col, row);
			int count = 0;
			std::vector<Index>elements;
			for (auto el =0; el < grid_cl->grid_elements_per_tile(); el++) {
				elements.push_back(IsTileIndexAssumedEmpty(grid_cl, tile) ?
					GRID_EMPTY_TILE : GRID_SOLID_TILE);
				
			}
			grid_block gb{ row,col,elements};
			gr_row.insert(gr_row.begin() + col, gb);
			
		}
		grid_idx++;
	}
}
//END OF CLASS FUNCS
//!!WHEN VECTOR IS ALLOCATED USE INSERT!!!!!!//// FUAAA GIATIII
void ComputeTileGridBlocks1(const TileMap* map, std::unique_ptr<_Grid_>& grid_cl) {
	Index grid_idx =0 ;
	Index grid_col = 0;
	Dim col;
	Dim row;
	GridMap& grid = grid_cl->get_grid();
	for (row = 0; row < Engine_Consts.map_rows; row++){ 
		std::vector<GridIndex>& gr_row = grid[grid_idx];
		grid_col = 0;
		for (col = 0; col < Engine_Consts.map_cols; col++) {
			Index tile = GetTile(col, row);
			int count = 0;
			for (auto el = grid_col; count < grid_cl->grid_elements_per_tile(); el++,count++) {	
				gr_row.insert(gr_row.begin() + el, IsTileIndexAssumedEmpty(grid_cl, tile) ?
					GRID_EMPTY_TILE :
					GRID_SOLID_TILE);   
			}
			grid_col+=grid_cl->grid_elements_per_tile();
		}
		grid_idx++;
	}
}
#include "../Include/Util/ConfigFuncs.h"

void DisplayGrid_2(SDL_Rect& viewWin, SDL_Renderer* myrenderer, std::unique_ptr<_Grid_>& grid_cl,int scale) {
	
	auto startCol = DIV_TILE_WIDTH(viewWin.x, Engine_Consts.power);
	auto startRow = DIV_TILE_HEIGHT(viewWin.y, Engine_Consts.power);
	auto endCol = DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1, Engine_Consts.power);
	auto endRow = DIV_TILE_HEIGHT(viewWin.y + viewWin.h - 1, Engine_Consts.power);
	auto dpyX = MOD_TILE_WIDTH(viewWin.x, Engine_Consts.Tile_width);
	auto dpyY = MOD_TILE_WIDTH(viewWin.y, Engine_Consts.Tile_height);
	int grid_rows =  grid_cl->grid_block_rows();
	int grid_cols = grid_cl->grid_block_columns();
	
	Dim space = 1; //space between grid elements 

	for (Dim rowTile = startRow; rowTile <= endRow; ++rowTile) {
		for (Dim colTile = startCol; colTile <= endCol; ++colTile) {
			auto block = grid_cl->GetGridTileBlock_2(rowTile, colTile);
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

void DisplayGrid(SDL_Rect& viewWin, SDL_Renderer* myrenderer, std::unique_ptr<_Grid_>& grid_cl) {
	
	auto startCol = DIV_TILE_WIDTH(viewWin.x, Engine_Consts.power);
	auto startRow = DIV_TILE_HEIGHT(viewWin.y, Engine_Consts.power);
	auto endCol = DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1, Engine_Consts.power);
	auto endRow = DIV_TILE_HEIGHT(viewWin.y + viewWin.h - 1, Engine_Consts.power);
	auto dpyX = MOD_TILE_WIDTH(viewWin.x, Engine_Consts.Tile_width);
	auto dpyY = MOD_TILE_WIDTH(viewWin.y, Engine_Consts.Tile_height);

	for (Dim rowTile = startRow; rowTile <= endRow; ++rowTile){
		for (Dim colTile = startCol; colTile <= endCol; ++colTile) {
			if (!IsTileIndexAssumedEmpty(grid_cl, GetTile(colTile, rowTile))) {
				auto gridBlock = grid_cl->GetGridTileBlock(rowTile, colTile);
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

