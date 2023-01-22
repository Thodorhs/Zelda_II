#include "../../../Engine/Include/Grid/GridCompute2.h"

bool IsTileColorEmpty(SDL_Color c)
{
	//return emptyTileColors.In(c);
	return false;
} // return false to disable


std::string convert_SDLcolor_to_string(SDL_Color c){
	std::string coded_color = std::to_string(c.r) + std::to_string(c.g) + std::to_string(c.b) + std::to_string(c.a);
	return coded_color;
}

//ComputeGrid2
void ComputeTileGridBlocks2(
	const TileMap* map,
	GridIndex* grid,
	BitmapSurface tileSet,
	SDL_Color transColor,
	byte solidThreshold
) {
	BitmapSurface tileElem = *(SDL_CreateRGBSurface(0, TILE_WIDTH, TILE_HEIGHT, 32, 0, 0, 0, 0));
	BitmapSurface gridElem = *(SDL_CreateRGBSurface(0, GRID_ELEMENT_WIDTH, GRID_ELEMENT_HEIGHT, 32, 0, 0, 0, 0));
	SDL_Rect tileElemRect{};
	SDL_Rect tilesetRect{};

	for (auto row = 0; row < MAPHEIGHT; ++row)
		for (auto col = 0; col < MAPWIDTH; ++col) {
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
	BitmapSurface tileElem,
	BitmapSurface gridElem,
	BitmapSurface tileSet,
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
	BitmapSurface gridElement,
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

void BitmapAccessPixels(BitmapSurface bmp, const BitmapAccessFunctor& f) {
	bool flag = false;
	int result = 0;
	if (SDL_MUSTLOCK(&bmp)) {
		flag = true;
		result = SDL_LockSurface(&bmp);
		assert(result);
	}

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

	if (flag) SDL_UnlockSurface(&bmp);
}