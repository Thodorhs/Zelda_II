#pragma once
#include "SDL.h"
#include <vector>

typedef SDL_Surface BitmapSurface;
typedef SDL_Texture BitmapTexture;

typedef unsigned short Index;
typedef unsigned short Dim;

typedef unsigned char byte;
using GridIndex = byte;




#define MAPHEIGHT 16
#define MAPWIDTH  300
#define TILESETWIDTH 16
#define TILESETHEIGHT 16

#define NUMBEROFROOMS 10
#define NUMBEROFELEVATORS 4

#define TILEX_MASK 0xFF00
#define TILEX_SHIFT 8
#define TILEY_MASK 0x00FF

//WE WILL SCALE TILES TO 32X32 so its 2^5=32 not 2^4
#define MUL_TILE_WIDTH(i) ((i)<<4)
#define MUL_TILE_HEIGHT(i)((i)<<4)
#define DIV_TILE_WIDTH(i) ((i)>>4)
#define DIV_TILE_HEIGHT(i)((i)>>4)
#define MOD_TILE_WIDTH(i) ((i)&15)
#define MOD_TILE_HEIGHT(i)((i)&15)