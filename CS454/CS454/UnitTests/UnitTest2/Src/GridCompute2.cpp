#include "../../../Engine/Include/GridCompute2.h"

bool IsTileColorEmpty(SDL_Color c)
{
	return emptyTileColors.In(c);
} // return false to disable

//ComputeGrid2
/*
void ComputeTileGridBlocks2(
	const TileMap* map,
	GridIndex* grid,
	Bitmap tileSet,
	SDL_Color transColor,
	byte solidThreshold
) {
	auto tileElem = SDL_(TILE_WIDTH, TILE_HEIGHT);
	auto gridElem = BitmapCreate(GRID_ELEMENT_WIDTH, GRID_ELEMENT_HEIGHT);
	for (auto row = 0; row < MAX_HEIGHT; ++row)
		for (auto col = 0; col < MAX_WIDTH; ++col) {
			auto index = GetTile(col, row);
			PutTile(tileElem, 0, 0, tileSet, index);
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
	BitmapDestroy(tileElem);
	BitmapDestroy(gridElem);
}
*/

void ComputeGridBlock(
	GridIndex*& grid,
	Index index,
	Bitmap tileElem,
	Bitmap gridElem,
	Bitmap tileSet,
	SDL_Color transColor,
	byte solidThreshold
) {
	SDL_Rect src;
	SDL_Rect dest;

	for (auto i = 0; i < GRID_ELEMENTS_PER_TILE; ++i) {
		auto x = i % GRID_BLOCK_ROWS;
		auto y = i / GRID_BLOCK_COLUMNS;

		src.x, src.y, src.w, src.h = x * GRID_ELEMENT_WIDTH, y* GRID_ELEMENT_HEIGHT, GRID_ELEMENT_WIDTH, GRID_ELEMENT_HEIGHT;
		dest.x, dest.y = 0, 0;

		SDL_BlitSurface(&tileElem, src, &gridElem, dest);

		auto isEmpty = ComputeIsGridIndexEmpty(gridElem, transColor, solidThreshold);
		*grid++ = isEmpty ? GRID_EMPTY_TILE : GRID_SOLID_TILE;
	}
}

SDL_Color GetPixel32(PixelMemory pixel, const SDL_PixelFormat* format) {
	SDL_Color PixelColor;

	SDL_GetRGBA(mem, const SDL_PixelFormat * format, &PixelColor.r, &PixelColor.g, &PixelColor.b, &PixelColor.a);

	return PixelColor;
}

bool ComputeIsGridIndexEmpty(
	Bitmap gridElement,
	SDL_Color transColor,
	byte solidThreshold
) {
	auto n = 0;
	BitmapAccessPixels(
		gridElement,
		[transColor, &n](PixelMemory pixel, const SDL_PixelFormat* format) {
			auto c = GetPixel32(mem);
			if (c != transColor && !IsTileColorEmpty(c))
			++n;
		}
	);

	return n <= solidThreshold;
}

void BitmapAccessPixels(Bitmap bmp, const BitmapAccessFunctor& f) {
	auto result = SDL_LockSurface(bmp);
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

	SDL_UnlockSurface(bmp);
}
