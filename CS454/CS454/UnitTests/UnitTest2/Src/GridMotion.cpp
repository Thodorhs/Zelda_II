#include "../../../Engine/Include/Grid/GridMotion.h"
#include "../../../Engine/Include/Util/Print.h"
#include "../../../Engine/Include/Util/ConfigFuncs.h"

void SetSolidGridTile(GridMapOld* m, Dim col, Dim row)
{
	SetGridTile(m, col, row, GRID_SOLID_TILE);
}
void SetEmptyGridTile(GridMapOld* m, Dim col, Dim row)
{
	SetGridTile(m, col, row, GRID_EMPTY_TILE);
}
void SetGridTileFlags(GridMapOld* m, Dim col, Dim row, GridIndex flags)
{
	SetGridTile(m, col, row, flags);
}
void SetGridTileTopSolidOnly(GridMapOld* m, Dim col, Dim row)
{
	SetGridTileFlags(m, col, row, GRID_TOP_SOLID_MASK);
}
bool CanPassGridTile(GridMap* m, Dim col, Dim row, GridIndex flags) // i.e. checks if flags set
{
	auto fl = (*m)[row][col].flags;
	auto res = fl & flags;
	return res == 0;
}

void FilterGridMotionLeft(GridMap* m, const SDL_Rect& r, int* dx){}

void FilterGridMotionRight(GridMap* m, const SDL_Rect& r, int* dx)
{
	Dim power = Engine_Consts.grid_power;
	Dim scale = static_cast<Dim>(get_config_value<int>(configurators_t::RENDER_CONFIG,"view_scale_action"));
	auto x2 = (r.x + r.w - 1)/scale;
	auto x2_next = x2 + *dx;
	if (x2_next >= Engine_Consts.Map_width) {
		*dx = (Engine_Consts.Map_width -1) - x2;
	}
	else {
		auto newCol = DIV_GRID_ELEMENT_WIDTH(x2_next,power);
		auto currCol = DIV_GRID_ELEMENT_WIDTH(x2,power);
		if (newCol != currCol) {
			assert(newCol - 1 == currCol); // we really move right
			auto startRow = DIV_GRID_ELEMENT_HEIGHT(r.y,power);
			auto endRow = DIV_GRID_ELEMENT_HEIGHT(r.y + r.h - 1,power);
			for (auto row = startRow; row <= endRow; ++row)
				if (!CanPassGridTile(m, newCol, row, GRID_LEFT_SOLID_MASK)) {
					pr_warning("can't move right");
					*dx = (MUL_GRID_ELEMENT_WIDTH(newCol,power)  -1) - x2;
					break;
				}
		}
	}
}

void FilterGridMotionUp(GridMap* m, const SDL_Rect& r, int* dy){}

void FilterGridMotionDown(GridMap* m, const SDL_Rect& r, int* dy){}


void FilterGridMotion(GridMap* m, const SDL_Rect& r, int* dx, int* dy)
{
	assert(
		abs(*dx) <= Engine_Consts.Grid_el_sz && abs(*dy) <= Engine_Consts.Grid_el_sz
	);
	// try horizontal move
	if (*dx < 0)
		FilterGridMotionLeft(m, r, dx);
	else
		if (*dx > 0)
			FilterGridMotionRight(m, r, dx);
	// try vertical move
	if (*dy < 0)
		FilterGridMotionUp(m, r, dy);
	else
		if (*dy > 0)
			FilterGridMotionDown(m, r, dy);
}