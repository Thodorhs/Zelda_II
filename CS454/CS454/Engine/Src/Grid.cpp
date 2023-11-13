#include "../Include/Grid/Grid.h"

bool IsTileIndexAssumedEmpty(std::unique_ptr<_Grid_>& grid_cl, Index index) {
	return index == grid_cl->get_empty();
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

_Grid_::_Grid_()
{
	grid = GridMap(grid_max_height(), std::vector<GridIndex>(grid_max_width(), 0));
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
