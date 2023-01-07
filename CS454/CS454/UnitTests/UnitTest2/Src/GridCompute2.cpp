#include "../../../Engine/Include/GridCompute2.h"

bool IsTileColorEmpty(SDL_Color c)
{
	return emptyTileColors.In(c);
} // return false to disable

bool IsTileIndexAssumedEmpty(Index index) {
	if (index == 61) return false;
	else return true;
}


GridIndex* GetGridTileBlock(Dim colTile, Dim rowTile, Dim tileCols, GridIndex* grid) {
	return grid + (rowTile * tileCols + colTile) * GRID_BLOCK_SIZEOF;
}

void DisplayGrid(SDL_Rect viewWin, GridIndex* grid, Dim tileCols, SDL_Renderer* myrenderer) {
	auto startCol = DIV_TILE_WIDTH(viewWin.x);
	auto startRow = DIV_TILE_HEIGHT(viewWin.y);
	auto endCol = DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1);
	auto endRow = DIV_TILE_HEIGHT(viewWin.y + viewWin.h - 1);
	for (Dim rowTile = startRow; rowTile <= endRow; ++rowTile)
		for (Dim colTile = startCol; colTile <= endCol; ++colTile) {

			auto sx = MUL_TILE_WIDTH(colTile - startCol);
			auto sy = MUL_TILE_HEIGHT(rowTile - startRow);
			auto* gridBlock = GetGridTileBlock(colTile, rowTile, tileCols, grid);
			for (auto rowElem = 0; rowElem < GRID_BLOCK_ROWS; ++rowElem)
				for (auto colElem = 0; colElem < GRID_BLOCK_COLUMNS; ++colElem)

					if (*gridBlock++ & GRID_SOLID_TILE) {
						auto x = sx + MUL_GRID_ELEMENT_WIDTH(colElem);
						auto y = sy + MUL_GRID_ELEMENT_HEIGHT(rowElem);
						auto w = GRID_ELEMENT_WIDTH - 1;
						auto h = GRID_ELEMENT_HEIGHT - 1;
						SDL_Rect gridRect;
						gridRect.x = x;
						gridRect.y = y;
						gridRect.w = w;
						gridRect.h = h;
						SDL_RenderDrawRect(myrenderer, &gridRect);
					}
		}
}


std::string convert_SDLcolor_to_string(SDL_Color c){
	std::string coded_color = std::to_string(c.r) + std::to_string(c.g) + std::to_string(c.b) + std::to_string(c.a);
	return coded_color;
}

//ComputeGrid2
void ComputeTileGridBlocks2(
	const TileMap* map,
	GridIndex* grid,
	Bitmap tileSet,
	SDL_Color transColor,
	byte solidThreshold
) {
	Bitmap tileElem;// = BitmapCreate(TILE_WIDTH, TILE_HEIGHT);
	Bitmap gridElem{};// = BitmapCreate(GRID_ELEMENT_WIDTH, GRID_ELEMENT_HEIGHT);
	SDL_Rect tileElemRect{};
	SDL_Rect tilesetRect{};

	for (auto row = 0; row < MAX_HEIGHT; ++row)
		for (auto col = 0; col < MAX_WIDTH; ++col) {
			auto index = GetTile(col, row);
			tilesetRect.x, tilesetRect.y, tilesetRect.h, tilesetRect.w = MUL_TILE_WIDTH(index % 12), MUL_TILE_HEIGHT(index / 12), TILE_HEIGHT, TILE_WIDTH;
			tileElemRect.x, tileElemRect.y, tileElemRect.h, tileElemRect.w =  0, 0, TILE_HEIGHT, TILE_WIDTH;

			SDL_BlitSurface(&tileSet, &tilesetRect, &tileElem, &tileElemRect);

			if (IsTileIndexAssumedEmpty(index)) {
				emptyTileColors.Insert(tileElem, index); // assume tile colors to be empty
				memset(grid, GRID_EMPTY_TILE, GRID_ELEMENTS_PER_TILE);
				grid += GRID_ELEMENTS_PER_TILE;
			}
			else
				ComputeGridBlock(// auto increments grid as T*& 
					grid, index, tileElem, gridElem,
					tileSet, transColor, solidThreshold
				);
		}
	SDL_FreeSurface(&tileElem);
	SDL_FreeSurface(&gridElem);
}


void ComputeGridBlock(
	GridIndex*& grid,
	Index index,
	Bitmap tileElem,
	Bitmap gridElem,
	Bitmap tileSet,
	SDL_Color transColor,
	byte solidThreshold
) {
	SDL_Rect src{};
	SDL_Rect dest{};

	for (auto i = 0; i < GRID_ELEMENTS_PER_TILE; ++i) {
		auto x = i % GRID_BLOCK_ROWS;
		auto y = i / GRID_BLOCK_COLUMNS;

		src.x, src.y, src.w, src.h = x * GRID_ELEMENT_WIDTH, y* GRID_ELEMENT_HEIGHT, GRID_ELEMENT_WIDTH, GRID_ELEMENT_HEIGHT;
		dest.x, dest.y, dest.w, dest.h = 0, 0, GRID_ELEMENT_WIDTH, GRID_ELEMENT_HEIGHT;

		SDL_BlitSurface(&tileElem, NULL, &gridElem, NULL);

		auto isEmpty = ComputeIsGridIndexEmpty(gridElem, transColor, solidThreshold);
		*grid++ = isEmpty ? GRID_EMPTY_TILE : GRID_SOLID_TILE;
	}
}


SDL_Color GetPixel32(PixelMemory pixel, const SDL_PixelFormat* format) {
	SDL_Color PixelColor{};
	SDL_GetRGBA(*(pixel), format, &PixelColor.r, &PixelColor.g, &PixelColor.b, &PixelColor.a);

	return PixelColor;
}


bool ComputeIsGridIndexEmpty(
	Bitmap gridElement,
	SDL_Color transColor,
	byte solidThreshold
) {
	auto n = 0;
	auto counter = 0;
	BitmapAccessPixels(
		gridElement,
		[transColor, &n, &counter](PixelMemory pixel, const SDL_PixelFormat* format) {
			SDL_Color c = GetPixel32(pixel, format);

			if (c.r != transColor.r && c.g != transColor.g && c.b != transColor.b && c.a != transColor.a)
				if (!IsTileColorEmpty(c)) 
					++n;
		}
	);

	return n <= (unsigned int)solidThreshold;
}

void BitmapAccessPixels(Bitmap bmp, const BitmapAccessFunctor& f) {
	auto result = SDL_LockSurface(&bmp);
	assert(result);

	int bpp = bmp.format->BytesPerPixel;
	PixelMemory pixel;
	auto offset = bmp.pitch;
	auto depth = bmp.format->BitsPerPixel;

	for (auto y = bmp.h; y--; ) {
		for (auto x = bmp.w; x--; ) {
			pixel = (Uint32*)bmp.pixels + y * bmp.pitch + x * bpp;
			f(pixel, bmp.format);
		}
	}

	SDL_UnlockSurface(&bmp);
}
