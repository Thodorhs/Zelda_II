#pragma once
#include "SDL.h"
#include <iostream>
#include <set>
#include <cassert>
#include <Functional>
#include "../../../Engine/Include/MapEditor.h"

typedef unsigned short Index;
typedef unsigned short Dim;

#define MAX_WIDTH 21
#define MAX_HEIGHT 42
#define TILE_WIDTH 16
#define TILE_HEIGHT 16

#define GRID_THIN_AIR_MASK 0x0000 // element is ignored
#define GRID_LEFT_SOLID_MASK 0x0001 // bit 0
#define GRID_RIGHT_SOLID_MASK 0x0002 // bit 1
#define GRID_TOP_SOLID_MASK 0x0004 // bit 2
#define GRID_BOTTOM_SOLID_MASK 0x0008 // bit 3
#define GRID_GROUND_MASK 0x0010 // bit 4, keep objects top / bottom (gravity)
#define GRID_FLOATING_MASK 0x0020 // bit 5, keep objects anywhere inside (gravity)
#define GRID_EMPTY_TILE GRID_THIN_AIR_MASK
#define GRID_SOLID_TILE \
(GRID_LEFT_SOLID_MASK | GRID_RIGHT_SOLID_MASK | GRID_TOP_SOLID_MASK | GRID_BOTTOM_SOLID_MASK)

#define GRID_ELEMENT_WIDTH 4
#define GRID_ELEMENT_HEIGHT 4
#if 16 % GRID_ELEMENT_WIDTH != 0
#error "TILE_WIDTH % GRID_ELEMENT_WIDTH must be zero!"
#endif
#if 16 % GRID_ELEMENT_HEIGHT != 0
#error "TILE_HEIGHT % GRID_ELEMENT_HEIGHT must be zero!"
#endif
#define GRID_BLOCK_COLUMNS (16 / GRID_ELEMENT_WIDTH)
#define GRID_BLOCK_ROWS (16 / GRID_ELEMENT_HEIGHT)
#define GRID_ELEMENTS_PER_TILE (GRID_BLOCK_ROWS * GRID_BLOCK_COLUMNS)
#define GRID_MAX_HEIGHT (240 * GRID_BLOCK_ROWS)
#define GRID_MAX_WIDTH (320 * GRID_BLOCK_COLUMNS)
typedef unsigned char byte;
using GridIndex = byte;

typedef GridIndex GridMap[GRID_MAX_WIDTH][GRID_MAX_HEIGHT];
static GridMap grid; // example of a global static grid

#define GRID_BLOCK_SIZEOF \
(GRID_ELEMENTS_PER_TILE * sizeof(GridIndex))

#define DIV_GRID_ELEMENT_WIDTH(i) ((i)>>2)
#define DIV_GRID_ELEMENT_HEIGHT(i) ((i)>>2)
#define MUL_GRID_ELEMENT_WIDTH(i) ((i)<<2)
#define MUL_GRID_ELEMENT_HEIGHT(i) ((i)<<2)

#define MUL_TILE_WIDTH(i) ((i)<<4)
#define MUL_TILE_HEIGHT(i)((i)<<4)
#define DIV_TILE_WIDTH(i) ((i)>>4)
#define DIV_TILE_HEIGHT(i)((i)>>4)
#define MOD_TILE_WIDTH(i) ((i)&15)
#define MOD_TILE_HEIGHT(i)((i)&15)

//GridCompute1
void SetGridTile(GridMap* m, Dim col, Dim row, GridIndex index);
bool IsTileIndexAssumedEmpty(Index index);
void ComputeTileGridBlocks1(Index(&MapGetTile)(Dim, Dim), GridIndex* grid);

////GridCompute2

//VGeneral definitionsV
typedef SDL_Surface Bitmap;
typedef uint32_t* PixelMemory;
typedef std::string color;

std::string convert_SDLcolor_to_string(SDL_Color c);

using BitmapAccessFunctor = std::function<void(PixelMemory, const SDL_PixelFormat* format)>;
void BitmapAccessPixels(Bitmap bmp, const BitmapAccessFunctor& f);
//end-General definitions-end

SDL_Color GetPixel32(PixelMemory pixel, const SDL_PixelFormat* format);

class TileColorsHolder final {
private:
	std::set<Index> indices;
	std::set<color> colors;
public:
	void Insert(Bitmap bmp, Index index) {
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

bool ComputeIsGridIndexEmpty(Bitmap gridElement, SDL_Color transColor, byte solidThreshold);
void ComputeGridBlock(
GridIndex*& grid,
	Index index,
	Bitmap tileElem,
	Bitmap gridElem,
	Bitmap tileSet,
	SDL_Color transColor,
	byte solidThreshold
);

void ComputeTileGridBlocks2(
	const TileMap* map,
	GridIndex* grid,
	Bitmap tileSet,
	SDL_Color transColor,
	byte solidThreshold
);



//Display Grid
GridIndex* GetGridTileBlock(Dim colTile, Dim rowTile, Dim tileCols, GridIndex* grid);
void DisplayGrid(SDL_Rect viewWin, GridIndex* grid, Dim tileCols, SDL_Renderer* myrenderer);