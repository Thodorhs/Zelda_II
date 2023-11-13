#pragma once
#include "SDL.h"
#include <vector>
#include <map>

#include <memory>
typedef SDL_Surface BitmapSurface;
typedef SDL_Texture BitmapTexture;

typedef unsigned short Index;
typedef unsigned short Dim;

typedef unsigned char byte;
using GridIndex = byte;
typedef std::map<int, bool> KEY_MAP_t;

typedef struct Engine_Consts_t {
	Dim Tile_width,Tile_height,power,
		Map_height,Map_width,
		Grid_el_sz,grid_power,map_rows,map_cols;
	
	Engine_Consts_t(Dim tw,Dim th,Dim pow,Dim mh,Dim mw,Dim el_sz,Dim map_r,Dim map_c,Dim _pow):
		Tile_width(tw),Tile_height(th),power(pow),
		Map_height(mh),Map_width(mw),Grid_el_sz(el_sz),
		map_rows(map_r),map_cols(map_c),grid_power(_pow)
	{;}

	Engine_Consts_t(void) = default;
};

extern Engine_Consts_t Engine_Consts;

#define MAPHEIGHT 16
#define MAPWIDTH  300
#define TILE_WIDTH 16
#define TILE_HEIGHT 16



#define TILEX_MASK 0xFF00
#define TILEX_SHIFT 8
#define TILEY_MASK 0x00FF

//WE WILL SCALE TILES TO 32X32 so its 2^5=32 not 2^4
#define MUL_TILE_WIDTH(i,power)((i)<<power)
#define MUL_TILE_HEIGHT(i,power)((i)<<power)
#define DIV_TILE_WIDTH(i,power)((i)>>power)
#define DIV_TILE_HEIGHT(i,power)((i)>>power)
#define MOD_TILE_WIDTH(i,tw)((i)&(tw-1))
#define MOD_TILE_HEIGHT(i,th)((i)&(th-1))



