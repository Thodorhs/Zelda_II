#include "../../../Engine/Include/Grid/GridMotion.h"
#include "../../../Engine/Include/Util/Print.h"
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
	SetGridTileFlags(m, col, row, GRID_TOP_SOLID_MASK);
}
bool CanPassGridTile(S_Grid_Map* m, Dim col, Dim row, GridIndex flags) // i.e. checks if flags set
{
	auto fl = (*m)[row][col].flags;
	auto res = fl & flags;
	return res == 0;
}

void FilterGridMotionLeft(GridMap* m, const SDL_Rect& r, int* dx){}

void FilterGridMotionRight(S_Grid_Map* m, const SDL_Rect& r, int* dx)
{
	Dim power = Engine_Consts.grid_power;
	Dim scale = 2;
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


void FilterGridMotion(GridMap* m, const SDL_Rect& r, int* dx, int* dy) {}