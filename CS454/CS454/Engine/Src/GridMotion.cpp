#include "../Include/Grid/GridMotion.h"
#include "../Include/Util/Print.h"
#include "../Include/Util/ConfigFuncs.h"

void SetSolidGridTile(GridMapOld* m, Dim col, Dim row) { SetGridTile(m, col, row, GRID_SOLID_TILE); }

void SetEmptyGridTile(GridMapOld* m, Dim col, Dim row) { SetGridTile(m, col, row, GRID_EMPTY_TILE); }

void SetGridTileFlags(GridMapOld* m, Dim col, Dim row, GridIndex flags) { SetGridTile(m, col, row, flags); }

void SetGridTileTopSolidOnly(GridMapOld* m, Dim col, Dim row) { SetGridTileFlags(m, col, row, GRID_TOP_SOLID_MASK); }

bool CanPassGridTile(GridMap* m, Dim col, Dim row, GridIndex flags) { // i.e. checks if flags set
	auto res = (*m)[row][col].flags & flags;
	return res == 0;
}

void FilterGridMotionLeft(GridMap* m, const SDL_Rect& r, int* dx) {
	Dim power = Engine_Consts.grid_power;
	Dim scale = static_cast<Dim>(get_config_value<int>(configurators_t::RENDER_CONFIG, "view_scale_action"));
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
				if (!CanPassGridTile(m, newCol, row, GRID_RIGHT_SOLID_MASK)) {
					pr_warning("can't move left");
					*dx = MUL_GRID_ELEMENT_WIDTH(currCol, power) - r.x / scale;
					break;
				}
		}
	}
}

void FilterGridMotionRight(GridMap* m, const SDL_Rect& r, int* dx) {
	Dim power = Engine_Consts.grid_power;
	Dim scale = static_cast<Dim>(get_config_value<int>(configurators_t::RENDER_CONFIG, "view_scale_action"));
	auto x2 = (r.x + r.w - 1);
	auto x2_next = x2 + *dx;
	if (x2_next >= Engine_Consts.Map_width) {
		*dx = (Engine_Consts.Map_width - 1) - x2;
		pr_warning("can't move right");
	}
	else {
		auto newCol = DIV_GRID_ELEMENT_WIDTH(x2_next, power)/scale; 
		auto currCol = DIV_GRID_ELEMENT_WIDTH(x2, power)/scale; 
		if (newCol != currCol) {
			assert(newCol - 1 == currCol); // we really move right
			auto startRow = DIV_GRID_ELEMENT_HEIGHT(r.y, power)/scale;
			auto endRow = DIV_GRID_ELEMENT_HEIGHT(r.y + r.h - 1, power)/scale;
			for (auto row = startRow; row <= endRow; ++row)
				if (!CanPassGridTile(m, newCol, row, GRID_LEFT_SOLID_MASK)) {
					pr_warning("can't move right");
					*dx = (MUL_GRID_ELEMENT_WIDTH(newCol, power) - 1) - x2/scale;
					break;
				}
		}
	}
}

void FilterGridMotionUp(GridMap* m, const SDL_Rect& r, int* dy) {
	Dim power = Engine_Consts.grid_power;
	Dim scale = static_cast<Dim>(get_config_value<int>(configurators_t::RENDER_CONFIG, "view_scale_action"));
	auto y1_next = r.y + *dy;
	if (y1_next < 0)
		*dy = -r.y;
	else {
		auto newRow = DIV_GRID_ELEMENT_HEIGHT(y1_next, power) / scale;
		auto currRow = DIV_GRID_ELEMENT_HEIGHT(r.y, power) / scale;
		if (newRow != currRow) {
			assert(newRow + 1 == currRow); // we really move up
			auto startCol = DIV_GRID_ELEMENT_WIDTH(r.x, power) / scale;
			auto endCol = DIV_GRID_ELEMENT_WIDTH(r.x + r.w - 1, power) / scale;
			for (auto col = startCol; col <= endCol; ++col)
				if (!CanPassGridTile(m, col, newRow, GRID_BOTTOM_SOLID_MASK)) {
					pr_warning("can't move up");
					*dy = MUL_GRID_ELEMENT_HEIGHT(currRow, power) - r.y / scale;
					break;
				}
		}
	}
}

void FilterGridMotionDown(GridMap* m, const SDL_Rect& r, int* dy) {
	Dim power = Engine_Consts.grid_power;
	Dim scale = static_cast<Dim>(get_config_value<int>(configurators_t::RENDER_CONFIG, "view_scale_action"));
	auto y2 = r.y + r.h - 1;
	auto y2_next = y2 + *dy;
	if (y2_next >= Engine_Consts.Map_height) {
		*dy = (Engine_Consts.Map_height)-1 - y2;
	}
	else {
		auto newRow = DIV_GRID_ELEMENT_HEIGHT(y2_next, power) / scale;
		auto currRow = DIV_GRID_ELEMENT_HEIGHT(y2, power) / scale;
		if (newRow != currRow) {
			assert(newRow - 1 == currRow); // we really move down
			auto startCol = DIV_GRID_ELEMENT_WIDTH(r.x, power) / scale;
			auto endCol = DIV_GRID_ELEMENT_WIDTH(r.x + r.w - 1, power) / scale;
			for (auto col = startCol; col <= endCol; ++col)
				if (!CanPassGridTile(m, col, newRow, GRID_TOP_SOLID_MASK)) {
					pr_warning("can't move down");
					*dy = (MUL_GRID_ELEMENT_HEIGHT(newRow, power)) - 1 - y2 / scale;
					break;
				}
		}
	}
}

void FilterGridMotion(GridMap* m, const SDL_Rect& r, int* dx, int* dy) {
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