#pragma once
#include "SDL.h"
#include "Grid.h"
#include <set>
#include <cassert>
#include <Functional>
#include "../MapEditor.h"

////GridCompute2

//VGeneral definitionsV
typedef uint32_t* PixelMemory;
typedef std::string color;

std::string convert_SDLcolor_to_string(SDL_Color c);

using BitmapAccessFunctor = std::function<void(PixelMemory, const SDL_PixelFormat* format)>;
void BitmapAccessPixels(BitmapSurface bmp, const BitmapAccessFunctor& f);
//end-General definitions-end

SDL_Color GetPixel32(PixelMemory pixel, const SDL_PixelFormat* format);

class TileColorsHolder final {
private:
	std::set<Index> indices;
	std::set<color> colors;
public:
	void Insert(BitmapSurface bmp, Index index) {
		if (indices.find(index) == indices.end()) {
			indices.insert(index);
			BitmapAccessPixels(
				bmp,
				[this](PixelMemory pixel, const SDL_PixelFormat* format)
				{ colors.insert(convert_SDLcolor_to_string(GetPixel32(pixel, format))); }
			);
		}
	}
	
	void print() {
		int counter = 0;
		for (auto& it : colors) {
			std::cout << it << std::endl; counter++;
		}
		std::cout << counter << std::endl;
	}
	bool In(SDL_Color c) const
	{
		return colors.find(convert_SDLcolor_to_string(c)) != colors.end();
	}
};

static TileColorsHolder emptyTileColors;
bool IsTileColorEmpty(SDL_Color c);
bool IsTileIndexAssumedEmpty(Index index);

bool ComputeIsGridIndexEmpty(BitmapSurface gridElement, SDL_Color transColor, byte solidThreshold);
void ComputeGridBlock(
GridIndex*& grid,
	Index index,
	BitmapSurface tileElem,
	BitmapSurface gridElem,
	BitmapSurface tileSet,
	SDL_Color transColor,
	byte solidThreshold
);

void ComputeTileGridBlocks2(
	const TileMap* map,
	GridIndex* grid,
	BitmapSurface tileSet,
	SDL_Color transColor,
	byte solidThreshold
);