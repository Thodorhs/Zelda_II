#pragma once
#include "SDL.h"

typedef SDL_Surface BitmapSurface;
typedef SDL_Texture BitmapTexture;

typedef unsigned short Index;
typedef unsigned short Dim;

typedef unsigned char byte;
using GridIndex = byte;

#define MAPHEIGHT 16
#define MAPWIDTH  50
#define TILESETWIDTH 10
#define TILESETHEIGHT 10

//WE WILL SCALE TILES TO 32X32 so its 2^5=32 not 2^4
#define MUL_TILE_WIDTH(i) ((i)<<5)
#define MUL_TILE_HEIGHT(i)((i)<<5)
#define DIV_TILE_WIDTH(i) ((i)>>5)
#define DIV_TILE_HEIGHT(i)((i)>>5)
#define MOD_TILE_WIDTH(i) ((i)&15)
#define MOD_TILE_HEIGHT(i)((i)&15)