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