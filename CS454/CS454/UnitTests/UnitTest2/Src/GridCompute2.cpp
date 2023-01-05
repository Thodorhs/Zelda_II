#include "../../../Engine/Include/GridCompute2.h"
#include "../../../Engine/Include/GridCompute2.h"

bool IsTileColorEmpty(SDL_Color c)
{
	return emptyTileColors.In(c);
} // return false to disable

//ComputeGrid2

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

void ComputeGridBlock(
	GridIndex*& grid,
	Index index,
	Bitmap tileElem,
	Bitmap gridElem,
	Bitmap tileSet,
	SDL_Color transColor,
	byte solidThreshold
) {
	for (auto i = 0; i < GRID_ELEMENTS_PER_TILE; ++i) {
		auto x = i % GRID_BLOCK_ROWS;
		auto y = i / GRID_BLOCK_ROWS;
		BitmapBlit(
			tileElem,
			{ x * GRID_ELEMENT_WIDTH, y * GRID_ELEMENT_HEIGHT, GRID_ELEMENT_WIDTH, GRID_ELEMENT_HEIGHT },
			gridElem,
			{ 0, 0 }
		);
		auto isEmpty = ComputeIsGridIndexEmpty(gridElem, transColor, solidThreshold);
		*grid++ = isEmpty ? GRID_EMPTY_TILE : GRID_SOLID_TILE;
	}
}

Color GetPixel32(PixelMemory mem) {
	RGBA c;
	ReadPixelColor32(mem, &c, &c.a);
	return MakeColor32(c.r, c.g, c.b, c.a);
}

bool ComputeIsGridIndexEmpty(
	Bitmap gridElement,
	SDL_Color transColor,
	byte solidThreshold
) {
	auto n = 0;
	BitmapAccessPixels(
		gridElement,
		[transColor, &n](PixelMemory mem) {
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
	auto mem = BitmapGetMemory(bmp);
	auto offset = BitmapGetLineOffset(bmp);
	for (auto y = BitmapGetHeight(bmp); y--; ) {
		auto buff = mem;
		for (auto x = BitmapGetWidth(bmp); x--; ) {
			f(buff);
			buff += GetDepth();
		}
		mem += offset;
	}
	SDL_UnlockSurface(bmp);
}
